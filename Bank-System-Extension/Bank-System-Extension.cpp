#include <iostream>
#include<iomanip>
#include"ReadInputsLib.h";
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

void BankSystem();
void ManageUsers();

const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

struct stBankClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool ToDelete = false;
	bool ToUpdate = false;
};

struct stUser {
	string Username;
	string Password;
	short Permissions = 0;
	bool ToDelete = false;
	bool ToUpdate = false;
};

stUser CurrentUser;

enum enPermissions {

	All = -1, ListClients = 1, AddClient = 2, DeleteClient = 4,
	UpdateClient = 8, FindClient = 16, PerformTransactions = 32,
	ManageTheUsers = 64
};

short ReadPermissions() {
	char Accept = 'n';
	short Permission = 0;

	Accept = ReadInput::ReadCharacter("Do you want to give him all permissions? Y/N");

	cout << endl;
	if (toupper(Accept) == 'Y') return -1;
	else {
		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to show clients? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::ListClients;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to add clients? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::AddClient;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to delete clients? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::DeleteClient;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to update clients? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::UpdateClient;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to find clients? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::FindClient;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to performtransactions? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::PerformTransactions;

		Accept = ReadInput::ReadCharacter("Do you want to give him permissions to manage users? Y/N");
		if (toupper(Accept) == 'Y') Permission += enPermissions::ManageTheUsers;

	}
	return Permission;
}

stBankClient ReadClientData() {
	stBankClient Client1;

	Client1.AccountNumber = ReadInput::ReadString("Please enter Account Number");
	Client1.PinCode = ReadInput::ReadString("Please enter Pin Code");
	Client1.Name = ReadInput::ReadString("Please enter Name");
	Client1.Phone = ReadInput::ReadString("Please enter Phone Number");
	Client1.AccountBalance = ReadInput::ReadNumber("Please enter Balance");

	return Client1;
}

stUser ReadUserData() {
	stUser User;
	User.Username = ReadInput::ReadString("Please enter Username");
	User.Password = ReadInput::ReadString("Please enter Password");
	User.Permissions = ReadPermissions();

	return User;
}

void PrintClientData(stBankClient Client) {
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Account Pin Code: " << Client.PinCode << endl;
	cout << "User Name: " << Client.Name << endl;
	cout << "Phone Number: " << Client.Phone << endl;
	cout << "Accout Balance: " << Client.AccountBalance << endl;
}

void PrintUserData(stUser User) {
	cout << "Username: " << User.Username << endl;
	cout << "Password: " << User.Password << endl;
	cout << "Permissions: " << User.Permissions << endl;
}

void AddDataLineToFile(string FileName, string DataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

string ConvertRecordToLine(stBankClient Client1, string Del = "#//#") {
	string Record = "";

	Record += Client1.AccountNumber;
	Record += Del;
	Record += Client1.PinCode;
	Record += Del;
	Record += Client1.Name;
	Record += Del;
	Record += Client1.Phone;
	Record += Del;
	Record += to_string(Client1.AccountBalance);

	return Record;


}

string ConvertRecordToLine(stUser User, string Del = "#//#") {
	string Record = "";

	Record += User.Username;
	Record += Del;
	Record += User.Password;
	Record += Del;
	Record += to_string(User.Permissions);

	return Record;
}

stBankClient ConvertLineToRecord(string S1, string Del = "#//#") {
	short Pos = S1.find(Del);
	stBankClient Client1;
	string sWord;


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.AccountNumber = sWord;
	Pos = S1.find(Del);


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.PinCode = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Name = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Phone = sWord;

	Client1.AccountBalance = stod(S1);


	return Client1;
}

stUser ConvertLineToRecordU(string S1, string Del = "#//#") {
	short Pos = S1.find(Del);
	stUser User;
	string sWord;


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	User.Username = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	User.Password = sWord;
	Pos = S1.find(Del);

	User.Permissions = stoi(S1);

	return User;

}

void AddNewClient() {
	cout << "Adding New Client" << endl;
	stBankClient Client1;
	Client1 = ReadClientData();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client1, "#//#"));
}

void AddNewUser() {
	cout << "Adding New User" << endl;
	stUser User;
	User = ReadUserData();
	AddDataLineToFile(UsersFileName, ConvertRecordToLine(User, "#//#"));
}

void AddClients() {
	char AddMore = 'Y';

	do {
		AddNewClient();
		cout << "Do you want to add more clients? Y/N" << endl;
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void AddUsers() {
	char AddMore = 'Y';

	do {
		AddNewUser();
		cout << "Do you want to add more users? Y/N" << endl;
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

vector <stBankClient> ReadClientsFromFile(string FileName) {
	vector <stBankClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stBankClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;
}

vector <stUser> ReadUsersFromFile(string FileName) {
	vector <stUser> vUsers;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stUser User;
		while (getline(MyFile, Line)) {
			User = ConvertLineToRecordU(Line);
			vUsers.push_back(User);
		}

		MyFile.close();

	}

	return vUsers;
}

void PrintHorizontalLine() {
	for (short i = 0; i < 60; i++) cout << "__";
	cout << endl;
}

void PrintSeparator() {
	cout << " | ";
}

void PrintHeader(short NumOfRecords) {

	cout << setw(55) << "Client List(" << NumOfRecords << ") Client(s)." << endl;
	PrintHorizontalLine();
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << "Account Number";
	PrintSeparator();
	cout.width(10); cout << left << "Pin Code";
	PrintSeparator();
	cout.width(35); cout << left << "Client Name";
	PrintSeparator();
	cout.width(15); cout << left << "Phone";
	PrintSeparator();
	cout.width(10); cout << left << "Balance" << endl;
	PrintHorizontalLine();
}

void PrintUsersHeader(short NumOfRecords) {
	cout << setw(55) << "Users List(" << NumOfRecords << ") User(s)." << endl;
	PrintHorizontalLine();
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << "Username";
	PrintSeparator();
	cout.width(10); cout << left << "Password";
	PrintSeparator();
	cout.width(35); cout << left << "Permissions";
	PrintSeparator();
	cout << endl;
	PrintHorizontalLine();
}

void PrintOneClient(stBankClient Client1) {
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << Client1.AccountNumber;
	PrintSeparator();
	cout.width(10); cout << left << Client1.PinCode;
	PrintSeparator();
	cout.width(35); cout << left << Client1.Name;
	PrintSeparator();
	cout.width(15); cout << left << Client1.Phone;
	PrintSeparator();
	cout.width(10); cout << left << Client1.AccountBalance << endl;
}

void PrintOneUser(stUser User) {
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << User.Username;
	PrintSeparator();
	cout.width(10); cout << left << User.Password;
	PrintSeparator();
	cout.width(5); cout << left << User.Permissions;
}

void PrintOneClientBalance(stBankClient Client1) {
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << Client1.AccountNumber;
	PrintSeparator();
	cout.width(35); cout << left << Client1.Name;
	PrintSeparator();
	cout.width(10); cout << left << Client1.AccountBalance << endl;
}

void PrintAllClients(vector <stBankClient> Clients) {
	PrintHeader(Clients.size());

	for (stBankClient& Client : Clients) {
		PrintOneClient(Client);
	}

}

void PrintAllUsers(vector <stUser> Users) {
	PrintUsersHeader(Users.size());

	for (stUser& User : Users) {
		PrintOneUser(User);
	}

}

void AllBalancesHeader(short NumOfRecords) {
	cout << setw(55) << "Client List(" << NumOfRecords << ") Client(s)." << endl;
	PrintHorizontalLine();
	cout << endl;
	PrintSeparator();
	cout.width(15); cout << left << "Account Number";
	PrintSeparator();
	cout.width(35); cout << left << "Client Name";
	PrintSeparator();
	cout.width(10); cout << left << "Balance" << endl;
	PrintHorizontalLine();
}

void PrintAllClientsBalances(vector <stBankClient> Clients) {
	AllBalancesHeader(Clients.size());
	for (stBankClient& Client : Clients) {
		PrintOneClientBalance(Client);
	}
}

bool IsAccount(string AccountNumber, stBankClient& Client, vector <stBankClient> vClients) {

	for (stBankClient& C : vClients) {
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool IsUser(string Username, stUser& User, vector <stUser> vUsers) {
	for (stUser& U : vUsers) {
		if (U.Username == Username)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void MarkForDeletion(string AccountNumber, vector <stBankClient>& vClients) {
	for (stBankClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			Client.ToDelete = true;
		}
	}
}

void MarkForDeletion(string Username, vector <stUser>& vUsers) {
	for (stUser& User : vUsers) {
		if (User.Username == Username) {
			User.ToDelete = true;
		}
	}
}

void SaveVectorToFile(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;
	string Line;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			Line = ConvertRecordToLine(Client);
			MyFile << Line << endl;
		}

		MyFile.close();
	}
}

void SaveVectorToFile(string FileName, vector <stUser> vUsers) {
	fstream MyFile;
	string Line;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stUser& User : vUsers) {
			Line = ConvertRecordToLine(User);
			MyFile << Line << endl;
		}

		MyFile.close();
	}
}

void SaveVectorToFileToDelete(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			if (Client.ToDelete == false) {
				MyFile << ConvertRecordToLine(Client) << endl;
			}
		}
		MyFile.close();
	}

}

void SaveVectorToFileToDelete(string FileName, vector <stUser> vUsers) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stUser& User : vUsers) {
			if (User.ToDelete == false) {
				MyFile << ConvertRecordToLine(User) << endl;
			}
		}
		MyFile.close();
	}
}

void DeleteAccount(string AccountNumber, vector <stBankClient>& vClients) {
	char Delete;
	stBankClient Client;
	if (IsAccount(AccountNumber, Client, vClients)) {

		PrintClientData(Client);
		Delete = ReadInput::ReadCharacter("Are you sure you want to delete it? Y/N");
		if (toupper(Delete) == 'Y') {
			MarkForDeletion(AccountNumber, vClients);
			SaveVectorToFileToDelete(ClientsFileName, vClients);
			vClients = ReadClientsFromFile(ClientsFileName);
			cout << "Account Deleted Successfully" << endl;
		}

	}
	else {
		cout << "Account Can't be found :-(" << endl;
	}

}

void DeleteUser(string Username, vector <stUser>& vUsers) {
	char Delete;
	stUser User;
	if (IsUser(Username, User, vUsers)) {

		PrintUserData(User);
		Delete = ReadInput::ReadCharacter("Are you sure you want to delete it? Y/N");
		if (toupper(Delete) == 'Y') {
			MarkForDeletion(Username, vUsers);
			SaveVectorToFileToDelete(ClientsFileName, vUsers);
			vUsers = ReadUsersFromFile(UsersFileName);
			cout << "User Deleted Successfully" << endl;
		}

	}
	else {
		cout << "User Can't be found :-(" << endl;
	}
}

void MarkForUpdate(string AccountNumber, vector <stBankClient>& vClients) {
	for (stBankClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			Client.ToUpdate = true;
		}
	}
}

void MarkForUpdate(string Username, vector <stUser>& vUsers) {
	for (stUser& User : vUsers) {
		if (User.Username == Username) {
			User.ToUpdate = true;
		}
	}
}

void SaveVectorToFileToUpdate(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			if (Client.ToUpdate == false) {
				MyFile << ConvertRecordToLine(Client) << endl;
			}
			else {
				Client = ReadClientData();
				MyFile << ConvertRecordToLine(Client) << endl;
			}
		}
		MyFile.close();
	}
}

void SaveVectorToFileToUpdate(string FileName, vector <stUser> vUsers) {
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stUser& User : vUsers) {
			if (User.ToUpdate == false) {
				MyFile << ConvertRecordToLine(User) << endl;
			}
			else {
				User = ReadUserData();
				MyFile << ConvertRecordToLine(User) << endl;
			}
		}
		MyFile.close();
	}
}

void UpdateAccount(string AccountNumber, vector <stBankClient>& vClients) {
	char Update;
	stBankClient Client;
	if (IsAccount(AccountNumber, Client, vClients)) {

		PrintClientData(Client);
		Update = ReadInput::ReadCharacter("Are you sure you want to update it? Y/N");
		if (toupper(Update) == 'Y') {
			MarkForUpdate(AccountNumber, vClients);
			SaveVectorToFileToUpdate(ClientsFileName, vClients);
			vClients = ReadClientsFromFile(ClientsFileName);
		}
		cout << "Account Updated Successfully" << endl;
	}
	else {
		cout << "Account Can't be found :-(" << endl;
	}
}

void UpdateUser(string Username, vector <stUser>& vUsers) {
	char Update;
	stUser User;
	if (IsUser(Username, User, vUsers)) {

		PrintUserData(User);
		Update = ReadInput::ReadCharacter("Are you sure you want to update it? Y/N");
		if (toupper(Update) == 'Y') {
			MarkForUpdate(Username, vUsers);
			SaveVectorToFileToUpdate(UsersFileName, vUsers);
			vUsers = ReadUsersFromFile(UsersFileName);
		}
		cout << "User Updated Successfully" << endl;
	}
	else {
		cout << "User Can't be found :-(" << endl;
	}
}

void AccessDeniedScreen() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "                 Access Denied                 " << endl;
	cout << "===============================================" << endl;
	cout << "You don't have the permission to access this, please contact admin" << endl;
}

bool AccessGuranted(enPermissions Permission) {
	if (Permission == enPermissions::All) return true;
	else {
		if ((Permission & CurrentUser.Permissions) == Permission) return true;
		else return false;
	}
}

void MainMenuScreen() {
	cout << "===============================================" << endl;
	cout << "               Main Menu Screen               " << endl;
	cout << "===============================================" << endl;

	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Manage Users." << endl;
	cout << "\t[8] Logout." << endl;
	cout << "===============================================" << endl;

}

void ManageUsersMenuScreen() {
	cout << "===============================================" << endl;
	cout << "            Manage Users Menu Screen           " << endl;
	cout << "===============================================" << endl;

	cout << "\t[1] List Users." << endl;
	cout << "\t[2] Add New User." << endl;
	cout << "\t[3] Delete User." << endl;
	cout << "\t[4] Update User." << endl;
	cout << "\t[5] Find User." << endl;
	cout << "\t[6] Main Menu." << endl;

	cout << "===============================================" << endl;
}

void ShowClientListScreen() {
	if (!AccessGuranted(enPermissions::ListClients)) {
		AccessDeniedScreen();
	}
	else {
		vector <stBankClient> vClients;
		vClients = ReadClientsFromFile(ClientsFileName);
		system("cls");
		PrintAllClients(vClients);
	}
}

void ShowUsersListScreen() {
	vector <stUser> vUsers;
	vUsers = ReadUsersFromFile(UsersFileName);
	system("cls");
	PrintAllUsers(vUsers);
}

void ShowBalancesScreen() {
	vector <stBankClient> vClients;
	vClients = ReadClientsFromFile(ClientsFileName);
	system("cls");
	PrintAllClientsBalances(vClients);
}

void AddNewClientScreen() {
	if (!AccessGuranted(enPermissions::AddClient)) {
		AccessDeniedScreen();
	}
	else {
		system("cls");
		cout << "===============================================" << endl;
		cout << "             Add New Client Screen             " << endl;
		cout << "===============================================" << endl;
		AddClients();
	}
}

void AddNewUserScreen() {

	system("cls");
	cout << "===============================================" << endl;
	cout << "              Add New User Screen              " << endl;
	cout << "===============================================" << endl;
	AddUsers();
}

void DeleteAccountScreen() {
	if (!AccessGuranted(enPermissions::DeleteClient)) {
		AccessDeniedScreen();
	}
	else {
		system("cls");
		vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
		cout << "===============================================" << endl;
		cout << "             Delete Account Screen             " << endl;
		cout << "===============================================" << endl;
		string AccNum;
		AccNum = ReadInput::ReadString("Please enter account number you want to delete");
		DeleteAccount(AccNum, vClients);
	}
}

void DeleteUserScreen() {
	system("cls");
	vector <stUser> vUsers = ReadUsersFromFile(UsersFileName);
	cout << "===============================================" << endl;
	cout << "               Delete User Screen              " << endl;
	cout << "===============================================" << endl;
	string Username;
	Username = ReadInput::ReadString("Please enter username you want to delete");
	DeleteUser(Username, vUsers);
}

void UpdateAccountScreen() {
	if (!AccessGuranted(enPermissions::UpdateClient)) {
		AccessDeniedScreen();
	}
	else {
		system("cls");
		vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
		cout << "===============================================" << endl;
		cout << "             Update Account Screen             " << endl;
		cout << "===============================================" << endl;
		string AccNum;
		AccNum = ReadInput::ReadString("Please enter account number you want to update");
		UpdateAccount(AccNum, vClients);
	}
}

void UpdateUserScreen() {
	system("cls");
	vector <stUser> vUsers = ReadUsersFromFile(UsersFileName);
	cout << "===============================================" << endl;
	cout << "               Update User Screen              " << endl;
	cout << "===============================================" << endl;
	string Username;
	Username = ReadInput::ReadString("Please enter username you want to update");
	UpdateUser(Username, vUsers);
}

void FindClientScreen() {
	if (!AccessGuranted(enPermissions::FindClient)) {
		AccessDeniedScreen();
	}
	else {
		system("cls");
		vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
		cout << "===============================================" << endl;
		cout << "             Find Account Screen             " << endl;
		cout << "===============================================" << endl;
		string AccNum;
		AccNum = ReadInput::ReadString("Please enter account number you want to search for");
		stBankClient Client;

		if (IsAccount(AccNum, Client, vClients))
			PrintClientData(Client);
		else cout << "Account Can't be found :-(" << endl;

	}
}

void FindUserScreen() {
	system("cls");
	vector <stUser> vUsers = ReadUsersFromFile(UsersFileName);
	cout << "===============================================" << endl;
	cout << "                Find User Screen               " << endl;
	cout << "===============================================" << endl;
	string Username;
	Username = ReadInput::ReadString("Please enter username you want to search for");
	stUser User;

	if (IsUser(Username, User, vUsers))
		PrintUserData(User);
	else cout << "User Can't be found :-(" << endl;
}

void TransactionsMenuScreen() {
	if (!AccessGuranted(enPermissions::PerformTransactions)) {
		AccessDeniedScreen();
	}
	else {
		system("cls");
		cout << "===============================================" << endl;
		cout << "            Transactions Menu Screen           " << endl;
		cout << "===============================================" << endl;
		cout << "\t[1] Deposit." << endl;
		cout << "\t[2] Withdraw." << endl;
		cout << "\t[3] Total Balances." << endl;
		cout << "\t[4] Main Menu" << endl;
		cout << "===============================================" << endl;

	}
}

void Deposit(string AccNum) {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	double Amount;
	cout << "Please enter amount you want to deposit" << endl;
	cin >> Amount;
	char Dep = 'N';
	cout << "Are you sure you want to deposit: $" << Amount << " to " << AccNum << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance += Amount;
				SaveVectorToFile(ClientsFileName, vClients);
				cout << "Amount of: $" << Amount << " has been deposited to " << Client.Name << " Successfully" << endl;
			}
		}
	}
	else return;

}

void DepositScreen() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	stBankClient Client;
	system("cls");
	cout << "===============================================" << endl;
	cout << "                 Deposit Screen                " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to deposit to");
	if (IsAccount(AccNum, Client, vClients)) {
		PrintClientData(Client);
		Deposit(AccNum);
	}
	else {
		cout << "Account is not found" << endl;
		system("pause");
		DepositScreen();
	}
}

void Withdraw(string AccNum) {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	double Amount;
	cout << "Please enter amount you want to withdraw" << endl;
	cin >> Amount;
	char Dep = 'N';
	cout << "Are you sure you want to withdraw: $" << Amount << " from " << AccNum << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance -= Amount;
				SaveVectorToFile(ClientsFileName, vClients);
				cout << "Amount of: $" << Amount << " has been withdrawed from " << Client.Name << " Successfully" << endl;
			}
		}
	}
	else return;
}

void WithdrawalScreen() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	stBankClient Client;
	system("cls");
	cout << "===============================================" << endl;
	cout << "               Withdrawal Screen               " << endl;
	cout << "===============================================" << endl;
	string AccNum;
	AccNum = ReadInput::ReadString("Please enter account number you want to withdraw from");
	if (IsAccount(AccNum, Client, vClients)) {
		PrintClientData(Client);
		Withdraw(AccNum);
	}
	else {
		cout << "Account is not found" << endl;
		system("pause");
		WithdrawalScreen();
	}
}

void TransactionsScreen() {
	TransactionsMenuScreen();
	short Choice = ReadInput::ReadNumInRange(1, 4, "Please choose what do you want to do [1] -> [4]");
	switch (Choice)
	{
	case 1:
		DepositScreen();
		system("pause");
		TransactionsScreen();
	case 2:
		WithdrawalScreen();
		system("pause");
		TransactionsScreen();
	case 3:
		ShowBalancesScreen();
		system("pause");
		TransactionsScreen();
	case 4:
		BankSystem();
	}
}

void LoginScreen() {
	system("cls");
	vector <stUser> vUsers = ReadUsersFromFile(UsersFileName);
	cout << "===============================================" << endl;
	cout << "                 Login Screen                  " << endl;
	cout << "===============================================" << endl;
	string Username, Password;
	Username = ReadInput::ReadString("Please enter username");
	Password = ReadInput::ReadString("Please enter password");
	stUser User;

	if (IsUser(Username, User, vUsers))
	{
		if (User.Password == Password) {
			BankSystem();
		}
		else {
			cout << "Wrong Password" << endl;
			system("pause");
			LoginScreen();
		}
	}
	else {
		cout << "Wrong Username" << endl;
		system("pause");
		LoginScreen();
	}
}

void BankSystem() {
	vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);
	system("cls");
	int Choice;
	MainMenuScreen();
	Choice = ReadInput::ReadNumInRange(1, 8, "Choose what do you want to do [1] -> [8]");
	switch (Choice)
	{
	case 1:
		ShowClientListScreen();
		system("pause");
		BankSystem();
	case 2:
		AddNewClientScreen();
		system("pause");
		BankSystem();
	case 3:
		DeleteAccountScreen();
		system("pause");
		BankSystem();
	case 4:
		UpdateAccountScreen();
		system("pause");
		BankSystem();
	case 5:
		FindClientScreen();
		system("pause");
		BankSystem();
	case 6:
		TransactionsScreen();
		system("pause");
	case 7:
		ManageUsers();
		system("pause");
		break;
	case 8:
		LoginScreen();
	}
}

void ManageUsers() {
	vector <stUser> vUsers = ReadUsersFromFile(UsersFileName);
	system("cls");
	int Choice;
	ManageUsersMenuScreen();
	Choice = ReadInput::ReadNumInRange(1, 6, "Choose what do you want to do [1] -> [6]");
	switch (Choice)
	{
	case 1:
		ShowUsersListScreen();
		system("pause");
		ManageUsers();
	case 2:
		AddNewUserScreen();
		system("pause");
		ManageUsers();
	case 3:
		DeleteUserScreen();
		system("pause");
		ManageUsers();
	case 4:
		UpdateUserScreen();
		system("pause");
		ManageUsers();
	case 5:
		FindUserScreen();
		system("pause");
		ManageUsers();

	case 6:
		BankSystem();
	}
}

int main()
{
	LoginScreen();

	system("pause");
	return 0;
}