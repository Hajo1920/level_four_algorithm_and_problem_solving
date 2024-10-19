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

stDays IncreaseDateByXDays(stDays Date, int addDays) {
   
    for(int x = 1; x <= addDays; x++){
        Date = IncreaseDateByOneDay(Date);
    }
    return Date;
}

stDays IncreaseDateByOneWeek(stDays Date) {
    for(short x = 1; x <= 7; x++){
        Date = IncreaseDateByOneDay(Date);
    }
    return Date;
}

stDays IncreaseDateByXWeeks(stDays Date, int input) {
     for(int x = 1; x <= input; x++){
      Date = IncreaseDateByOneWeek(Date);
   }

  return Date;
}

stDays IncreaseDateByOneMonth(stDays Date) {
    Date.month++;
    return Date;
}

stDays IncreaseDateByXMonths(stDays Date, int input) {
  for(int x = 1; x <= input; x++){
    Date = IncreaseDateByOneMonth(Date);
  }

  return Date;
}

stDays IncreaseDateByOneYear(stDays Date) {
  Date.year++;

  return Date;
}

stDays IncreaseDateByXYears(stDays Date, int input) {
  for(int x = 1; x <= input; x++){
    Date = IncreaseDateByOneYear(Date);
  }

  return Date;
}

stDays IncreaseDateByXYearsFaster(stDays Date, int input){
    Date.year += input;

    return Date;
}

stDays IncreaseDateByOneDecade(stDays Date) {
  Date.year += 10; 
  return Date;
}

stDays IncreaseDateByXDecades(stDays Date, int input) {

  for(int x = 1; x <= input * 10; x++){
  
    Date = IncreaseDateByOneYear(Date);

  }

  return Date;
}

stDays IncreaseDateByXDecadesFaster(stDays Date, int input) {

  Date.year+= input * 10;
  return Date;
}

stDays IncreaseDateByCentury(stDays Date) {

  Date.year += 100;
  return Date;
}

stDays IncreaseDateByMillenium(stDays Date) {
   Date.year += 1000;
  return Date;
  return Date;
}
int main(){
    stDays Days = ReadFullDate();

    Days = IncreaseDateByOneDay(Days);
    cout << "01-Adding one day: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXDays(Days, 10);
    cout << "02-Adding 10 days: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByOneWeek(Days);
     cout << "03-Adding one week: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXWeeks(Days, 10);
     cout << "04-Adding 10 weeks: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByOneMonth(Days);
     cout << "05-Adding one month: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXMonths(Days,5);
     cout << "06-Adding 5 months: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByOneYear(Days);
     cout << "07-Adding one year: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXYears(Days, 10);
     cout << "08-Adding 10 years: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXYearsFaster(Days, 10);
     cout << "09-Adding 10 years (faster): " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByOneDecade(Days);
     cout << "10-Adding one decade: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXDecades(Days, 10);
     cout << "11-Adding 10 decades: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByXDecadesFaster(Days, 10);
     cout << "12-Adding 10 decades (faster): " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByCentury(Days);
     cout << "13-Adding one century: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = IncreaseDateByMillenium(Days);
     cout << "14-Adding one millenium: " << Days.day << "/" << Days.month << "/" << Days.year << endl;

    return 0;
}