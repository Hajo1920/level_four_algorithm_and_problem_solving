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

enCompare CompareBeforeEqualAfter(stDay DayOne, stDay DayTwo){

    if(isDateOneBeforeDatetwo(DayOne, DayTwo)){
        return enCompare::Before;
    }
    if(isDateOneEqualsDatetwo(DayOne, DayTwo)){
        return enCompare::Equal;
    }
        return enCompare::After;
}

bool isPeriodsOverlap(stPeriod periodOne, stPeriod periodTwo){

    if(CompareBeforeEqualAfter(periodTwo.EndDate, periodOne.StartDate) == enCompare::Before || CompareBeforeEqualAfter(periodTwo.StartDate , periodOne.EndDate) ==  enCompare::After){
        return false;
    }

    return true;
}

int main(){

    

    cout << "\nPeriod one: " << endl;
    stPeriod PeriodOne = ReadPeriods();

    cout << "\nPreiod two: " << endl;
    stPeriod PeriodTwo = ReadPeriods();
    

    if(isPeriodsOverlap(PeriodOne, PeriodTwo)){
        cout << "Yes Periods overlap" << endl;
    }else cout << "No Periods does not overlap" << endl;

    return 0;
}
