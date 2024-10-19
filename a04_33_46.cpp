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


stDays DecreaseDateByOneDay(stDays Date) {
    if (Date.month == 1) {
        if (Date.day == 1) {
            Date.day = 31;
            Date.year = 12;
            Date.year--;
        } else {
            Date.month--;
            Date.day = Date.day = NumberOfDaysInMonth(Date.year, Date.month);
        }
    } else {
        Date.day--;
    }
    return Date;
}

stDays DecreaseDateByXDays(stDays Date, int addDays) {
   
    for(int x = 1; x <= addDays; x++){
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

stDays DecreaseDateByOneWeek(stDays Date) {
    for(short x = 1; x <= 7; x++){
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

stDays DecreaseDateByXWeeks(stDays Date, int input) {
     for(int x = 1; x <= input; x++){
      Date = DecreaseDateByOneWeek(Date);
   }

  return Date;
}

stDays DecreaseDateByOneMonth(stDays Date) {
    Date.month--;
    
    return Date;
}

stDays DecreaseDateByXMonths(stDays Date, int input) {
  for(int x = 1; x <= input; x++){
    Date = DecreaseDateByOneMonth(Date);
  }

  return Date;
}

stDays DecreaseDateByOneYear(stDays Date) {
  Date.year--;
  return Date;
}

stDays DecreaseDateByXYears(stDays Date, int input) {
  for(int x = 1; x <= input; x++){
    Date = DecreaseDateByOneYear(Date);
  }

  return Date;
}

stDays DecreaseDateByXYearsFaster(stDays Date, int input){
    Date.year -= input;
    return Date;
}

stDays DecreaseDateByOneDecade(stDays Date) {
  Date.year -= 10; 
  return Date;
}

stDays DecreaseDateByXDecades(stDays Date, int input) {

  for(int x = 1; x <= input * 10; x++){
  
    Date = DecreaseDateByOneYear(Date);

  }

  return Date;
}

stDays DecreaseDateByXDecadesFaster(stDays Date, int input) {

  Date.year-= input * 10;
  return Date;
}

stDays DecreaseDateByCentury(stDays Date) {

  Date.year -= 100;
  return Date;
}

stDays DecreaseDateByMillenium(stDays Date) {
   Date.year -= 1000;
  return Date;
  return Date;
}
int main(){
    stDays Days = ReadFullDate();

    Days = DecreaseDateByOneDay(Days);
    cout << "01-subtracting one day: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXDays(Days, 10);
    cout << "02-subtracting 10 days: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByOneWeek(Days);
     cout << "03-subtracting one week: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXWeeks(Days, 10);
     cout << "04-subtracting 10 weeks: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByOneMonth(Days);
     cout << "05-subtracting one month: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXMonths(Days,5);
     cout << "06-subtracting 5 months: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByOneYear(Days);
     cout << "07-subtracting one year: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXYears(Days, 10);
     cout << "08-subtracting 10 years: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXYearsFaster(Days, 10);
     cout << "09-subtracting 10 years (faster): " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByOneDecade(Days);
     cout << "10-subtracting one decade: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXDecades(Days, 10);
     cout << "11-subtracting 10 decades: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByXDecadesFaster(Days, 10);
     cout << "12-subtracting 10 decades (faster): " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByCentury(Days);
     cout << "13-subtracting one century: " << Days.day << "/" << Days.month << "/" << Days.year << endl;
    Days = DecreaseDateByMillenium(Days);
     cout << "14-subtracting one millenium: " << Days.day << "/" << Days.month << "/" << Days.year << endl;

    return 0;
}