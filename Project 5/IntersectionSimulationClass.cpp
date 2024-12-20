#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

//takes a travel direction and creates an event for an arrival
//at the expected time
void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  double mean;
  double stdDev;
  int eventType;
  int timeToArrival;
  int arrivalTime;
  EventClass arrivalEvent;
  //setup the proper mean and standard deviation.
  if (travelDir == EAST_DIRECTION)
  {
    mean = eastArrivalMean;
    stdDev = eastArrivalStdDev;
    eventType = EVENT_ARRIVE_EAST;
  }
  
  else if (travelDir == WEST_DIRECTION)
  {
    mean = westArrivalMean;
    stdDev = westArrivalStdDev;
    eventType = EVENT_ARRIVE_WEST;
  }
  
  else if (travelDir == NORTH_DIRECTION)
  {
    mean = northArrivalMean;
    stdDev = northArrivalStdDev;
    eventType = EVENT_ARRIVE_NORTH;
  }

  else
  {
    mean = southArrivalMean;
    stdDev = southArrivalStdDev;
    eventType = EVENT_ARRIVE_SOUTH;
  }

  //get the time of arrival
  timeToArrival = getPositiveNormal(mean, stdDev);
  arrivalTime = currentTime + timeToArrival;

  //create event and add it to our list.
  arrivalEvent = EventClass(arrivalTime, eventType);
  eventList.insertValue(arrivalEvent);

  //print time, event type, and when the event happens
  cout << "Time: " << currentTime << " Scheduled " << arrivalEvent << endl;
  
}


void IntersectionSimulationClass::scheduleLightChange(
     )
{
  int nextLightTypeId;
  int currentLightDuration;
  int lightChangeTime;
  
  EventClass lightChangeEvent;

  //set next light
  if (currentLight == LIGHT_GREEN_EW)
  {
    nextLightTypeId = EVENT_CHANGE_YELLOW_EW;
    currentLightDuration = eastWestGreenTime;
  }
  
  else if (currentLight == LIGHT_YELLOW_EW)
  {
    nextLightTypeId = EVENT_CHANGE_GREEN_NS;
    currentLightDuration = eastWestYellowTime;
  }

  else if (currentLight == LIGHT_GREEN_NS)
  {
    nextLightTypeId = EVENT_CHANGE_YELLOW_NS;
    currentLightDuration = northSouthGreenTime;
  }

  else
  {
    nextLightTypeId = EVENT_CHANGE_GREEN_EW;
    currentLightDuration = northSouthYellowTime;
  }

  //set light change event and schedule it
  lightChangeTime = currentTime + currentLightDuration;
  lightChangeEvent = EventClass(lightChangeTime, nextLightTypeId);
  eventList.insertValue(lightChangeEvent);

  //print time, event type, and when the event happens
  cout << "Time: " << currentTime << " Scheduled " << lightChangeEvent << endl;
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  //retrieve event with smallest timeOccurs in eventList.
  EventClass nextEvent;  
  //removeFront outputs the front of the list to nextEvent.
  eventList.removeFront(nextEvent);


  if (nextEvent.getTimeOccurs() > timeToStopSim)
  {
    cout << endl;
    cout << "Next event occurs AFTER the simulation end time ("
         << nextEvent << ")!" << endl;
    return false;
  }

  //update time to when our event occurs
  currentTime = nextEvent.getTimeOccurs();
  int eventType = nextEvent.getType();
  cout << endl;
  cout << "Handling " << nextEvent << endl;

  /*
                         _            _     
         /\             (_)          | |    
        /  \   _ __ _ __ ___   ____ _| |___ 
       / /\ \ | '__| '__| \ \ / / _` | / __|
      / ____ \| |  | |  | |\ V / (_| | \__ \
     /_/    \_\_|  |_|  |_| \_/ \__,_|_|___/                        
  */


  //Put a new car in the proper queue, and schedule
  //a new arrival in the proper direction.
  if (eventType == EVENT_ARRIVE_EAST)
  {
    CarClass newCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(newCar);
    int queueLength = eastQueue.getNumElems();

    cout << "Time: " << currentTime << " Car #" << newCar.getId()
         << " arrives east-bound - queue length: " << queueLength << endl;
    scheduleArrival(EAST_DIRECTION);
    
    //statistics
    maxEastQueueLength = max(maxEastQueueLength, queueLength);
  }


  else if (eventType == EVENT_ARRIVE_WEST)
  {
    CarClass newCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(newCar);
    int queueLength = westQueue.getNumElems();

    cout << "Time: " << currentTime << " Car #" << newCar.getId()
         << " arrives west-bound - queue length: " << queueLength << endl;
    scheduleArrival(WEST_DIRECTION);

    //statistics
    maxWestQueueLength = max(maxWestQueueLength, queueLength);
  }


  else if (eventType == EVENT_ARRIVE_NORTH)
  {
    CarClass newCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(newCar);
    int queueLength = northQueue.getNumElems();

    cout << "Time: " << currentTime << " Car #" << newCar.getId()
         << " arrives north-bound - queue length: " << queueLength << endl;
    scheduleArrival(NORTH_DIRECTION);

    //statistics
    maxNorthQueueLength = max(maxNorthQueueLength, queueLength);
  }


  else if (eventType == EVENT_ARRIVE_SOUTH)
  {
    CarClass newCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(newCar);
    int queueLength = southQueue.getNumElems();

    cout << "Time: " << currentTime << " Car #" << newCar.getId()
         << " arrives south-bound - queue length: " << queueLength << endl;
    scheduleArrival(SOUTH_DIRECTION);

    //statistics
    maxSouthQueueLength = max(maxSouthQueueLength, queueLength);
  }


  /*
        _      _       _     _       
       | |    (_)     | |   | |      
       | |     _  __ _| |__ | |_ ___ 
       | |    | |/ _` | '_ \| __/ __|
       | |____| | (_| | | | | |_\__ \
       |______|_|\__, |_| |_|\__|___/
                  __/ |              
                 |___/               
  */


  //nextCar is the next in line to go at the intersection
  CarClass nextCar;
  //this means the light will change to yellow in east/west direction
  //so the currentLight is green in east/west direction
  if (eventType == EVENT_CHANGE_YELLOW_EW)
  {
    int eastCarsAdvanced = 0;
    int initialEastQueueLength = eastQueue.getNumElems();
    cout << "Advancing cars on east-west green" << endl;
    while (eastCarsAdvanced < eastWestGreenTime
        && eastQueue.getNumElems() > 0)
    {
      //this takes the next car out of the queue and assigns it to nextCar
      eastQueue.dequeue(nextCar);
      cout << "  Car #" << nextCar.getId() << " advances east-bound" << endl;
      eastCarsAdvanced += 1;
    }

    //do the same loop for the west direction
    int westCarsAdvanced = 0;
    int initialWestQueueLength = westQueue.getNumElems();
    while (westCarsAdvanced < eastWestGreenTime
        && westQueue.getNumElems())
    {
      westQueue.dequeue(nextCar);
      cout << "  Car #" << nextCar.getId() << " advances west-bound" << endl;
      westCarsAdvanced += 1;
    }

    //      Summary statistics
    cout << "East-bound cars advanced on green: " << eastCarsAdvanced
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on green: " << westCarsAdvanced
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    maxEastQueueLength = max(maxEastQueueLength, initialEastQueueLength);
    maxWestQueueLength = max(maxWestQueueLength, initialWestQueueLength);
    numTotalAdvancedEast += eastCarsAdvanced;
    numTotalAdvancedWest += westCarsAdvanced;


    currentLight = LIGHT_YELLOW_EW;
    scheduleLightChange();
  }


  //handle light changing to yellow in north/south direction
  //meaning the currentLight is green in north/south direction.
  else if (eventType == EVENT_CHANGE_YELLOW_NS)
  {
    int northCarsAdvanced = 0;
    int initialNorthQueueLength = northQueue.getNumElems();

    cout << "Advancing cars on north-south green" << endl;
    while (northCarsAdvanced < northSouthGreenTime
        && northQueue.getNumElems() > 0)
    {
      northQueue.dequeue(nextCar);
      cout << "  Car #" << nextCar.getId() << " advances north-bound" << endl;
      northCarsAdvanced += 1;
    }

    //do the same loop for the south direction
    int southCarsAdvanced = 0;
    int initialSouthQueueLength = southQueue.getNumElems();

    while (southCarsAdvanced < northSouthGreenTime
        && southQueue.getNumElems())
    {
      southQueue.dequeue(nextCar);
      cout << "  Car #" << nextCar.getId() << " advances south-bound" << endl;
      southCarsAdvanced += 1;
    }
    
    //      Summary statistics
    cout << "North-bound cars advanced on green: " << northCarsAdvanced
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on green: " << southCarsAdvanced
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    maxNorthQueueLength = max(maxNorthQueueLength, initialNorthQueueLength);
    maxSouthQueueLength = max(maxSouthQueueLength, initialSouthQueueLength);
    numTotalAdvancedNorth += northCarsAdvanced;
    numTotalAdvancedSouth += southCarsAdvanced;


    currentLight = LIGHT_YELLOW_NS;
    scheduleLightChange();
  
  }


  //light changing to green in east/west direction means
  //currentLight is yellow in north/south direction
  //yellow lights have an extra check for the driver to pass through
  //with probability percentCarsAdvanceOnYellow/100
  else if (eventType == EVENT_CHANGE_GREEN_EW)
  {
    /*
            North direction
    */

    cout << "Advancing cars on north-south yellow" << endl;

    int northCarsAdvanced = 0;
    int initialNorthQueueLength = northQueue.getNumElems();
    //runsYellow breaks the loop below if the car decides to stop
    //with probability percentCarsAdvanceOnYellow/100
    bool runsYellow = true;

    //this loop runs as long as there are still cars in line,
    //time for the next car to make it through,
    //and the next car will run a yellow.
    while (northCarsAdvanced < northSouthYellowTime
        && northQueue.getNumElems() > 0
        && runsYellow)
    {
      if (getUniform(0, 100) < percentCarsAdvanceOnYellow)
      {
        northQueue.dequeue(nextCar);
        cout << "  Car #" << nextCar.getId() 
             << " advances north-bound" << endl;
        northCarsAdvanced += 1;
      }
      else
      {
        cout << "  Next north-bound car will NOT advance on yellow" << endl;
        runsYellow = false;
      }
    }
    if (northCarsAdvanced == 0 && northQueue.getNumElems() == 0)
    {
      cout << "  No north-bound cars waiting to advance on yellow" << endl;
    }
    /*
            South direction
    */
    int southCarsAdvanced = 0;
    int initialSouthQueueLength = southQueue.getNumElems();
    runsYellow = true;

    //this loop runs as long as there are still cars in line,
    //time for the next car to make it through,
    //and the next car will run a yellow.
    while (southCarsAdvanced < northSouthYellowTime
        && southQueue.getNumElems() > 0
        && runsYellow)
    {
      if (getUniform(0, 100) < percentCarsAdvanceOnYellow)
      {
        southQueue.dequeue(nextCar);
        cout << "  Car #" << nextCar.getId() 
             << " advances north-bound" << endl;
        southCarsAdvanced += 1;
      }
      else
      {
        cout << "  Next south-bound car will NOT advance on yellow" << endl;
        runsYellow = false;
      }
    }

    if (southCarsAdvanced == 0 && southQueue.getNumElems() == 0)
    {
      cout << "  No south-bound cars waiting to advance on yellow" << endl;
    }

    //      Summary statistics
    cout << "North-bound cars advanced on yellow: " << northCarsAdvanced
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on yellow: " << southCarsAdvanced
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    maxNorthQueueLength = max(maxNorthQueueLength, initialNorthQueueLength);
    maxSouthQueueLength = max(maxSouthQueueLength, initialSouthQueueLength);
    numTotalAdvancedNorth += northCarsAdvanced;
    numTotalAdvancedSouth += southCarsAdvanced;


    currentLight = LIGHT_GREEN_EW;
    scheduleLightChange();
  }
  

  //light changing to green in north/south direction means
  //currentLight is yellow in east/west direction.
  else if (eventType == EVENT_CHANGE_GREEN_NS)
  {
    /*
            East direction
    */

    cout << "Advancing cars on east-west yellow" << endl;

    int eastCarsAdvanced = 0;
    int initialEastQueueLength = eastQueue.getNumElems();
    //runsYellow breaks the loop below if the car decides to stop
    //with probability percentCarsAdvanceOnYellow/100
    bool runsYellow = true;

    //this loop runs as long as there are still cars in line,
    //time for the next car to make it through,
    //and the next car will run a yellow.
    while (eastCarsAdvanced < eastWestYellowTime
        && eastQueue.getNumElems() > 0
        && runsYellow)
    {
      if (getUniform(0, 100) < percentCarsAdvanceOnYellow)
      {
        eastQueue.dequeue(nextCar);
        cout << "  Car #" << nextCar.getId()
             << " advances east-bound" << endl;
        eastCarsAdvanced += 1;
      }
      else
      {
        cout << "  Next east-bound car will NOT advance on yellow" << endl;
        runsYellow = false;
      }
    }
    if (eastCarsAdvanced == 0 && eastQueue.getNumElems() == 0)
    {
      cout << "  No east-bound cars waiting to advance on yellow" << endl;
    }
    /*
            West direction
    */
    int westCarsAdvanced = 0;
    int initialWestQueueLength = westQueue.getNumElems();
    runsYellow = true;


    while (westCarsAdvanced < eastWestYellowTime
        && westQueue.getNumElems() > 0
        && runsYellow)
    {
      if (getUniform(0, 100) < percentCarsAdvanceOnYellow)
      {
        westQueue.dequeue(nextCar);
        cout << "  Car #" << nextCar.getId()
             << " advances west-bound" << endl;
        westCarsAdvanced += 1;
      }
      else
      {
        cout << "  Next west-bound car will NOT advance on yellow" << endl;
        runsYellow = false;
      }
    }

    if (westCarsAdvanced == 0 && westQueue.getNumElems() == 0)
    {
      cout << "  No west-bound cars waiting to advance on yellow" << endl;
    }

    //      Summary Statistics
    cout << "East-bound cars advanced on yellow: " << eastCarsAdvanced
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on yellow: " << westCarsAdvanced
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    maxEastQueueLength = max(maxEastQueueLength, initialEastQueueLength);
    maxWestQueueLength = max(maxWestQueueLength, initialWestQueueLength);
    numTotalAdvancedEast += eastCarsAdvanced;
    numTotalAdvancedWest += westCarsAdvanced;


    currentLight = LIGHT_GREEN_NS;
    scheduleLightChange();
  }

  //continue simulation
  return true;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
