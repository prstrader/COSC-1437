// Programming Assignment 2
// Programming Fundamentals II (COSC 1437)
// Author: Gregory 
// Description: Calculates weekly summer job pay with tax and bonus.

// Setup
#include <iostream>
#include <iomanip>      
#include <string>
using namespace std;
 
int main()
{
    // Part B Constant
    const double TAX_RATE = 0.14;
    const int BONUS = 50;

    // Part C Variables
    string name;
    double payRate;
    double hoursWorked;
    double grossPay;
    double tax;
    double netPay;

    // Format decimal output
    cout << fixed << setprecision(2);

    // prompt inputs
    cout << "Enter last name: ";
    cin >> name;

    cout << "Enter hourly pay rate: ";
    cin >> payRate;

    cout << "Enter hours worked this week: ";
    cin >> hoursWorked;

    // Calculations 
    grossPay = payRate * hoursWorked;
    tax = grossPay * TAX_RATE;
    netPay = grossPay - tax + BONUS;

    // Produce Output
    cout << endl;
    cout << "Employee: " << name << endl;
    cout << "Pay Rate: $" << payRate << endl;
    cout << "Hours Worked: " << hoursWorked << endl;
    cout << "Gross Pay: $" << grossPay << endl;
    cout << "Tax (14%): $" << tax << endl;
    cout << "Net Pay (after tax + $50 bonus): $" << netPay << endl;

    return 0;
}
