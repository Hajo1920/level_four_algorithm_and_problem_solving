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

struct stDate {
 short day,month,year;
};

stDate ReadFullDates(){
    stDate Days;
     Days.day = ReadDay();
    Days.month = ReadMonth();
    Days.year = Readyear();

    return Days;
}

bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInMonth(short year, short month){

    short daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (month == 2) ? (isLeapYear(year) ? 29:28) : daysInMonth[month-1];
}

bool checkIsLastDay(stDate Day){
  return Day.day == NumberOfDaysInMonth(Day.year, Day.month);
}

bool isValidDay(stDate Day){
    return Day.day <= NumberOfDaysInMonth(Day.year, Day.month);
}

bool checkIsLastMonth(short month, short year){
    return month == 12;
}


int main(){
    stDate Days = ReadFullDates();

    if(isValidDay(Days)) cout << "\nYes Day is valid date\n";
    else cout << "\nNo Day is invalid date.\n";

    return 0;
}