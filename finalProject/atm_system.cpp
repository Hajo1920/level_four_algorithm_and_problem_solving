/*
Project name: Bank System Extension 2
Project description: A separate ATM-system That allow users to do transactions using thier account.
Developer: Ahmed Osman
Credit: Dr.Mohammed Abu Hadhoud. @ Programming Advices 
*/

#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>

using namespace std;
void Login();
void MainMenu(short &chooseOperation);

void LogIn();

const string clientRecordFile = "UsersAccoutInformation.txt";
enum enAtmMenus {Quick=1, Normal=2, Deposit=3, CheckBalance=4, Logout=5};
enum enQuickWithDrawList {Twenty=20, Fifty=50, Hundred=100, HundredFifty=150, TwoHundred=200, FiveHundred=500, Thousand=1000, FiveThousand=5000};

struct sClientInfo {
    string accountNumber;
    string pinCode;
    string clientName;
    string clientPhone;
    double clientBalance;
    bool markForDelete = false;
};

void SystemManiMenu(sClientInfo& ClientInfo, vector<sClientInfo>&vClients);



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

bool FindClientByAccountNumber(string& AccountNumber, vector<sClientInfo>& vClients, sClientInfo& Client){
    for (sClientInfo C : vClients){
        if (C.accountNumber == AccountNumber){
            Client = C;
            return true;
            }
        }
    return false;
}

bool FindClientByNameAndpinCode(string accountNum, string pinCode, vector<sClientInfo>& vClients, sClientInfo& Client){
    for (sClientInfo client : vClients){
        if (client.accountNumber == accountNum && client.pinCode == pinCode){
            Client = client;
            return true;
            }
        }
    return false;
}

sClientInfo ConvertLinetoRecord(string Line, string Seperator = "#//#") { 

    sClientInfo Client; 
    vector<string> vClientData;     
    vClientData = Spliter(Line, Seperator);     
    Client.accountNumber = vClientData[0];     
    Client.pinCode = vClientData[1];     
    Client.clientName = vClientData[2];     
    Client.clientPhone = vClientData[3];     
    Client.clientBalance = stod(vClientData[4]); //cast string to doublereturn Client; 

    return Client;
    
    } 

string ConvertRecordToLine(sClientInfo Client, string Seperator = "#//#"){
    string stClientRecord = "";
    stClientRecord += Client.accountNumber + Seperator;
    stClientRecord += Client.pinCode + Seperator;
    stClientRecord += Client.clientName + Seperator;
    stClientRecord += Client.clientPhone + Seperator;
    stClientRecord += to_string(Client.clientBalance);
    return stClientRecord;
}

vector<sClientInfo> LoadClientData(string file){

    fstream myFile;
    vector<sClientInfo> ClientInfo;

    myFile.open(file, ios::in); // readmood

    if(myFile.is_open()){
        string line;
        sClientInfo Client;
        while(getline(myFile, line)){
            if(!(line.empty())){
                Client = ConvertLinetoRecord(line);
                ClientInfo.push_back(Client);
            }
        }
    }
    myFile.close();

    return ClientInfo;
}


bool FindClientByName(string name, vector<sClientInfo>& vClients, sClientInfo& Client){
    for (sClientInfo client : vClients){
        if (client.accountNumber == name){
            Client = client;
            return true;
            }
        }
    return false;
}

void WelcomeUser(sClientInfo& Client){

    cout << endl;
    cout << setw(30)<< "_____________ Mis/Mr " << Client.clientName << " _____________"<< setw(20);
    cout << endl;
}

void MainMenuScreen(sClientInfo& Client){
    system("clear");
    WelcomeUser(Client);
    cout << "\n======================================================================\n";
    cout << setw(40)<< " ATM Main Menu " << setw(20);
    cout << "\n======================================================================\n";
    cout << setw(25)<< left << "[1] Quick Withdraw" << setw(20)<< endl;
    cout << setw(25)<< left << "[2] Normal Withdraw" << setw(20) << endl;
    cout << setw(25)<< left << "[3] Deposit" << setw(20) << endl;
    cout << setw(25)<< left << "[4] Check Balance" << setw(20) << endl;
    cout << setw(25)<< left << "[5] Logout" << setw(20) << endl;
    cout << "\n======================================================================\n";
}

void ChooseOperation(short& chooseOperation){

      do {
     cout << "Choose what operation do you want to do ? [1 to 5]: ";
    cin >> chooseOperation;
    while (cin.fail()){
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! please enter a number: ";
        cin >> chooseOperation;
    }
    }while (chooseOperation <= 0 || chooseOperation > 5);
}


void ShowLoginPage(){
    system("clear");
    cout << "\n----------------------------------------------------------------\n";
    printf("               --[ Welcome to ATM Banking Service ]--                ");
    cout << "\n----------------------------------------------------------------\n";
    cout << setw(10) << "Please Enter Your Account Credientals:" << setw(10);
}

vector<sClientInfo> AddFreshCleint(string clientRecordFile, vector<sClientInfo> &allClientData, string& accountNumber){
    fstream clientsFile;
    clientsFile.open(clientRecordFile, ios::out);
    string RecordLine;
    if(clientsFile.is_open()){
        for(sClientInfo Client: allClientData){
          if(Client.markForDelete == false){
               RecordLine = ConvertRecordToLine(Client);
               clientsFile << RecordLine << endl;
            
            }
     }
     clientsFile.close();

    }

    return allClientData;
    
}

void UpdateClientData(string& accountNumber, vector<sClientInfo>& allClientData, sClientInfo& NewClientInfo){
    char confirmDelete = 'n';
    sClientInfo Client;

    if(FindClientByAccountNumber(accountNumber, allClientData, Client)){

        for(sClientInfo &Client: allClientData){
                if(Client.accountNumber == accountNumber){
                    Client = NewClientInfo;
                    break;
                }
            }
        AddFreshCleint(clientRecordFile, allClientData, accountNumber);

    }
     
    
}

bool isClientValid(string name, string pinCode, vector<sClientInfo>&vClients, sClientInfo& ClientInfo){
   if(FindClientByNameAndpinCode(name, pinCode, vClients, ClientInfo)){
    return true;
   }

   return false;
}

void QuickWithDrawMenu(){
    cout << "\n==================================================\n";
     printf("       - Quick Withdraw Menu -                   ");
    cout << "\n==================================================\n";
    cout << "\n\n";
    printf("[+]  20$          |          [+]  50$");
    cout << "\n\n";
    printf("[+]  100$         |          [+]  150$");
    cout << "\n\n";
    printf("[+]  200$         |          [+]  500$");
    cout << "\n\n";
    printf("[+]  1000$        |          [+]  5000$");
    cout << "\n\n";
    cout << "\n==================================================\n";
}

short ReadQuickWithdrawChooise(sClientInfo& ClientInfo){
    vector<short> validInputs = {20,50,100,150,200,500,1000,5000};
    short choise;
    bool validInput = false;
    cout << "\nNote:Your Current Balance is " << ClientInfo.clientBalance << endl;
    do {
        cout << "\nPlease choose one from available quick withdraws listed above ? ";
        cin >> choise;
        while (cin.fail()){
        
           cin.clear();
           cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           cout << "Invalid input! please enter a number only ";
           cin >> choise;
    }
    for(short &input: validInputs){
        if(choise == input){
            validInput = true;
            break;
        }
    }
    }while (!validInput);

    return choise;
}

void QuickWithdrawOperation(short choosedMoney, sClientInfo& ClientInfo, vector<sClientInfo>& allClientData){
    if(choosedMoney > ClientInfo.clientBalance){
        system("clear");
        cout << "\nYour current balance is not sufficent for amount of withdrawal you requested\n" << endl;
        cout << "\nPress any key to return to main menu.. \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        SystemManiMenu(ClientInfo, allClientData);
    }

    switch (choosedMoney)
    {
    case  enQuickWithDrawList::Twenty:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::Fifty:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::Hundred:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::HundredFifty:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::TwoHundred:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::FiveHundred:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::Thousand:
        ClientInfo.clientBalance-=choosedMoney;
        break;

    case  enQuickWithDrawList::FiveThousand:
        ClientInfo.clientBalance-=choosedMoney;
        break;
    
    default:
        break;
    }
}

void QuickWithdraw(sClientInfo& ClientInfo, vector<sClientInfo>& allClientData){
    short choosedMoney = 0;
    char withdrawAgain = 'n';
    QuickWithDrawMenu();

    choosedMoney = ReadQuickWithdrawChooise(ClientInfo);

    QuickWithdrawOperation(choosedMoney, ClientInfo, allClientData);
    UpdateClientData(ClientInfo.accountNumber, allClientData, ClientInfo);
    system("clear");
    cout << "\nOperation Successfull!\n";
    cout << "\nNow Your Current Balance is: " << ClientInfo.clientBalance << endl;
    cout << "\nDo you want to withdraw again [Y] or [N] ? \n";
    cin >> withdrawAgain;
    if(tolower(withdrawAgain) == 'y'){
        QuickWithdraw(ClientInfo, allClientData);
    }
     SystemManiMenu(ClientInfo, allClientData);
    
}
int ReadWithdrawAmount(){
    int withdraw;
     do {
     cout << "How much amount do you want to withdraw: ";
     cin >> withdraw;
    while (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! please enter a number: ";
        cin >> withdraw;
    }
    }while (withdraw <= 0 || withdraw > 50000);

    return withdraw;
}

int ReadDepositAmount(){
    int deposit;
     do {
     cout << "How much amount do you want to deposit [min:1$ max:50,000$]: ";
     cin >> deposit;
    while (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! please enter a number: ";
        cin >> deposit;
    }
    }while (deposit <= 0 || deposit > 50000);

    return deposit;
}

// vector<sClientInfo> SaveNewClientsDataToFile(string clientRecordFile, vector<sClientInfo> &allClientData){
//     fstream clientsFile;
//     clientsFile.open(clientRecordFile, ios::out);
//     string RecordLine;
//     if(clientsFile.is_open()){
//         for(sClientInfo& Client: allClientData){
//             if(Client.markForDelete == false){
//                RecordLine = ConvertRecordToLine(Client);
//                clientsFile << RecordLine << endl;
//             }
//      }
//      clientsFile.close();
//     }

//     return allClientData;
    
// }
void DepositCredit(vector<sClientInfo>& allClientData, sClientInfo& ClientInfo){
    
    char depositConfirm = 'n';
    double depositAmout = 0;

    depositAmout = ReadDepositAmount();
    cout << "Are you sure you want to deposit " << depositAmout << "$ to " << ClientInfo.clientName << ",s Balance ? [y] or [n]: ";
    cin >> depositConfirm;
    if(tolower(depositConfirm) == 'y'){
    ClientInfo.clientBalance+= depositAmout;
    UpdateClientData(ClientInfo.accountNumber, allClientData, ClientInfo);
    system("clear");
    cout << "\nDeposit Operation Successful.\n";
    cout << "\nNow " << ClientInfo.clientName << ",s balance is " << ClientInfo.clientBalance << "\n";
    cout << "\nPress any key to return to main menu.. \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    SystemManiMenu(ClientInfo, allClientData);

            }
    
}


void Normalwithdraw(sClientInfo& ClientInfo, vector<sClientInfo>& allClientData){
    int amount = ReadWithdrawAmount();

    if(amount < 20 && amount % 5 != 0){
        cout << "\n Invalid amount\n";
        amount = ReadDepositAmount();
    }

    if(ClientInfo.clientBalance < amount){
        system("clear");
        cout << "\nYour current balance is not sufficent for amount of withdrawal you requested\n" << endl;
        cout << "\nPress any key to return to main menu.. \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        SystemManiMenu(ClientInfo, allClientData);
    }
        ClientInfo.clientBalance -= amount;
        UpdateClientData(ClientInfo.accountNumber, allClientData, ClientInfo);
        system("clear");
        cout << "\nWithdraw operation successful!\n" << endl;
        cout << "\nPress any key to return to main menu.. \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        SystemManiMenu(ClientInfo, allClientData);
       

    
}

void Checkbalance(sClientInfo& ClientInfo, vector<sClientInfo>& allClientData){
    system("clear");
    cout << "\nYour current balance is: " << ClientInfo.clientBalance << endl;
    cout << "\nPress any key to return to main menu.. \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    SystemManiMenu(ClientInfo, allClientData);
}

void SystemManiMenu(sClientInfo& ClientInfo, vector<sClientInfo>& allClientData){
    short chooseOperation;
    MainMenuScreen(ClientInfo);
    ChooseOperation(chooseOperation);

         switch (chooseOperation) {
    case enAtmMenus::Quick:
        system("clear");
        QuickWithdraw(ClientInfo, allClientData);
        break;
    case enAtmMenus::Normal:
        system("clear");
        Normalwithdraw(ClientInfo, allClientData);
        break;
    case enAtmMenus::Deposit:
        system("clear");
       DepositCredit(allClientData, ClientInfo);
    
        break;

    case enAtmMenus::CheckBalance:
        system("clear");
        Checkbalance(ClientInfo, allClientData);
        break;

    case enAtmMenus::Logout:
        system("clear");
        LogIn();
        break;
    default:
        break;
    }
    
}


void LogIn(){
    vector<sClientInfo> vClients = LoadClientData(clientRecordFile);
    string accountNumber = "";
    string pinCode = "";
    sClientInfo ClientInfo;

    while(!isClientValid(accountNumber, pinCode, vClients, ClientInfo)){
        ShowLoginPage();

        cout << "\nEnter Account Number: ";
        getline(cin >> ws, accountNumber);

        cout << "\nEnter Account Pincode: ";
        cin >> pinCode;

        if(!isClientValid(accountNumber, pinCode, vClients, ClientInfo)){
            system("clear");
            cout << "\nIncorrect Account Number or pinCode !\n";
            cout << "\nPlease repeat again carefully.\n" << endl;
            cout << "\nPress any key to try again.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        }
    }
    SystemManiMenu(ClientInfo, vClients);

    
}

int main(){
    LogIn();
    return 0;
}