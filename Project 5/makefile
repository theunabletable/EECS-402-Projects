project5.exe: project5.o random.o CarClass.o EventClass.o IntersectionSimulationClass.o
	g++ project5.o random.o CarClass.o EventClass.o IntersectionSimulationClass.o -o project5.exe

project5.o: project5.cpp IntersectionSimulationClass.h CarClass.h EventClass.h random.h constants.h
	g++ -std=c++98 -Wall -c project5.cpp -o project5.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c random.cpp -o random.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h FIFOQueueClass.h CarClass.h random.h constants.h
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

clean:
	rm -f *.o project5.exe
