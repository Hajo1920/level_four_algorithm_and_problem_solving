#include <ios>
#include <iostream>
#include <limits>
using namespace std;

short Readyear(){
    short num;

    do {
    cout << "Enter year to check how much days,hours, minutes and seconds are in a year: ";
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

bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInYear(short year){

    return isLeapYear(year) ?  366 : 365; 
}

short NumberOfHoursInYear(short year){
    
    return NumberOfDaysInYear(year) * 24;
}

short NumOfMinutesInYear(short year){
    
    return NumberOfHoursInYear(year) * 60;
}

short NumOfSecondsInYear(short year){
  

    return NumOfMinutesInYear(year) * 60;
}

int main(){
    short year = Readyear();
    bool isLeap = isLeapYear(year);
    
    cout << "Number of Days in year [" << year << "] is " << NumberOfDaysInYear(year) << endl;
    cout << "Number of Hours in year [" << year << "] is " << NumberOfHoursInYear(year) << endl;
    cout << "Number of Minutes in year [" << year << "] is " << NumOfMinutesInYear(year) << endl;
    cout << "Number of Seconds in year [" << year << "] is " << NumOfSecondsInYear(year) << endl;
    return 0;
}