#include <ios>
#include <iostream>
#include <limits>
using namespace std;

short Readyear(){
    short num;

    do {
    cout << "Enter year to check: ";
    cin >> num;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter integer type only!";
        cin >> num;
    }

    } while (num < 0);

    return num;
}

short ReadMonth(){
    short num;

    do {
    cout << "choose a month [1 - 12]: ";
    cin >> num;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter integer type only!";
        cin >> num;
    }

    } while (num <= 0 || num > 12);

    return num;
}

bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInMonth(short year, short month){

    short daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    return (month == 2) ? (isLeapYear(year) ? 29:28) : daysInMonth[month-1];
}

short NumberOfHoursInMonth(short year, short month){
    
    return NumberOfDaysInMonth(year, month) * 24;
}

long NumOfMinutesInMonth(short year, short month){
    
    return NumberOfHoursInMonth(year, month) * 60;
}

long NumOfSecondsInMonth(short year, short month){

    return NumOfMinutesInMonth(year, month) * 60;
}

int main(){
    short year = Readyear();
    short month = ReadMonth();
    
    bool isLeap = isLeapYear(year);
    
    cout << "Number of Days in month [" << month << "] is " << NumberOfDaysInMonth(year, month) << endl;
    cout << "Number of Hours in month [" << month << "] is " << NumberOfHoursInMonth(year,month) << endl;
    cout << "Number of Minutes in month [" << month << "] is " << NumOfMinutesInMonth(year,month) << endl;
    cout << "Number of Seconds in month [" << month << "] is " << NumOfSecondsInMonth(year,month) << endl;
    return 0;
}