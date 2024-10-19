#include <ios>
#include <iostream>
#include <limits>
#include <ctime>
using namespace std;

short Readyear(){
    short num;

    do {
    cout << "Enter a year: ";
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
    cout << "Enter a month [1 - 12]: ";
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

short ReadDay() {
    short num;
    do {
    cout << "Enter a day [1 - 31]: ";
    cin >> num;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter integer type only!";
        cin >> num;
    }

    } while (num <= 0 || num > 31);

    return num;
}
bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInMonth(short year, short month){

    short daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (month == 2) ? (isLeapYear(year) ? 29:28) : daysInMonth[month-1];
}

struct stDays {
    short day;
    short month;
    short year;
};

stDays ReadFullDate(){
    stDays Days;

    Days.day = ReadDay();
    Days.month = ReadMonth();
    Days.year = Readyear();

    return Days;
}

bool checkIsLastDay(stDays Day){
  return Day.day == NumberOfDaysInMonth(Day.year, Day.month);
}


bool checkIsLastMonth(short month){
    return month == 12;
}

stDays IncreaseDateByOneDay(stDays Date) {
    if (checkIsLastDay(Date)) {
        if (checkIsLastMonth(Date.month)) {
            Date.month = 1;
            Date.day = 1;
            Date.year++;
        } else {
            Date.day = 1;
            Date.month++;
        }
    } else {
        Date.day++;
    }
    return Date;
}


// this is my solution.
// stDays IncreaseDayByOne(stDays Days){
//     if(Days.month == 2 && Days.day > NumberOfDaysInMonth(Days.year, Days.month)){
//         Days.day = NumberOfDaysInMonth(Days.year, Days.month);
//         cout << "You entered extra day for february which should be 29 if leap year or 28 for normal year." << endl;
//         cout << "We automatically have returned the value of the day to the correct last day of february" << endl;
//     }
//     Days.day++;

//     if(Days.day > NumberOfDaysInMonth(Days.year, Days.month)){
        
//             Days.day = 1;
//             Days.month++;
        
//         if(Days.month > 12){
//             Days.month = 1;
//             Days.year++;
//         }
//     }

//     return Days;
// }

int main(){
    stDays Days = ReadFullDate();

    Days = IncreaseDateByOneDay(Days);

    cout << "Day after adding by one day is: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    return 0;
}