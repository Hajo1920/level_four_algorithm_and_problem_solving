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
    if(year % 400 == 0){
        return true;
    }

    else if(year % 100 == 0){
        return false; 
    }
    else if(year % 4 == 0){
        return true;
    }

    return false;
}

int main(){

    int year = Readyear();

    if(isLeapYear(year)){
        cout << "Yes year " << year << " is a Leap year." << endl;
    }
    else cout << "No year " << year << " is not a Leap year." << endl;
    
    return 0;
}