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

int ReadAddDay() {
    int num;
    do {
    cout << "Enter days you want to add: ";
    cin >> num;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter integer type only!";
        cin >> num;
    }

    } while (num <= 0);

    return num;
}

struct sDateMonthYear {
    short day;
    short month;
    short year;
};

sDateMonthYear ReadFullDate(){
    sDateMonthYear DMY;

    DMY.day = ReadDay();
    DMY.month = ReadMonth();
    DMY.year = Readyear();

    return DMY;
}

sDateMonthYear GetDayOfAddedDays(sDateMonthYear DMY, int addedDays){
    
    int remainingDays = addedDays + RemainingDaysOfYear(DMY.day, DMY.month, DMY.year);
    DMY.month = 1;
    short monthDays = 0;
    while(true){
        monthDays = NumberOfDaysInMonth(DMY.year, DMY.month);
        if(remainingDays > monthDays){
            remainingDays-= monthDays;
            DMY.month++;
             if(DMY.month > 12){
            DMY.month = 1;
            DMY.year++;
        }
        }
       
        else{
            DMY.day = remainingDays;
            break;
        }
    }
    return DMY;
}

int main(){

    sDateMonthYear DMY  = ReadFullDate();
    int addedDays = ReadAddDay();

    DMY = GetDayOfAddedDays(DMY, addedDays);

    cout << "Date for [" << addedDays << "] is: " << DMY.day << "/" << DMY.month << "/" << DMY.year << endl;
    return 0;
}