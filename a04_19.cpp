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

struct stDay {
    int day;
    int month;
    int year;
};



stDay ReadFullDateOne(){
    stDay Days;

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



short RemainingDaysOfYear(short day, short month, short year){

    short remainingDays = 0;
    for(short x = 1; x < month; x++){
        remainingDays+= NumberOfDaysInMonth(year, x);
    }
   
    return remainingDays + day;
}

bool isDateOneBeforeDatetwo(stDay DayOne, stDay DayTwo){
  return DayOne.year < DayTwo.year ? true : (DayOne.year == DayTwo.year ? (DayOne.month < DayTwo.month ? true: (DayOne.month == DayTwo.month ? (DayOne.day < DayTwo.day) : false)):false);
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


void SwapDates(stDay& Date1, stDay& Date2) {
    stDay TempDate;
    TempDate.year = Date1.year;
    TempDate.day = Date1.year;
    TempDate.day = Date1.year;

    Date1.year = Date2.year;
    Date1.month = Date2.month;
    Date1.day = Date2.day;

    Date2.year = TempDate.year;
    Date2.month = TempDate.month;
    Date2.day = TempDate.day;
}

int GetDifferenceInDays(stDay Date1, stDay Date2, bool IncludeEndDay = false) {
    int Days = 0;
    short SawpFlagValue = 1;
    if (!isDateOneBeforeDatetwo(Date1, Date2)) {
        SwapDates(Date1, Date2);
        SawpFlagValue = -1;
    }
    while (isDateOneBeforeDatetwo(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
}



int main(){
    
  stDay DayOne = ReadFullDateOne();
  stDay DayTwo = ReadFullDateOne();


  cout << "Difference is: " << GetDifferenceInDays(DayOne, DayTwo) << endl;
  cout << "Difference (including end day) is: " << GetDifferenceInDays(DayOne, DayTwo, true) << endl;

    return 0;
}
