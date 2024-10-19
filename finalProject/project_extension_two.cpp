/*
Project name: Bank System Extension 2
Project description: An extra extension for our previous bank system project.
Adding Adminstrational usage and security.
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



const string clientRecordFile = "UsersAccoutInformation.txt";
const string usersFile = "Users.txt";

enum enBankOperation {ShowClientList=1, AddNewClient=2, DeleteClientRecord=3, UpdateClientRecord=4, FindClientRecord=5, Transactions=6, ManageUsers=7, Logout=8};
enum enTransactionOperation {Deposit=1, Withdraw=2, TotalBalance=3, ExitToMainMenu=4};
enum enManageUsers {UserList=1, AddUser=2, DeleteUser=3, UpdateUser=4, FindUser=5, BackMainMenu=6};
enum enPermissionList {userAlpha=-1, allowShowClientList=1, allowAddNewClient=2, allowDeleteClient=4, allowUpdateClient=8, allowFindClient=16, allowTransactionAccess=32, allowManageUsersAccess=64 };

struct sClientInfo {
    string accountNumber;
    string pinCode;
    string clientName;
    string clientPhone;
    double clientBalance;
    bool markForDelete = false;
};

struct sUserInfo{
    string userName;
    string userPassword;
    short permission;
    bool markUserForDelete = false;
};


sUserInfo CurrentUser;

void  MainMenu(short &chooseOperation);

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

bool FindClientByAccountNumber(string AccountNumber, vector<sClientInfo> vClients, sClientInfo& Client){
    for (sClientInfo C : vClients){
        if (C.accountNumber == AccountNumber){
            Client = C;
            return true;
            }
        }
    return false;
}

bool CheckPermission(enPermissionList Permissions){
    if(CurrentUser.permission == enPermissionList::userAlpha){
        return true;
    }
    if((Permissions & CurrentUser.permission) == Permissions){
        return true;
    }
    return false;
}

void ShowAccessDenied(){
    system("clear");
    cout << "\n================ Access Denied ==================\n";
    cout << "\nYour Access permit is limited at this system\n";
    cout << "\nPlease contact this system Admins for extra information\n";
    cout << "\nPress any key to return to main menu.. \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    return;
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

    sUserInfo ConvertUserLinetoRecord(string& Line, string Seperator = "#//#") { 

    sUserInfo User; 
    vector<string> vUserData;     
    vUserData = Spliter(Line, Seperator);     
    User.userName = vUserData[0];  
    User.userPassword = vUserData[1];     
    User.permission =  stoi(vUserData[2]);  
    return User;
    
    } 

    string ConvertUserRecordToLine(sUserInfo& User, string Seperator = "#//#"){
    string stUserRecord = "";
    stUserRecord += User.userName + Seperator;
    stUserRecord += User.userPassword + Seperator;
    stUserRecord += to_string(User.permission);
    return stUserRecord;
}



bool FindUserByNameAndPassword(string name, string password, vector<sUserInfo>& vUsers, sUserInfo& User){
    for (sUserInfo usr : vUsers){
        if (usr.userName == name && usr.userPassword == password){
            User = usr;
            CurrentUser = User;
            return true;
            }
        }
    return false;
}

bool FindUserByName(string& name, vector<sUserInfo>& vUsers, sUserInfo& User){
    for (sUserInfo& usr : vUsers){
        if (usr.userName == name){
            User = usr;
            return true;
            }
        }
    return false;
}


vector<sUserInfo> LoadUserData(string file){

    fstream myFile;
    vector<sUserInfo> UserInfo;

    myFile.open(file, ios::in); // readmood

    if(myFile.is_open()){
        string line;
        sUserInfo User;
        while(getline(myFile, line)){
            if(!(line.empty())){
                User = ConvertUserLinetoRecord(line);
                UserInfo.push_back(User);
            }
        }
    }
    myFile.close();

    return UserInfo;
}

void PrintUserInfo(sUserInfo& User){
     cout << "\nThe following are details of the user\n";     
     cout << "\nUser Name : " << User.userName;    
     cout << "\nPassword   : " << User.userPassword;    
}

void PrintClientInfo(sClientInfo Client){
     cout << "\nThe following are details of the client\n";     
     cout << "\nAccout Number : " << Client.accountNumber;    
     cout << "\nPin Code     : " << Client.pinCode;     
     cout << "\nName         : " << Client.clientName;     
     cout << "\nPhone        : " << Client.clientPhone;     
     cout << "\nAccount Balance: " << Client.clientBalance;
     cout << endl;
    
}

vector<sClientInfo> AddFreshCleint(string clientRecordFile, vector<sClientInfo> &allClientData, string accountNumber){
    fstream clientsFile;
    clientsFile.open(clientRecordFile, ios::out);
    string RecordLine;
    if(clientsFile.is_open()){
        for(sClientInfo Client: allClientData){
          if(Client.markForDelete == false){
               RecordLine = ConvertRecordToLine(Client);
               clientsFile << "\n" << RecordLine << endl;
            
            }
     }
     clientsFile.close();

    }

    return allClientData;
    
}

sClientInfo ReadNewAccountInformation(string accountNumber){

    sClientInfo ClientInfo;

    ClientInfo.accountNumber = accountNumber;

    cout << "Enter PIN code: ";
    getline(cin >> ws,ClientInfo.pinCode);

    cout << "Enter New Name: ";
    getline(cin, ClientInfo.clientName);

    cout << "Enter new phone number: ";
    getline(cin, ClientInfo.clientPhone);

    cout << "Update new account balance: ";
    cin >> ClientInfo.clientBalance;

    return ClientInfo;
}

string ReadClientAccountNumber(){
       
    string accountNumber;

    cout << "Enter client account number: ";
    cin >> accountNumber;
    return accountNumber;
}


bool UpdateClientData(string accountNumber, vector<sClientInfo>& allClientData){
    char confirmDelete = 'n';
    sClientInfo Client;

    if(FindClientByAccountNumber(accountNumber, allClientData, Client)){
        PrintClientInfo(Client);

        cout << "Please confirm yes [y] or no [n] to update this client: ";
        cin >> confirmDelete;

        if(tolower(confirmDelete) == 'y'){
            for(sClientInfo &Client: allClientData){
                if(Client.accountNumber == accountNumber){
                    Client = ReadNewAccountInformation(accountNumber);
                    break;
                }
            }
            AddFreshCleint(clientRecordFile, allClientData, accountNumber);

            system("clear");
            cout << "Record updated successfuly." << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return true;
        }else{
            system("clear");
            cout << "Revert Action:No changes have been made" << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return false;
        }
    }
     
     return false; 
    
}


char DeleteConfirm(){
    char confrimation = 'n';

     cout << "Are you sure you want to delete this client record ? [y] yes [n] no: ";
     cin >> confrimation;

    return confrimation;
}

bool MarkClientForDeleteByAccountNumber(string& AccountNumber, vector <sClientInfo>& vClients){
    for (sClientInfo& C : vClients){
        if (C.accountNumber == AccountNumber){
            C.markForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClientInfo> SaveNewClientsDataToFile(string clientRecordFile, vector<sClientInfo> &allClientData){
    fstream clientsFile;
    clientsFile.open(clientRecordFile, ios::out);
    string RecordLine;
    if(clientsFile.is_open()){
        for(sClientInfo& Client: allClientData){
            if(Client.markForDelete == false){
               RecordLine = ConvertRecordToLine(Client);
               clientsFile << RecordLine << endl;
            }
     }
     clientsFile.close();
    }

    return allClientData;
    
}

bool DeleteClientByAccountNum(string accountNumber, vector<sClientInfo>& allClientData){
    

    char confirmDelete = 'n';
    sClientInfo Client;

    if(FindClientByAccountNumber(accountNumber, allClientData, Client)){
        PrintClientInfo(Client);

        cout << "Please confirm yes [y] or no [n] to delete the client: ";
        cin >> confirmDelete;

        if(tolower(confirmDelete) == 'y'){
            MarkClientForDeleteByAccountNumber(accountNumber, allClientData);
            SaveNewClientsDataToFile(clientRecordFile, allClientData);

            allClientData = LoadClientData(clientRecordFile);
            
            system("clear");
            cout << "Record Deleted successfuly." << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return true;
        }else{
            system("clear");
            cout << "No changes have been made" << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return false;
        }
    }
   
     return false; 
    
}

void TableTitle(vector<sClientInfo>& stClientData){
    
    cout << "\n";
    cout << setw(50) << right << "Client List ("<< stClientData.size() <<") Client(s)" << setw(50);
  
}

void TitlesHeader(){
   cout << "\n_______________________________________________________________";     
   cout << "_________________________________________\n" << endl;     
   cout << "| " << left << setw(15) << "Accout Number";     
   cout << "| " << left << setw(15) << "Pin Code";     
   cout << "| " << left << setw(40) << "Client Name";     
   cout << "| " << left << setw(12) << "Phone";     
   cout << "| " << left << setw(12) << "Balance";     
   cout << "\n______________________________________________________________";     
   cout << "_________________________________________\n" << endl;
}

void PrintClientRecord(sClientInfo Client) {     
    cout << "| " << setw(15) << left << Client.accountNumber;     
    cout << "| " << setw(15) << left << Client.pinCode;     
    cout << "| " << setw(40) << left << Client.clientName;    
    cout << "| " << setw(12) << left << Client.clientPhone;     
    cout << "| " << setw(12) << left << Client.clientBalance; } 

void RevealClientData(vector<sClientInfo>& stClientData){
  for(sClientInfo Client: stClientData){
    PrintClientRecord(Client);
    cout << endl;
  }
}
    


void ShowInfoTable(vector<sClientInfo> stClientData){
       
  TableTitle(stClientData);
  cout << endl;
  TitlesHeader();
  RevealClientData(stClientData);

  cout << "\nPress any key to return to main menu.. \n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cin.get();
  return;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName){
vector <sClientInfo> vClients;
fstream MyFile;
MyFile.open(FileName, ios::in);//read Mode
if (MyFile.is_open()){
    string Line;
    sClientInfo Client;
    while (getline(MyFile, Line)){
        Client = ConvertLinetoRecord(Line);
        if (Client.accountNumber == AccountNumber){
            MyFile.close();
            return true;
     }
    vClients.push_back(Client);
    }
    MyFile.close();
    }
    return false;
}

sClientInfo ReadNewClient(){
    sClientInfo Client;
    cout << "Enter Account Number? ";
// Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.accountNumber);
    while (ClientExistsByAccountNumber(Client.accountNumber, clientRecordFile)){
        cout << "\nClient with [" << Client.accountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.accountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.pinCode);
    cout << "Enter Name? ";
    getline(cin, Client.clientName);
    cout << "Enter Phone? ";
    getline(cin, Client.clientPhone);
    cout << "Enter clientBalance? ";
    cin >> Client.clientBalance;

    return Client;
}

void AddDataLineToFile(string FileName, string stDataLine){
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()){
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}


void AddClient(){

    sClientInfo Client;
    Client = ReadNewClient();
    AddDataLineToFile(clientRecordFile, ConvertRecordToLine(Client));
    
}

void AddNewClients(){
      
    char AddMore = 'Y';
    do{
    system("clear");
    cout << "Adding New Client:\n\n";
    AddClient();
    cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
    cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

string ReadUserName(){
    string username = "";
    cout << "\nEnter User Name: ";
    cin >> username;

    return username;
}

int ShowExitScreen(bool &mainContunity){
    system("clear");
    cout << setw(30) << right << "Thanks for using our bank system :) " << setw(30) << endl;
    cout << setw(35) << right << "Comeback any time " << setw(35) << endl;
    cout << setw(30) << right << "Press any key to exit the program... " << setw(30) << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    mainContunity = false;
    system("clear");
    return 0;
}

void ExitTransactionMainMenu(bool &transactionContunity){
    transactionContunity = false;
    return;
}

void ExitManageUsersMenu(bool &manageUsersContunity){
    manageUsersContunity = false;
    return;
}

void MainMenu(short &chooseOperation){
    
    cout << "\n======================================================================\n";
    cout << setw(40)<< " Main Menu " << setw(20);
    cout << "\n======================================================================\n";
    cout << setw(25)<< left << "[1] Show Client List." << setw(20)<< endl;
    cout << setw(25)<< left << "[2] Add New Client." << setw(20) << endl; 
    cout << setw(25)<< left << "[3] Delete Client Record." << setw(20) << endl;
    cout << setw(25)<< left << "[4] Update Client Record." << setw(20) << endl;
    cout << setw(25)<< left << "[5] Find Client Record" << setw(20) << endl;
    cout << setw(25)<< left << "[6] Transactions." << setw(20) << endl;
    cout << setw(25)<< left << "[7] Manage Users." << setw(20) << endl;
    cout << setw(25)<< left << "[8] Logout." << setw(20);
    cout << "\n======================================================================\n";
    do {
     cout << "Choose what operation do you want to do ? [1 to 8]: ";
    cin >> chooseOperation;
    while (cin.fail()){
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! please enter a number: ";
        cin >> chooseOperation;
    }
    }while (chooseOperation <= 0 || chooseOperation > 8);
}

void TransactionIntro(){
    system("clear");
    cout << "\n======================================================================\n";
    cout << setw(40)<< " Transaction Main Menu " << setw(20);
    cout << "\n======================================================================\n";
    cout << setw(25)<< left << "[1] Deposti" << setw(20)<< endl;
    cout << setw(25)<< left << "[2] Withdraw" << setw(20) << endl;
    cout << setw(25)<< left << "[3] Show TotalBalances" << setw(20) << endl;
    cout << setw(25)<< left << "[4] Back To Main Menu" << setw(20) << endl;
    cout << "\n======================================================================\n";
}

int ReadDepositAmount(){
    double deposit;
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

void DepositCredit(vector<sClientInfo>& allClientData){
    string accountNumber = ReadClientAccountNumber();
    char depositConfirm = 'n';
    double depositAmout = 0;

    for(sClientInfo&Client: allClientData){
        while(!FindClientByAccountNumber(accountNumber, allClientData, Client)){
            cout << "We did not found (" << accountNumber << ") in the list. please try again. \n";
            accountNumber = ReadClientAccountNumber();
        }
        
        if(Client.accountNumber == accountNumber){
            PrintClientInfo(Client);
            depositAmout = ReadDepositAmount();
            cout << "Are you sure you want to deposit " << depositAmout << "$ to " << Client.clientName << ",s Balance ? [y] or [n]: ";
            cin >> depositConfirm;

            if(tolower(depositConfirm) == 'y'){
            Client.clientBalance+= depositAmout;
            SaveNewClientsDataToFile(clientRecordFile, allClientData);
            system("clear");
            cout << "\nDeposit Operation Successful.\n";
            cout << "\nNow " << Client.clientName << ",s balance is " << Client.clientBalance << "\n";
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return;

            }else{
                cout << "\nDeposit Operation Unsuccessful.\n";
                cout << setw(30) << right << "Press any key to return to main menu.. " << setw(30) << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                return;
            }
            
        }
    }
    
}

int ReadWithdrawAmount(){
    double withdraw;
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

void WithDrawCredit(vector<sClientInfo>& allClientData){
    string accountNumber = ReadClientAccountNumber();
    char withdrawConfirm = 'n';
    double withdrawAmout = 0;

    for(sClientInfo&Client: allClientData){
        while(!FindClientByAccountNumber(accountNumber, allClientData, Client)){
            cout << "We did not found (" << accountNumber << ") in the list. please try again.\n";
            
            accountNumber = ReadClientAccountNumber();
        }
        if(Client.accountNumber == accountNumber){
            if(Client.clientBalance <= 0){
                cout << "Client have zero balance, withdrawal is impossible.\n";
                cout << setw(30) << right << "Press any key to return to main menu " << setw(30) << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                return;

            }

            PrintClientInfo(Client);

            withdrawAmout = ReadWithdrawAmount();
            while(Client.clientBalance < withdrawAmout){
                cout << "\nYou can't withdraw amount which is greater than client,s current balance !\n";
                cout << "\nPlease enter balance lower or equal to " << Client.clientBalance << "$\n";
                withdrawAmout = ReadWithdrawAmount();
            }
            
            cout << "Are you sure you want to withdraw " << withdrawAmout << "$ from " << Client.clientName << ",s Balance ?[y] or [n]: ";
            cin >> withdrawConfirm;

            if(tolower(withdrawConfirm) == 'y'){
            Client.clientBalance+= -withdrawAmout;
            SaveNewClientsDataToFile(clientRecordFile, allClientData);
            system("clear");
            cout << "\nWithdraw Operation Successful.\n";
            cout << "\nNow " << Client.clientName << ",s balance is " << Client.clientBalance << "\n";
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            return;

            }else{
                cout << "\nWithdraw Operation Unsuccessful.\n";
                cout << setw(30) << right << "Press any key to return to main menu.. " << setw(30) << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                return;
            }
            
        }
    }

}

void PrintClientRecordBalanceLine(sClientInfo Client){

    cout << "| " << setw(15) << left << Client.accountNumber;
    cout << "| " << setw(40) << left << Client.clientName;
    cout << "| " << setw(12) << left << Client.clientBalance;
}

void ShowTotalBalances(){
    vector <sClientInfo> vClients = LoadClientData(clientRecordFile);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ")Client(s).";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0;
    if (vClients.size() == 0){

    }else {
        for (sClientInfo Client : vClients){
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.clientBalance;
            cout << endl;
        }
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
    cout << setw(30) << right << "\n\nPress any key to return to main menu.. " << setw(30) << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    return;
}

}

void TransactionOperation(short transactionOperation, bool& transactionContunity,  vector<sClientInfo>& allClientData, short& chooseOperation){
    
    switch (transactionOperation)
    {
    case enTransactionOperation::Deposit:
        system("clear");
        DepositCredit(allClientData);
        break;
    case enTransactionOperation::Withdraw:
        system("clear");
        WithDrawCredit(allClientData);
        break;
    case enTransactionOperation::TotalBalance:
        system("clear");
        ShowTotalBalances();
        break;
    case enTransactionOperation::ExitToMainMenu:
        ExitTransactionMainMenu(transactionContunity);
        break;
    
    default:
        break;
    }
}

void TransactionMainMenu(short& transactionOperation, vector<sClientInfo> allClientData, short& chooseOperation){
       
    bool transactionContunity = true;
    while(transactionContunity){
        TransactionIntro();
        
            do {
     cout << "Choose what operation do you want to do ? [1 to 4]: ";
    cin >> transactionOperation;
    while (cin.fail()){
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! please enter a number: ";
        cin >> transactionOperation;
    }
    }while (transactionOperation <= 0 || transactionOperation > 4);

    TransactionOperation(transactionOperation, transactionContunity ,allClientData, chooseOperation);

    }
}

bool isUserValid(string name, string password, vector<sUserInfo>&vUsers, sUserInfo& UserInfo){
   if(FindUserByNameAndPassword(name, password, vUsers, UserInfo)){
    return true;
   }

   return false;
}

void ShowLoginPage(){
    system("clear");
    cout << "\n----------------------------------------------------------------\n";
    printf("               --[ Welcome to our Bank System ]--                ");
    cout << "\n----------------------------------------------------------------\n";
    cout << setw(10) << "Please Enter Your Credientals:" << setw(10) << endl;
}


void ManageUsersIntro(){
    system("clear");
    cout << "\n======================================================================\n";
    cout << setw(40)<< " Manage Users Main Menu " << setw(20);
    cout << "\n======================================================================\n";
    cout << setw(25)<< left << "[1] List All Users" << setw(20)<< endl;
    cout << setw(25)<< left << "[2] Add New User" << setw(20) << endl;
    cout << setw(25)<< left << "[3] Delete User" << setw(20) << endl;
    cout << setw(25)<< left << "[4] Update User" << setw(20) << endl;
    cout << setw(25)<< left << "[5] Find User" << setw(20) << endl;
    cout << setw(25)<< left << "[6] Back To Main Menu" << setw(20) << endl;
    cout << "\n======================================================================\n";
}

void PrintUserRecord(sUserInfo User){

    cout << "| " << setw(15) << left << User.userName;
    cout << "| " << setw(40) << left << User.userPassword;
    cout << "| " << setw(12) << left << User.permission;
    cout << endl;
}

void UsersList(){
    vector <sUserInfo> vUsers = LoadUserData(usersFile);
    cout << "\n\t\t\t\t Users List (" << vUsers.size() << ")Users(s).";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(40) << "Password";
    cout << "| " << left << setw(12) << "Permission";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

        for (sUserInfo& User : vUsers){
            PrintUserRecord(User);
        }
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << setw(30) << right << "\n\nPress any key to return to main menu.. " << setw(30) << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    ManageUsersIntro();
}

bool UserExistCheck(string userName, string FileName){
vector <sUserInfo> vUser;
fstream MyFile;
MyFile.open(FileName, ios::in);//read Mode
if (MyFile.is_open()){
    string Line;
    sUserInfo User;
    while (getline(MyFile, Line)){
        User = ConvertUserLinetoRecord(Line);
        if (User.userName == userName){
            MyFile.close();
            return true;
     }
    vUser.push_back(User);
    }
    MyFile.close();
    }
    return false;
}

int ReadAllowedPermissions(){
    char Answer = 'n';
    int permission = 0;

    cout << "\nDo you want to give access to: Show Client List [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowShowClientList;

    cout << "\nDo you want to give access to: Add New Client [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowAddNewClient;

    cout << "\nDo you want to give access to: Delete Client Record [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowDeleteClient;

    cout << "\nDo you want to give access to: Update Client Record [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowUpdateClient;
    cout << "\nDo you want to give access to: Find Client Record [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowFindClient;

    cout << "\nDo you want to give access to: Transactions [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowTransactionAccess;

     cout << "\nDo you want to give access to: Manage Users [y] or [n])? ";
    cin >> Answer;

    if(tolower(Answer) == 'y') permission+= enPermissionList::allowManageUsersAccess;

    return permission;
}


sUserInfo ReadNewUser(){
    sUserInfo User;
    char permission;
    cout << "Enter New User Name? ";
// Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.userName);
    while (UserExistCheck(User.userName, usersFile)){
        cout << "\nThis user name is not available , please enter another name? ";
        getline(cin >> ws, User.userName);
    }

    cout << "Enter Password? ";
    getline(cin, User.userPassword);
    cout << "Is all permissions allowed for this user ? (y) or (n) ";
    cin >> permission;

    if(tolower(permission) == 'y'){
        User.permission = -1;
    }
    else if(tolower(permission) == 'n'){
     User.permission = ReadAllowedPermissions();
    }
    else{
        cout << "Operation unsuccessful." << endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();;
        ManageUsersIntro();
    }
    return User;
}

void AddUserDataLineToFile(string FileName, string userData){
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()){
        MyFile << "\n" << userData;
        MyFile.close();
    }
}


void AddNewUser(){
    sUserInfo User;
    User = ReadNewUser();
    AddUserDataLineToFile(usersFile, ConvertUserRecordToLine(User));
    
}

void CreateNewUser(){
    char AddMore = 'Y';
    do{
    system("clear");
    cout << "Adding New User:\n\n";
    AddNewUser();
    cout << "\n User Added Successfully, do you want to add more users? Y/N? ";
    cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
    ManageUsersIntro();
}

vector<sUserInfo> AddFreshUser(string userfile, vector<sUserInfo> &allUserData, string name){
    fstream usersFile;
    usersFile.open(userfile, ios::out);
    string RecordLine;

    if(usersFile.is_open()){
        for(sUserInfo User: allUserData){
          if(User.markUserForDelete == false){
               RecordLine = ConvertUserRecordToLine(User);
               usersFile << "\n" << RecordLine << endl;
            
            }
     }
     usersFile.close();

    }

    return allUserData;
    
}

bool MarkUserForDeleteByName(string& name, vector<sUserInfo>& vUserInfo){
    for (sUserInfo& U : vUserInfo){
        if (U.userName == name){
            U.markUserForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sUserInfo> SaveNewUsersDataToFile(string userFile, vector<sUserInfo> &vUserInfo){
    fstream usersFile;
    usersFile.open(userFile, ios::out);  
    string RecordLine;
    if(usersFile.is_open()){
        for(sUserInfo& User: vUserInfo){
            if(User.markUserForDelete != true){
               RecordLine = ConvertUserRecordToLine(User);
               usersFile << RecordLine << endl;
            }
        }
        usersFile.close();
    }
    return vUserInfo;
}

bool DeleteUserByName(string& name, vector<sUserInfo>& vUsersInfo){
    
    char confirmDelete = 'n';
    sUserInfo User;

    if(FindUserByName(name, vUsersInfo, User)){

        if(User.permission == -1){
            cout << "Operation Denied !" << endl;
            cout << "you can't delete admin account." << endl;
            cout << "\nPress any key to try again.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("clear");
            ManageUsersIntro();
            return false;
            
        }

        PrintUserInfo(User);

        cout << "\nPlease confirm yes [y] or no [n] to delete this user\n";
        cin >> confirmDelete;

        if(tolower(confirmDelete) == 'y'){
            MarkUserForDeleteByName(name, vUsersInfo);
            SaveNewUsersDataToFile(usersFile, vUsersInfo);

            vUsersInfo = LoadUserData(usersFile);          
            system("clear");
            cout << "Record Deleted successfuly." << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("clear");
            ManageUsersIntro();
            return true;
        }else{
            system("clear");
            cout << "No changes have been made" << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("clear");
            ManageUsersIntro();
            return false;
        }
    }
   
     return false; 
    
}
  
bool UpdateUsersData(string name, vector<sUserInfo>& allUserData){
    char confirmDelete = 'n';
    sUserInfo User;

    if(FindUserByName(name, allUserData, User)){
        PrintUserInfo(User);

        cout << "Please confirm yes [y] or no [n] to update this client: ";
        cin >> confirmDelete;

        if(tolower(confirmDelete) == 'y'){
            for(sUserInfo &User: allUserData){
                if(User.userName == name){
                    User = ReadNewUser();
                    break;
                }
            }
            
            AddFreshUser(usersFile, allUserData, name);

            system("clear");
            cout << "Record updated successfuly." << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            ManageUsersIntro();
            
        }else{
            system("clear");
            cout << "Revert Action:No changes have been made" << endl;
            cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            ManageUsersIntro();
        }
    }
     
     return false; 
    
}




void ManageUserMenu(short manageUsersOperation, bool& manageUsersContunity, vector<sUserInfo>& vUserInfo, sUserInfo& UserInfo){
    string name;
     switch (manageUsersOperation)
    {
    case enManageUsers::UserList:
        system("clear");
        UsersList();
        break;
    case enManageUsers::AddUser:
        system("clear");
        CreateNewUser();
        break;
    case enManageUsers::DeleteUser:
        system("clear");
        name = ReadUserName();
        DeleteUserByName(name, vUserInfo);
        break;
    case enManageUsers::UpdateUser:
        system("clear");
        name = ReadUserName();
        UpdateUsersData(name, vUserInfo);
        break;

    case enManageUsers::FindUser:
       system("clear");
       name = ReadUserName();
       if(FindUserByName(name, vUserInfo, UserInfo)){
         PrintUserInfo(UserInfo);
        cout << "\nPress any key to return to main menu.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            ManageUsersIntro();
       }
        break;
    case enManageUsers::BackMainMenu:
        system("clear");
        ExitManageUsersMenu(manageUsersContunity);
       break;
    
    default:
        break;
    }
}

void ManageUsersMenuReader(vector<sUserInfo>& vUserInfo, sUserInfo& UserInfo, short chooseOperation){
      
    short choise;
    bool manageUserContinuty = true;
    ManageUsersIntro();
    cout << endl;
  while(manageUserContinuty){
     do
   {
     cout << "Choose what do you want to do: [1 - 6]: ";
     cin >> choise;
   } while (choise <= 0 || choise > 6);
   ManageUserMenu(choise, manageUserContinuty,vUserInfo, UserInfo);
  }

}



void LogIn(){
    vector<sUserInfo> vUsers = LoadUserData(usersFile);
    string userName = "";
    string password = "";
    sUserInfo UserInfo;
    enPermissionList Permissions;

   

    while(!isUserValid(userName, password, vUsers, UserInfo)){
        ShowLoginPage();

        cout << "\nEnter User Name: ";
        getline(cin >> ws, userName);

        cout << "\nEnter User Passcode: ";
        cin >> password;

        if(!isUserValid(userName, password, vUsers, UserInfo)){
            system("clear");
            cout << "\nIncorrect User name or Password !\n";
            cout << "\nPlease repeat again carefully.\n" << endl;
            cout << "\nPress any key to try again.. \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        }
    }
    
    bool mainContunity = true;
    sClientInfo FindClient;
    string accountNumber;
    while(mainContunity){
    system("clear");
    short chooseOperation;
    short transactionOperation;

    MainMenu(chooseOperation);
   
    vector<sClientInfo> allClientData = LoadClientData(clientRecordFile);

    switch (chooseOperation) {
    case enBankOperation::ShowClientList:
        system("clear");
        if(!CheckPermission(enPermissionList::allowShowClientList)){
        ShowAccessDenied();
        system("clear");
    } else if(CheckPermission(enPermissionList::allowShowClientList))
        ShowInfoTable(allClientData);
        break;
    case enBankOperation::AddNewClient:
        system("clear");
         if(!CheckPermission(enPermissionList::allowAddNewClient)){
        ShowAccessDenied();
        system("clear");
    } else if(CheckPermission(enPermissionList::allowAddNewClient))
        AddNewClients();
        break;
    case enBankOperation::DeleteClientRecord:
        system("clear");
        if(!CheckPermission(enPermissionList::allowDeleteClient)){
        ShowAccessDenied();
        system("clear");
    } else if(CheckPermission(enPermissionList::allowDeleteClient))
        accountNumber = ReadClientAccountNumber();
        DeleteClientByAccountNum(accountNumber,allClientData);
        break;
    case enBankOperation::UpdateClientRecord:
        system("clear");
         if(!CheckPermission(enPermissionList::allowUpdateClient)){
        ShowAccessDenied();
        system("clear");
  
    } else if(CheckPermission(enPermissionList::allowUpdateClient))
        accountNumber = ReadClientAccountNumber();
        UpdateClientData(accountNumber,allClientData);
        break;
    case enBankOperation::FindClientRecord:
        system("clear");
         if(!CheckPermission(enPermissionList::allowFindClient)){
        ShowAccessDenied();
        system("clear");

    } else if(CheckPermission(enPermissionList::allowFindClient))
        accountNumber = ReadClientAccountNumber();
        if(FindClientByAccountNumber(accountNumber, allClientData, FindClient)){
            PrintClientInfo(FindClient);
            cout << setw(30) << right << "Press any key to return to main menu " << setw(30) << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();

        }
        
        break;
    case enBankOperation::Transactions:
        system("clear");
         if(!CheckPermission(enPermissionList::allowTransactionAccess)){
        ShowAccessDenied();
        system("clear");
        } else if(CheckPermission(enPermissionList::allowTransactionAccess))
        TransactionMainMenu(transactionOperation, allClientData,chooseOperation);
        break;

    case enBankOperation::ManageUsers:
        system("clear");
         if(!CheckPermission(enPermissionList::allowManageUsersAccess)){
        ShowAccessDenied();
        system("clear");
        
    } else if(CheckPermission(enPermissionList::allowManageUsersAccess))
        ManageUsersMenuReader(vUsers, UserInfo, chooseOperation);
        break;
    case enBankOperation::Logout:
        system("clear");
        LogIn();
        break;
    default:
        break;

    }
    }
}

int main(){
    LogIn();
    return 0;
}