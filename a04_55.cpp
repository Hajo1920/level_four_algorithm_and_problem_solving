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

short ReadVacationDays() {
    short num;
    do {
    cout << "Please enter how many days to spend on vacation: ";
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

struct stDay {
    int day;
    int month;
    int year;
};

stDay ReadFullDate(){
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

bool checkIsLastDay(stDay Day){
  return Day.day == NumberOfDaysInMonth(Day.year, Day.month);
}


bool checkIsLastMonth(short month){
    return month == 12;
}

int GetDay(short day, short month, short year){
    short A ,Y ,M;

    A = (14-month) /12;
    Y = year - A;
    M = month + (12*A)-2;

    return (day + Y + (Y/4)-(Y/100)+(Y/400)+((31*M)/12))%7;
}

int GetDay(stDay Day){

    return GetDay(Day.day, Day.month, Day.year);
}
string DayOfTheWeek(stDay Day, const string arrDays[]){

    return arrDays[GetDay(Day)];
}

bool isWeekEnd(string Day){
    return (Day == "Friday") || (Day == "Saturday");
}

bool isBusinessDay(string Day){
    return !isWeekEnd(Day);
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

stDay IncreaseDateByXDays(stDay Date, int addDays, const string arrDays[]) {

    short weekEndCounter = 0;

    // this while loop will start from the firstVacationDay and will loop and 
    // check weekEnd day and increase date by one untill business day arive and will break
    while(isWeekEnd(DayOfTheWeek(Date, arrDays))){
            Date = IncreaseDateByOneDay(Date);
        }
   // after the while loop braks. this for loop will start looping from the first business day
   // and will add one day for every weekEnd day it finds until it reaches the final day.
    for(int x = 1; x <= addDays+weekEndCounter; x++){
        Date = IncreaseDateByOneDay(Date);
         if(isWeekEnd(DayOfTheWeek(Date, arrDays))){
            weekEndCounter++;
        }
    }
    return Date;
}

int main(){
    const string arrDays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday","Friday","Saturday" };
    cout << "Vacation Starts:" << endl;
    stDay DayOne = ReadFullDate();
    short vacationDays = ReadVacationDays();

    DayOne = IncreaseDateByXDays(DayOne, vacationDays, arrDays);

    cout << "Return date: " << DayOfTheWeek(DayOne, arrDays) << ", " << DayOne.day << "/" << DayOne.month << "/" << DayOne.year << endl;

    return 0;
}
