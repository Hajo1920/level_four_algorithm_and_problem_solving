#include <ios>
#include <iostream>
#include <limits>
using namespace std;

int ReadNumber(){
    int num;

    do {
    cout << "Enter any posotive number to read it as text: ";
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

string ConvertNumberToText(int number){
   if(number == 0){
    return "";
   } 

   if(number >= 1 && number <= 19){
        string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven","Eight",
        "Nine", "Ten", "Eleven", "Twelve", "Therteen", "Fourteen", "Fifteen", "Sixteen",
       "Seventeen", "Eighteen", "Ninteen"};

       return arr[number] + " ";
   }
   
   if(number >= 20 && number <= 99){
    string arr[] = {"","", "Twenty", "Thirty", "Fourty", "Fifety","Sixty", "Seventy", "Eighty", "Ninety"};
    return arr[number / 10] + " " + ConvertNumberToText(number % 10);
   } 

   if(number >= 100 && number <= 199){
    return "One Hundred " + ConvertNumberToText(number % 100);
   }

   if(number >= 200 && number <= 999){
    return ConvertNumberToText(number /100) + "Hundreds " + ConvertNumberToText(number % 100);
   }

   if(number >= 1000 &&  number <= 1999){
    return "One Thousand " + ConvertNumberToText(number % 1000);
   }

   if(number >= 2000 && number < 999999){
    return ConvertNumberToText(number / 1000) + "Thousands " + ConvertNumberToText(number % 1000);
   }

   if(number >= 1000000 && number <= 1999999){
    return "One Million " + ConvertNumberToText(number % 1000000);
   }

   if(number >= 2000000 && number <= 999999999){
    return ConvertNumberToText(number / 1000000) + "Million " + ConvertNumberToText(number % 1000000);
   }

   if(number >= 1000000000 && number <= 1999999999){
    return "One Billion " + ConvertNumberToText(number % 1000000000);
   }

   else if(number >= 2000000000) {
    return ConvertNumberToText(number / 1000000000) + "Billion " + ConvertNumberToText(number % 1000000000);
   }

   return "Stack overflow number.";

   }


int main(){

    int number = ReadNumber();
    cout << ConvertNumberToText(number) << endl;
    return 0;
}