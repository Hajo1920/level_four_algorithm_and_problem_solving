#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ReadStringDate(){
    string day = "";

    cout << "\nPlease enter date: [dd/mm/yyyy]-> ";
    cin >> day;

    return day;
}

vector<string> Spliter(string str ,string delimeter){
    vector<string> vWords;
    string word;
    short pos = 0;

    while((pos = str.find(delimeter)) != std::string::npos){
        word = str.substr(0, pos);

        if(!word.empty()){
            vWords.push_back(word);
        }

        str.erase(0, pos + delimeter.length());
    }
    if(!str.empty()){
        vWords.push_back(str);
    }

    return vWords;
}

struct stDate {
    short day, month, year;
};

stDate StringToDate(vector<string>& date){
    stDate Day;

    Day.day = stoi(date.at(0));
    Day.month = stoi(date.at(1));
    Day.year = stoi(date.at(2));

    return Day;
}

string DateToString(stDate Day, string seperator){
    string strDate = "";
    strDate = to_string(Day.day)+seperator;
    strDate += to_string(Day.month)+seperator;
    strDate += to_string(Day.year);
    return strDate;
}

int main(){
    string day =  ReadStringDate();
    vector<string> data = Spliter(day, "/");

    stDate Day = StringToDate(data);

    cout << "Day: " << Day.day << endl;
    cout << "Month: "<< Day.month << endl;
    cout << "Year: " << Day.year << endl;

    cout << "\nYou Entered: " << DateToString(Day, "/") << endl;


    return 0;
}