#include <iostream>
using namespace std;

/* 
  Program to calculate interest accrued on a bank account
  EECS402 Fall 2024 Project 1
 
  Name: Andrew Jones
  Uniqname: drej
  Email: drej@umich.edu
  Student ID 8324 8056
  Date: September 19, 2024

  This program calculates interest for a bank account over a specified number 
  of months. Interest is applied according to different interest rates, 
  depending on account balance. Users can opt to display month-by-month 
  results or just the final balance.
*/

///Function prototypes
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     ); 

/*
  Accrues interest for a given number of months on the balance. 

  Parameter: balanceAmt is inputted by the user and is referenced as 
  the original balance into accrueOneMonthsInterest, which slowly 
  updates to the final balance. Must be non-negative.

  Parameter: numMonths is inputted by the user and is the number 
  of months to accrue interest for. Must be positive. This number is 
  how many times accrueOneMonthsInterest is called.

  Parameter: doPrintEachMonth if true, gets passed into accrueOneMonthsInterest 
  to display month-by-month interest, and to calculate silently if false.

  Function prints the final results of the interest and returns true if 
  interest accrual was successful, ultimately returns false and prints an error
  if balanceAmt is negative or if numMonths is zero or negative.
*/

bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     );

/*
  Accrues a single month of interest, potentially printing each month along
  the way, depending on the value of doPrintInfo

  Parameter: balanceAmt is referenced into this function by accrueInterest.
  Its size determines an interest rate. That interest rate is applied,
  and balanceAmt is updated accordingly.

  Parameter: doPrintInfo is passed in by accrueInterest. If true,
  this function will print the results of each month's interest, but
  if false, this function will calculate silently.

  Function prints the results of a single month of interest and returns true
  if it does so successfully. It returns false and gives an error if 
  balanceAmt is negative.
*/


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  double initialBalance;
  int numMonths;
  char printChoice;
  bool doPrintEachMonth;
  doPrintEachMonth = false;

  cout << "Enter the initial balance of the account: ";
  cin >> initialBalance;

  cout << "Enter the number of months to accrue interest: ";
  cin >> numMonths;
  
  //determine whether to print results each month
  cout << "Show month-by-month results? Type y for yes, any other for no: ";
  cin >> printChoice;
  if (printChoice == 'y')
  {
    doPrintEachMonth = true;
  }
  
  
  //accrue interest
  if (!accrueInterest(initialBalance, numMonths, doPrintEachMonth))
  {
    cout << "Sorry, an error was detected. Unable to provide results!" << endl;
  }
  
  return 0;
}
#endif

bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     )
{
  double initialBalance;         //balanceAmt will be mutated, so initialBalance
  initialBalance = balanceAmt;   //lets us save this original value to be                                        //printed at the end.              
  

  //Checks that the input is valid.
  if (numMonths <= 0)
  {
    cout << "ERROR in accrueInterest: numMonths must be > 0, but the value " 
         << numMonths << " was provided!" << endl;
    return false;
  }
  
  /*
    This accrues interest as many times as numMonths. If accrueOneMonthsInterest
    hits an error, this function will return false and kick back up to main.
  */
  for (int i = 0; i < numMonths; i++)
  {
    if (!accrueOneMonthsInterest(balanceAmt, doPrintEachMonth))
    {
      return false;
    }
  }
  
  //summarize results
  cout << "Interest accrued for " << numMonths << " months!" << endl;
  cout << "Initial balance: " << initialBalance << endl;
  cout << "Total interest accrued: " << balanceAmt - initialBalance << endl;
  cout << "Final balance: " << balanceAmt << endl;
  
  return true; 
  /* 
    if we've made it this far, the program has continued without error
    and returns true for main up above.
  */
}


bool accrueOneMonthsInterest(double &balanceAmt, const bool doPrintInfo)
{
  const double HIGH_BALANCE_INTEREST = 0.004;
  const double STD_BALANCE_INTEREST = 0.00225;
  const double LOW_BALANCE_INTEREST = 0.0015;
  const double MAX_THRESHOLD_BALANCE = 15000;
  const double MIN_THRESHOLD_BALANCE = 1000;
  double interestRate;
  double interest;
  /*
    HIGH_BALANCE_INTEREST at 0.4% is assigned to interestRate and applied 
    to balanceAmt's over MAX_THRESHOLD_BALANCE. 

    LOW_BALANCE_INTEREST at 0.15% is assigned to interestRate and applied 
    to balanceAmt's under MIN_THRESHOLD_BALANCE. 

    STD_BALANCE_INTEREST at 0.225% is assigned to interestRate and applied 
    to balanceAmt's between MIN_THRESHOLD_BALANCE and MAX_THRESHOLD_BALANCE. 

    interest will be calculated depending on balanceAmt and interestRate,
    then added to balanceAmt
  */

  //check for invalid balance and throw error if so.
  if (balanceAmt < 0)
  {
   cout << "ERROR in accrueOneMonthsInterest: balanceAmt must be >= 0," 
        << "but the value " << balanceAmt << " was provided!" << endl;
    return false;
  }
  
  //determine interest rate based on balanceAmt as described above.
  if (balanceAmt < MIN_THRESHOLD_BALANCE)
  {
    interestRate = LOW_BALANCE_INTEREST;
  }
  else if (balanceAmt >= MAX_THRESHOLD_BALANCE)
  {
    interestRate = HIGH_BALANCE_INTEREST;
  }
  else     
  {
    interestRate = STD_BALANCE_INTEREST;
  }

  //calculate interest
  interest = balanceAmt * interestRate;
  
  //calculate new balance based on interest, and print info.
  if (doPrintInfo)
  {
    cout << "Accruing interest for 1 month:" << endl;
    cout << "  Initial balance: " << balanceAmt << endl;
    cout << "  Initial rate: " << interestRate << endl;
    cout << "  Interest accrued: " << interest << endl;
    balanceAmt += interest;
    cout << "  New balance: " << balanceAmt << endl;
  }
  else //calculate new balance but do -not- print info.
  {
    balanceAmt += interest;
  }
  
  return true;
  //function ran without errors, returns true to accrueInterest.
}
  
