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
    Day.year =stoi(date.at(2));

    return Day;
}

string DateToString(stDate Day, string seperator){
    string strDate = "";
    strDate = to_string(Day.day)+seperator;
    strDate += to_string(Day.month)+seperator;
    strDate += to_string(Day.year);
    return strDate;
}

string ReplaceWordInString(string S1, string StringToReplace, string RepalceTo) { 
    short pos = S1.find(StringToReplace); 
    while (pos != std::string::npos){ 
        S1=S1.replace(pos, StringToReplace.length(), RepalceTo);         
        pos = S1.find(StringToReplace);
        //find next   
         } 
         return S1; }

string FormateDate(stDate Date, string defaultdateFormat="dd/mm/yyyy"){
    string formatedDate = "";

    formatedDate = ReplaceWordInString(defaultdateFormat, "dd", to_string(Date.day));
    formatedDate = ReplaceWordInString(formatedDate, "mm", to_string(Date.month));
    formatedDate = ReplaceWordInString(formatedDate, "yyyy", to_string(Date.year));

    return formatedDate;
}

int main(){
    string day =  ReadStringDate();
    vector<string> data = Spliter(day, "/");

    stDate Day = StringToDate(data);

    cout <<"\n"<< FormateDate(Day) <<"\n";     
    cout <<"\n"<< FormateDate(Day, "yyyy/dd/mm") <<"\n";     
    cout <<"\n"<< FormateDate(Day, "mm/dd/yyyy") <<"\n";     
    cout <<"\n"<< FormateDate(Day, "mm-dd-yyyy") <<"\n";     
    cout <<"\n"<< FormateDate(Day, "dd-mm-yyyy") <<"\n";     
    cout <<"\n"<< FormateDate(Day, "Day:dd, Month:mm, Year:yyyy") <<"\n";

    return 0;
}