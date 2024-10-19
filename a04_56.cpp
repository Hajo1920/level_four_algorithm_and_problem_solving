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

stDay ReadFullDate(){
    stDay Days;

    Days.day = ReadDay();
    Days.month = ReadMonth();
    Days.year = Readyear();

    return Days;
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

int main(){
   
    cout << "Enter Date one: " << endl;
    stDay DayOne = ReadFullDate();
    cout << "\nEnter Date two: " << endl;
    stDay DayTwo = ReadFullDate();

    if(isDateOneAfterDatetwo(DayOne, DayTwo)) cout << "\nYes DateOne is After DateTwo\n";
    else cout << "No DateOne is Not After DateTwo\n";
    return 0;
}
