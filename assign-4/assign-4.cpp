// ============================================================
// Name    : Gregory Ayala
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : Jun 14, 2026
// Program : Chapter 4 Major Project
// Option  : A — Hotel Billing  
// Purpose : This program calculates the billing total for a hotel stay.
// ============================================================

 // ===== SECTION 1: PSEUDOCODE =====
/*
start program

ask for nightly rate
ask for number of rooms
ask for number of nights
ask for tax rate

check all provided numbers for correct ranges with assert

convert tax rate from percent to decimal by dividing by 100

IF roomCount >= 10 and roomCount < 20
    set discount rate to 10%
    set discountTier to 1
ELSE IF roomCount >= 20 and roomCount < 30
    set discountRate to 20%
    set discountTier to 2
ELSE IF roomCount >= 30
    set discountRate to 30%
    set discountTier to 3
ELSE
    set discountRate to 0%
    set discountTier to 0
set loyalty status based on nights stayed at least 3

IF loyalty discount applies
    apply additional 5% discount 

IF no loyalty applies
    display message that 3 nights earns loyalty discount
ELSE 
    display that customer received a loyalty discount

IF discount tier equals 0 
    display message saying no room-booking discount was earned
ELSE IF discount tier does not equal 0
    display message saying a room discount was earned

IF room count is below first room threshold OR number of nights is 2 or fewer
    display message that a discount threshold was missed 

use switch to determine discount tier 
    case 0 :
        display no discount tier
    case 1: 
        display 10-19 rooms tier message
    case 2: 
        display 20-29 rooms tier message 
    case 3:
        display 30+ room tier message 
    default:
        display invalid message

compute subtotal using discounted nightly rate, rooms, and nights
compute sales tax amount
compute total bill

display formatted receipt showing
    nightly rate
    discount applied
    rooms
    nights
    subtotal
    sales tax amount
    total

end program
*/

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std; 

int main()
{
    //CONSTANTS
    const double DISCOUNT_TIER1 = 0.10;
    const double DISCOUNT_TIER2 = 0.20;
    const double DISCOUNT_TIER3 = 0.30;
    const double LOYALTY = 0.05;
    const int MIN_ROOM_TIER1 = 10;
    const int MIN_ROOM_TIER2 = 20;
    const int MIN_ROOM_TIER3 = 30;
    const int MIN_NIGHT_STAY = 3;
    const double EPSILON = 0.001; // adding EPSILON tolerance here 

     // ===== SECTION 2: INPUT & VALIDATION =====

    double nightlyRate;
    double salesTaxRate;
    int roomCount;
    int nightlyCount;

    cout << "Enter the nightly rate per room: " << endl;
    cin >> nightlyRate;

    cout << "Enter the number of rooms booked: " << endl;
    cin >> roomCount;

    cout << "Enter the number of nights: " << endl; 
    cin >> nightlyCount;

    cout << "Enter the tax rate percent: " << endl;
    cin >> salesTaxRate;
   

    // ASSERT   
    assert(nightlyRate > 0); // Checks that the rate is a number greater than 0. If false, the program aborts.
    assert(salesTaxRate >= 0 && salesTaxRate < 100); // Tax must be a number from 0-100. If outside that range, the program aborts.
    assert(nightlyCount > 0); // Enforces night count greater than 0. If false, the program aborts.
    assert(roomCount > 0); // Room count must be greater than 0. If false, the program aborts.

    // Section 6 operators used in assert: >, >=, &&, <


    // convert tax to %
    salesTaxRate = salesTaxRate / 100;

     // ===== SECTION 3: Operator Precedence Refrence =====

    /*
    Operator Precedence

    !               - Logical NOT - highest - evaluated first - right to left
    * / %           - multiplicative - left to right
    + -             - additive - left to right
    < <= > >=       - relational - left to right
    == !=           - equality - left to right
    &&              - logical AND - left to right
    ||              - logical OR - lowest - left to right
    */

    /*
    If rooms = 12, rate = 80.0, nights = 3

    !(rooms > 0) || (rate >= 50.0 && rooms != nights)
    !(12 > 0) || (80.0 >= 50.0 && 12 != 3)
    !(true) || (true && true)
    false || true
    true
    */
    
     // ===== SECTION 4: CORE LOGIC =====

    double newRate;
    int discountTier;

    if (roomCount >= MIN_ROOM_TIER1 && roomCount < MIN_ROOM_TIER2)
    {
        newRate = nightlyRate * (1 - DISCOUNT_TIER1);
        discountTier = 1;
    }
    else if (roomCount >= MIN_ROOM_TIER2 && roomCount < MIN_ROOM_TIER3)
    {
        newRate = nightlyRate * (1 - DISCOUNT_TIER2);
        discountTier = 2;
    }
    else if (roomCount >= MIN_ROOM_TIER3)
    {
        newRate = nightlyRate * (1 - DISCOUNT_TIER3);
        discountTier = 3;
    }
    else
    {
        newRate = nightlyRate;
        discountTier = 0;
    }

    if (discountTier == 0) //Section 6 operator ==
    {
        cout << "No discount was applied for this room booking" << endl;
    }
    else if (discountTier != 0) // Section 6 operator !=
    {
        cout << "You have received a discount for this stay!" << endl;
    }

    /* This compound Boolean expression checks whether the customer missed either the room discount threshold
    or the loyalty night threshold, so the program can warn them that at least one discount opportunity was missed. 
    */

    if (roomCount < MIN_ROOM_TIER1 || nightlyCount <= MIN_NIGHT_STAY -1) // Section 6 Operator < || <=
    {
        cout << "You have missed a discount threshold" << endl;
    }
    
    // length discount loyalty
    bool loyaltyQualified = nightlyCount >= MIN_NIGHT_STAY;
    if (loyaltyQualified)
    {
        newRate = newRate * (1 - LOYALTY);
    }
    
    if (!loyaltyQualified)
    {
        cout << "If you book 3 nights you will get a loyalty discount" << endl;
    }
    else
    {
        cout << "Congrats you earned a 5% loyalty discount" << endl; 
    }

     // ===== SECTION 5: SWITCH STATEMENT =====

    switch(discountTier)
    {
        case 0:
            cout << "This customer has normal status" << endl;
            break;
        case 1:
            cout << "This customer has purchased 10-19 rooms" << endl;
            break;
        case 2:
            cout << "This customer has purchased 20-29 rooms" << endl; 
        break;
        case 3:
            cout << "This customer has purchased 30+ rooms" << endl;
        break;
        default:
            cout << "Invalid, Discount tier could not be determined" << endl;
    }

    // math logic
    double discountApplied;
    double rateDifference;
    double subtotal;
    double salesTaxAmount;
    double total;

    rateDifference = nightlyRate - newRate;

    if (rateDifference < EPSILON) 
    {
        discountApplied = 0.0;
    }
    else 
    {
        discountApplied = (nightlyRate - newRate) / nightlyRate * 100;
    }

    subtotal = newRate * roomCount * nightlyCount;
    salesTaxAmount = subtotal * salesTaxRate;
    total = subtotal + salesTaxAmount;


     // ===== SECTION 7: FLOATING POINT BUG GUARD =====
    /* 
    When comparing the rate difference, we need to make sure that a floating-point number entered by the user can still be
    treated as equal to newRate when the difference is only a tiny rounding error. Since the program does not stop a user
    from entering a longer decimal value, we do not want the receipt to show a minuscule discount that does not really exist.
    Using == is unreliable because an extra decimal place can cause a rounding error. We chose the EPSILON method with a
    value of 0.001 because it checks to the third decimal place and helps ignore amounts smaller than a penny.
    
    */

     // ===== SECTION 8: FORMATTED OUTPUT RECEIPT =====
    cout << fixed << setprecision(2);
    cout << left << setw(30) << "Nightly Rate per room: " << right << "$" << setw(11)  << nightlyRate << endl;
    cout << left << setw(30) << "Discount Applied: " << right << setw(12) << discountApplied << '%' << endl;
    cout << left << setw(30) << "Number of Rooms: " << right << setw(12) << roomCount << endl;
    cout << left << setw(30) << "Number of nights: " << right << setw(12) << nightlyCount << endl;
    cout << left << setw(30) << "Subtotal before tax: " << right << "$" << setw(11)  << subtotal << endl;
    cout << left << setw(30) << "Sales tax amount: " << right << "$" << setw(11)  << salesTaxAmount << endl;
    cout << left << setw(30) << "Total billed: " << right << "$" << setw(11)  << total << endl; 

    return 0; 
}

 // ===== SECTION 9: KNOWN BUG RISKS =====
/* 
1) If a user inputs a negative number, it could show that we owe the user money. That is wrong, so we used assert to make sure
the code stops before that happens.
2) When the user inputs a number for tax, we cannot use it right away in the current logic. To avoid that issue, we immediately
converted it to a percent by dividing the number given by 100.
3) Floating-point values can store tiny rounding errors, so two rates that should be equal might appear slightly different. 
To prevent the receipt from showing a false tiny discount, the program uses an EPSILON tolerance and treats very small differences
as zero. 
*/
