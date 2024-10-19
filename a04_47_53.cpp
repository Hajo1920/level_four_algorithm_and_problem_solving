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



stDay GateSystemDate(){
    stDay Day;

    time_t t = time(0);
    tm* now = localtime(&t);

    Day.year = now->tm_year + 1900;
    Day.month = now->tm_mon + 1;
    Day.day = now->tm_mday;

    return Day;
}

short GetDay(short day, short month, short year){
    short A ,Y ,M;

    A = (14-month) /12;
    Y = year - A;
    M = month + (12*A)-2;

    return (day + Y + (Y/4)-(Y/100)+(Y/400)+((31*M)/12))%7;
}

//overloading
short GetDay(stDay Day){
    return GetDay(Day.day, Day.month, Day.year);
}


string DayOfTheWeek(stDay Day, const string arrDays[]){
    
    return arrDays[GetDay(Day)];
}

bool isEndOfWeek(string Day){

    return Day == "Saturday";
}

bool isWeekEnd(string Day){
    return (Day == "Friday") || (Day == "Saturday");
}

bool isBusinessDay(string Day){
    return !isWeekEnd(Day);
}

short DayUntilEndOfWeek(stDay Day){
    
    return 6 - GetDay(Day);
}


short DayUntilTheEndOfMonth(stDay Day){

    return NumberOfDaysInMonth(Day.year, Day.month) - Day.day;
}

short DayUntilTheEndOfYear(stDay Day){
    return RemainingDaysOfYear(Day.day, Day.month, Day.year);
}
int main(){
  const string arrDays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday","Friday","Saturday" };
  stDay Day = GateSystemDate();

  cout << "Today is " << DayOfTheWeek(Day, arrDays) << ", " << Day.day << "/" << Day.month << "/" << Day.year << endl;

  cout << "\nIs it end of the week ?\n";
  if(isEndOfWeek(DayOfTheWeek(Day, arrDays))){
    cout << "\nYes, it is end of the week.\n";
  }else{
    cout << "\nNo, Not end of the week.\n";
  }

   cout << "\nIs it a week end ?\n";
  if(isWeekEnd(DayOfTheWeek(Day, arrDays))){
    cout << "\nYes, it is a week end.\n";
  }else{
    cout << "\nNo, Not a week end.\n";
  }

  cout << "\nIs it a business day ?\n";
  if(isBusinessDay(DayOfTheWeek(Day, arrDays))){
    cout << "\nYes, it is a business day.\n";
  }else{
    cout << "\nNo, it is not a business day\n";
  }

  cout << "\nDay until end of week: " << DayUntilEndOfWeek(Day) << " Day(s)\n";
  cout << "\nDay until end of the month: " << DayUntilTheEndOfMonth(Day) << " Day(s)\n";
  cout << "\nDay until end of the year: " << DayUntilTheEndOfYear(Day) << " Day(s)\n";

    return 0;
}
