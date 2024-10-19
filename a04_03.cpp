#include <ios>
#include <iostream>
#include <limits>
using namespace std;

int Readyear(){
    int num;

    do {
    cout << "Enter year to check (Leap Year): ";
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

bool isLeapYear(int year){
    // making it one line of code
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main(){
    int year = Readyear();
    isLeapYear(year) ? cout << "Yes year " << year << " is a Leap year\n":cout << "No year " << year << " is not a Leap year\n";
    return 0;
}