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

bool isDateOneBeforeDatetwo(short day1, short month1, short year1, short day2, short month2, short year2){
  return year1 < year2 ? true : (year1 == year2 ? (month1 < month2 ? true: (month1 == month2 ? (day1 < day2) : false)):false);
}


int main(){
    
    short day = ReadDay();
    short month = ReadMonth();
    short year = Readyear();

    short day2 = ReadDay();
    short month2 = ReadMonth();
    short year2 = Readyear();

    if(isDateOneBeforeDatetwo(day,month,year, day2,month2,year2)){
        cout << "Yes Day1 is less than Day2" << endl;
    }else{
        cout << "No Day1 is greater than Day2 " << endl;
    }



    return 0;
}