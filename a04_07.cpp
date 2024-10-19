#include <ios>
#include <iostream>
#include <limits>
#include <ctime>
using namespace std;

int GetDay(short day, short month, short year){
    short A ,Y ,M;

    A = (14-month) /12;
    Y = year - A;
    M = month + (12*A)-2;

    return (day + Y + (Y/4)-(Y/100)+(Y/400)+((31*M)/12))%7;
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


int main(){
    
    const string arrDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday","Friday","Saturday"};
    int dayOrder = 0;
    int year = Readyear();
    int month = ReadMonth();
    int day = ReadDay();

    short dateindex = GetDay(day, month, year);

    cout << "Date: " << day << "/" << month << "/" << year << endl;
    cout << "Day order: " << dateindex << endl;
    cout << "Day name: " << arrDays[dateindex] << endl;
    
    return 0;
}