#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <ctime>

using namespace std;

string GetMonthName(int month){
    const string arrMonths[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    return arrMonths[month-1];
}

int GetDay(short day, short month, short year){
    short A ,Y ,M;

    A = (14-month) /12;
    Y = year - A;
    M = month + (12*A)-2;

    return (day + Y + (Y/4)-(Y/100)+(Y/400)+((31*M)/12))%7;
}


bool isLeapYear(short year){
 
   return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

short NumberOfDaysInMonth(short year, short month){

    short daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (month == 2) ? (isLeapYear(year) ? 29:28) : daysInMonth[month-1];
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

void PrintMonthCalendar(short year, short month){
    int current = GetDay(1, month, year);
    int numberOfDays = NumberOfDaysInMonth(year, month);

    cout << endl << " \n===============[-" << GetMonthName(month) << "-]=============== \n" << endl;
    cout << "   Sun  Mon  Tue  Wed  Thu  Fri  Sat \n" << endl;

    unsigned short i;
    for (i = 0; i < current; i++)
        cout << "     ";

    for (int j = 1; j <= numberOfDays; j++) {
        (j <= 9) ? cout  << setw(4) << "0" << j :cout << setw(5) << j;
        if (++i == 7) {
            i = 0;
            cout << "\n\n";
        }
    }
    cout << "\n ===================================== \n" << endl;
    
}

void PrintYearCalendar(short year){

    cout << "\n ------------------------------------- \n";
    printf("        C a l e n d a r -%d       ", year);
    cout << "\n ------------------------------------- \n";
    for(short m = 1; m <= 12; m++){
        PrintMonthCalendar(year, m);
        cout << "\n\n";
    }

}


int main(){

    short year = Readyear();

    PrintYearCalendar(year);

    return 0;
}