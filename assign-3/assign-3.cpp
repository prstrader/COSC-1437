// Programming Assignment 3
// Programming Fundamentals II (COSC 1437)
// Author: Gregory
// Description: Reads employee records from a file, writes a formatted
//              payroll report, then demonstrates stream-inspection
//              functions and input-failure handling.
 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
 
using namespace std;
 
int main()
{
    ifstream inFile("payrollData.txt");
    ofstream outFile("payrollReport.txt");

    if (!inFile)
    {
        cout << "Error opening payrollData.txt" << endl;
        return 1;
    }

    if (!outFile)
    {
        cout << "Error opening payrollReport.txt" << endl;
        return 1;
    }

    // Variable for one employee's data
    string firstName, lastName, department;
    double grossSalary, bonusPercent, taxPercent;
    double distance, travelTime;
    double paycheck, averageSpeed;

    outFile << fixed << showpoint << setprecision(2);

    while (inFile >> firstName)
    {
        inFile >> lastName >> department ;
        inFile >> grossSalary >> bonusPercent >> taxPercent;
        inFile >> distance >> travelTime;

        // Formulas
        paycheck = grossSalary + (grossSalary * bonusPercent / 100) - (grossSalary * taxPercent / 100);
        averageSpeed = distance / travelTime;


        // Out file setup
        // outFile << fixed << showpoint << setprecision(2); (commented out redundant)
        outFile << "Name: " << firstName << " " << lastName
                << ", Department: " << department << endl;
        outFile << "Monthly Gross Salary: $" << setw(8) << grossSalary
                << ", Bonus: " << bonusPercent << "%"
                << ", Taxes: " << taxPercent << "%" << endl;
        outFile << "Paycheck: $" << paycheck << endl;
        outFile << "Distance Traveled: " << distance << " miles"
                << ", Travel Time: " << travelTime << " hours" << endl;
        outFile << "Average Speed: " << averageSpeed << " miles per hour" << endl << endl; // two endl to add space between names
    }

    inFile.close();
    outFile.close();

    // Part 2: Stream Inspector

    // Variable
    string line;

    // Peek and getline
    cout << "Enter a line of text: ";
    char firstChar = cin.peek();

    if (firstChar >= '0' and firstChar <= '9')
    {
        cout << "The first character is a digit." << endl;
    }
    else if ((firstChar >= 'A' and firstChar <= 'Z') or 
            (firstChar >= 'a' and firstChar <= 'z'))
    {
        cout << "The first character is a letter." << endl;
    }
    else
    {
        cout << "The first character is neither a letter nor a digit." << endl;
    }

    getline(cin, line);
    cout << "You entered: " << line << endl;
    cout << endl;

    // putback(): could be used after reading one character to inspect,
    // then returning it to the stream so another input operations can use it. 

    // Ignore and getline
    int userInteger;
    string description;

    cout << "Enter an integer: ";
    cin >> userInteger;

    cin.ignore(1000, '\n');
    
    cout << "Enter a full-line description: ";
    getline(cin, description);

    cout << "Integer: " << userInteger << endl;
    cout << "Description: " << description << endl;

    // Input failure
    double number;

    cout << "Enter a number: ";
    cin >> number;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. That was not a number." << endl; 
    }
    else
    {
        cout << "You entered: " << number << endl;
    }

    return 0;
}

