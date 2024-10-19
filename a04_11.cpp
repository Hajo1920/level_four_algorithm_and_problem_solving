#include <ios>
#include <iostream>
#include <limits>
#include <ctime>
using namespace std;

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


int Readyear(){
    int num;

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

int ReadMonth(){
    int num;

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

int ReadDay() {
    int num;
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

struct sDateMonthYear {
    short day;
    short month;
    short year;
};

sDateMonthYear GetDayOfRemainingDays(short dateOfyear, short year){
    sDateMonthYear DMY;

    short remainingDays = dateOfyear;
    DMY.year = year;
    DMY.month = 1;

    short dateOfMonth = 0;

    while(true){
        dateOfMonth = NumberOfDaysInMonth(year, DMY.month);
        if(remainingDays > dateOfMonth){
            remainingDays-=dateOfMonth;
            DMY.month++;
        }
        else {
            remainingDays = DMY.day;
            break;
        }
    }
    return DMY;
}



int main(){
    
    short day = ReadDay();
    short month = ReadMonth();
    short year = Readyear();

    short remainingDays = RemainingDaysOfYear(day, month, year);
    sDateMonthYear DMY;

    DMY = GetDayOfRemainingDays(remainingDays, year);


    cout << "Number of days from the begining of the year is: " << remainingDays << endl;

    cout << "Date for [" << remainingDays << "] is: " << DMY.day << "/" << DMY.month << "/" << DMY.year << endl;
    return 0;
}