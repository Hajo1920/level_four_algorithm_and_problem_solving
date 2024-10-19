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


bool isDateInBetweenPeriod(stPeriod period, stDay Day){
    return isDateOneBeforeDatetwo(period.StartDate, Day) && isDateOneAfterDatetwo(period.EndDate, Day);
}

int main(){

    cout << "\nPeriod one: " << endl;
    stPeriod period = ReadPeriods();

    cout << "\nEnter Date: " << endl;
    stDay Day = ReadFullDate();
    if(isDateInBetweenPeriod(period, Day)){
        cout << "Yes date is with in a period" << endl;
    }else cout << "No date is not with in a period" << endl;

    return 0;
}
