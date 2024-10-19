#include <ios>
#include <iostream>
#include <limits>
#include <ctime>
using namespace std;

enum enCompare  {Before=-1, Equal=0, After=1};

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

struct stDay {
    int day;
    int month;
    int year;
};

struct stPeriod{

    stDay StartDate;
    stDay EndDate;
};

stDay ReadFullDate(){
    stDay Days;

    Days.day = ReadDay();
    Days.month = ReadMonth();
    Days.year = Readyear();

    return Days;
}

stPeriod ReadPeriods(){
    stPeriod Period;

    cout << "Enter Start date: " << endl;
    Period.StartDate = ReadFullDate();
    cout << "Enter End date: " << endl;
    Period.EndDate = ReadFullDate();

    return Period;
}
bool isDateOneBeforeDatetwo(stDay DayOne, stDay DayTwo){
  return DayOne.year < DayTwo.year ? true : (DayOne.year == DayTwo.year ? (DayOne.month < DayTwo.month ? true: (DayOne.month == DayTwo.month ? (DayOne.day < DayTwo.day) : false)):false);
}

bool isDateOneEqualsDatetwo(stDay DayOne, stDay DayTwo){

  return DayOne.year == DayTwo.year  ? DayOne.month == DayTwo.month ? DayOne.month == DayTwo.month : false : false;
}

bool isDateOneAfterDatetwo(stDay DayOne, stDay DayTwo){

  return (!isDateOneBeforeDatetwo(DayOne,DayTwo)) && isDateOneEqualsDatetwo(DayOne, DayTwo);
}
bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInMonth(short year, short month){

    short daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (month == 2) ? (isLeapYear(year) ? 29:28) : daysInMonth[month-1];
}

bool checkIsLastDay(stDay Day){
  return Day.day == NumberOfDaysInMonth(Day.year, Day.month);
}


bool checkIsLastMonth(short month){
    return month == 12;
}

stDay IncreaseDateByOneDay(stDay Date) {
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

int GateDateOneAndDateTwoDifference(stDay DayOne, stDay DayTwo, bool includeOneDay=false){
   int days = 0;

   while(isDateOneBeforeDatetwo(DayOne, DayTwo)){
    days++;
    DayOne = IncreaseDateByOneDay(DayOne);
   }

   return includeOneDay ? ++days : days;
}

int PeriodLength(stPeriod Period, bool includeEndDay=false){
    return GateDateOneAndDateTwoDifference(Period.StartDate, Period.EndDate, includeEndDay);
}

int main(){

    cout << "\nPeriod one: " << endl;
    stPeriod PeriodOne = ReadPeriods();

    cout << "Period length is: " << PeriodLength(PeriodOne) << endl;
    cout << "Period length (including end day) is: " << PeriodLength(PeriodOne, true) << endl;
    
    return 0;
}
