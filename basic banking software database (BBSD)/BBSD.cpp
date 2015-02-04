#define _CRT_SECURE_NO_WARNINGS // Prevnt OS depenency to Windows and using Microsoft functions (for time)....
// Project: Basic Banking Software Database
// Name: Brandan Tyler Lasley
// Date: 1/30/2014 18:57

// should this be an economy where money can't be created or destroyed? Maybe a default cash? like a real bank?

// This will be based on a level system from 0 - 2
// 0 Customer
// 1 Employee
// 2 Boss (root?)

// ====== CUSTOMER ======
// Balance
// Depost
// Withdraw
// Transfer
// Total Cash (optional, A place to withdrawl money, employee or bank shouldn't beable to NSA spy on the customer?)

// ====== EMPLOYEE ======
// Everything above
// Add customer (account)
// Delete customer (account)
// Search records using "Name" using Swquential search

// ====== BOSS ======
// Everything in the bank teller and customer
// List total number of employees in bank
// List Ttoal amount of money in the bank
// Total deposits in a day
// total withdrawls in a day
// Abillity to see detailed log of all transactions
// Sort databade (optional)
// Create money (optional)

// Remember to declare constants or a varible to control ALL ARRAYS!

// Completed (16/16) levels (2/3) 100% Complete

// Todo: 
//

// Know Issues & Limiatations:
// Max 2000 customers
// If you use the illegal char '◦' anywhere in the program it will corrupt the database, I may fix this.
// I have no idea how a credit card, savings, or 'instant access' works. So those wasn't added.  
// Any illegal chars will break it.
// Ugh.... Detailed log wasn't possible... couldn't read certian parts of the data because some lines of the log file were longer than other
// causing ifstream to go out of sync... probably some way to make it read upto the '\n' but i'm unsure at this moment on how to do it. Need to test other things also.

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include "BBSD.h"

using namespace std;

enum AccountType {
	unknown = -1, Checking, Savings, CreditCard, InstantAccess
};

enum Permissions {
	Customer, Employee, Root
};

struct Account {
	// Login Info
	string username;
	string password;

	int account = -1; 
	string firstName;
	string lastName;
	AccountType type = AccountType::Checking;
	Permissions Permissions = Permissions::Customer;
	float money = 0; // Money is like debit
	float cash = 0;  // Cash is what the 'customer' has on hand. hypothetical.
};

class customer {
	// ====== CUSTOMER ======
	// Balance
	// Depost
	// Withdraw (and transfer)
	// Total Cash (optional, A place to withdrawl money, employee or bank shouldn't beable to NSA spy on the customer?)
public:
	void balance(int customerid, Account accounts[], int size) { // <B>
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (customerid == accounts[i].account) {
					cout << "Current balance: " << accounts[i].money << endl;
				}
			}
		}
	}

	bool depost(int customerid, double amount, Account accounts[], int size) { // <D>
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (customerid == accounts[i].account) {
					if (amount > accounts[i].cash) {
						cout << "You do not have enough cash to make this deposit!" << endl;
						return false;
					}
					else {
						accounts[i].money = accounts[i].money + amount;
						accounts[i].cash = accounts[i].cash - amount;
						cout << "Deposit Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return false;
	}

	bool withdraw(int customerid, double amount, Account accounts[], int size) { // <W>
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (customerid == accounts[i].account) {
					if (amount > accounts[i].money) {
						cout << "You do not have enough money to make this withdrawl!" << endl;
						return false;
					}
					else {
						accounts[i].money = accounts[i].money - amount;
						accounts[i].cash = accounts[i].cash + amount;
						cout << "Withdraw Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return false;
	}


	// I dont know enough about banks to impliment it the way you want it... is a Checkings/Savings account on a completely
	// different account or is it the same account just with a struct and can a credit card go into the negitives!?? 

	// ATMs dont allow you to transfer funds anyways, atleast not any that I've used. 
	// This function will simpily transfer it from one account to the other, this is a debit type system because i've only used a 
	// debit card and have no idea how anything else works. No negatives, no debt. 

	// I do enjoy how you leave most of the project up to your imagination and research though. 
	// But there wasn't enough infomation on how to handle those different account types and how they work. 

	bool transfer(int customerid, double amount, int accountid, Account accounts[], int size) { // <W>
		if (customerid != -1) {
			int myaccount = -1;
			// Find my account number (index). 
			for (int i = 0; i <= size - 1; i++) {
				if (customerid == accounts[i].account) {
					myaccount = i;
				}
			}

			if (myaccount == -1) {
				return false;
			}

			// Find the account number of the transfer person. 
			for (int i = 0; i <= size - 1; i++) {
				if (accountid == accounts[i].account) {
					if (accounts[myaccount].money < amount) { // < means less than, abit dyslexic when it comes to <> so I get it wrong, its the other way.
						return false;
					}
					else {
						accounts[myaccount].money = accounts[myaccount].money - amount;
						accounts[i].money = accounts[i].money + amount;
						cout << "Transfer Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return true;
	}

	void customercash(int customerid, Account accounts[], int size) { // <CC>
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].account == customerid) {
					cout << "Your current cash is: " << accounts[i].cash << endl;
					break;
				}
			}
		}
	}
};

class empolyee {
	// ====== EMPLOYEE ======
	// Everything above
	// Add customer (account)
	// Delete customer (account)
	// Search records using "Name" using Swquential search

	/*
	// Login Info
	string username;
	string password;

	int account = 0; 
	string firstName;
	string lastName;
	AccountType type = AccountType::Checking;
	Permissions Permissions = Permissions::Customer;
	float money = 0; // Money is like debit
	float cash = 0;  // Cash is what the 'customer' has on hand. hypothetical.
	
	*/
public:
	bool addCustomer(string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype, Account accounts[], int size) { //AC
		bool found = false;
		int AccountID = -1;
		/*
				// Account # Algorithm (will break after 2000, unless the array size is changed)
		for (int i = 0; i <= size - 1; i++) {
			for (int b = 0; b <= size - 1; b++) {
				if (accounts[i].account == b) {
					found = true;
				}
				if (found == true) {
					AccountID = b;
					break;
				}
			}
		}
		*/
		
		for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].account == -1) {
					accounts[i].account = i + 1;
					accounts[i].username = username;
					accounts[i].password = password;
					accounts[i].firstName = firstname;
					accounts[i].lastName = lastname;
					accounts[i].type = accounttype;
					accounts[i].Permissions = permissions;
					cout << "Success! Account #: " << i + 1;
					return true;
					break;
				}
			}
		return false;
	}

	bool delCustomer(int customerid, Account accounts[], int size) { // DC
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].account == customerid) {

					// Clean up and remove user!
					accounts[i].account = -1;
					accounts[i].username = "";
					accounts[i].password = "";
					accounts[i].cash = 0;
					accounts[i].money = 0;
					accounts[i].type = AccountType::Checking;
					accounts[i].Permissions = Permissions::Customer;

					return true;
					break;
				}
			}
		}
		return false;
	}

	// Case Sensitive!
	void search(string customername, Account accounts[], int size) { // search
		for (int i = 0; i <= size - 1; i++) {
			if (accounts[i].firstName == customername) {
				cout << "Account Infomation: " << endl
					<< "Account #: " << accounts[i].account << endl
					<< "Username: " << accounts[i].username << endl 
					<< "Money (in checking): " << accounts[i].money << endl 
					<< "Account Type: " << accounts[i].type << endl 
					<< "Permissions: " << accounts[i].Permissions << endl;
			}
		}
	}
};
class root {
	// ====== BOSS ======
	// Everything in the bank teller and customer
	// List total number of employees in bank
	// List total amount of money in the bank
	// Total deposits in a day
	// total withdrawls in a day
	// Abillity to see detailed log of all transactions
	// Sort databade (optional)
	// Create money (optional)
	// Reload DB (optional)
	// Save DB (optional)

private:
	const std::string currentDateTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

public:
	void listEmployees(Account accounts[], int size) {
		for (int i = 0; i <= size - 1; i++) {
			if (accounts[i].Permissions == Permissions::Employee) {
				if (accounts[i].account != -1) {
					cout
						<< "=======================================" << endl
						<< "Account Infomation: " << endl
						<< "Account #: " << accounts[i].account << endl
						<< "Username: " << accounts[i].username << endl;
				}
			}
		}
	}

	// Not added to the options/command list!!!! <================================== <- Fixed
	void listAdmin(Account accounts[], int size) {
		for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].Permissions == Permissions::Root) {
				if (accounts[i].account != -1) {
					cout
						<< "=======================================" << endl
						<< "Account Infomation: " << endl
						<< "Account #: " << accounts[i].account << endl
						<< "Username: " << accounts[i].username << endl;
				}
			}
		}
	}

	// Sorry about the CTRL + C CTRL + V code, I normally dont do this, just for time sake. Need to debug other things then worry about
	// Fixing this code so its more robust. 
	void totalDeposits() { // <--- Needs work
		string date;
		string td = currentDateTime();
		std::string delimiter = ".";

		size_t pos = 0;
		std::string token;
		while ((pos = td.find(delimiter)) != std::string::npos) {
			token = td.substr(0, pos);
			date = token;
			break;
			td.erase(0, pos + delimiter.length());
		}

		string filename;
		ifstream data;

		data.open("log_file.txt");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file, press enter to exit";
			getchar();
			getchar();
		}

		double amount = 0;
		while (!data.eof()) {
			string date2 = "";
			string timestamp = "";
			string type;
			double in = 0;
			string dummy = "";

			data >> timestamp >> type >> dummy >> in;
			td = timestamp;
			data.ignore();

			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}
			if (type == "Deposit") {
				if (date == date2) {
					amount += in;
				}
			}
		}

		cout << "Todays Total Deposits: " << amount << endl;
	}

	void totalWithdrawl() { // <--- Needs Work
		string date;
		string td = currentDateTime();
		std::string delimiter = ".";

		size_t pos = 0;
		std::string token;
		while ((pos = td.find(delimiter)) != std::string::npos) {
			token = td.substr(0, pos);
			date = token;
			break;
			td.erase(0, pos + delimiter.length());
		}

		string filename;
		ifstream data;

		data.open("log_file.txt");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file, press enter to exit";
			getchar();
			getchar();
		}

		double amount = 0;
		while (!data.eof()) {
			string date2 = "";
			string timestamp = "";
			string type;
			double in = 0;
			string dummy = "";


			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}

			data >> timestamp >> type >> dummy >> in;
			
			data.ignore();
			td = timestamp;

			
			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}
			if (type == "Withdraw") {
				if (date == date2) {
					amount += in;
				}
			}
		}

		cout << "Todays Total Withdrawl: " << amount << endl;

	}

	void viewLog() { 
		ifstream myReadFile;
		myReadFile.open("log_file.txt");
		char output[100];
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {
				myReadFile >> output;
				cout << output;
			}
		}
		cout << endl;
		myReadFile.close();
	}

	void reloadDatabase(Account accounts[], int size) {
		
		// Clean DB
		for (int i = 0; i <= size - 1; i++) {
				// Clean up and remove user!
				accounts[i].account = -1;
				accounts[i].username = "";
				accounts[i].password = "";
				accounts[i].cash = 0;
				accounts[i].money = 0;
				accounts[i].type = AccountType::Checking;
				accounts[i].Permissions = Permissions::Customer;
		}


		string filename;
		ifstream data;

		int account;
		string username;
		string password;
		string firstname;
		string lastname;
		double cash;
		double money;

		int type;
		int permissions;

		data.open("members.db");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file...";
			getchar();
			getchar();
		}

		int i = 0;

		while (!data.eof()){
			data >> account >> username >> password >> firstname >> lastname >> cash >> money >> type >> permissions;
			accounts[i].account = account;
			accounts[i].username = username;
			accounts[i].password = password;
			accounts[i].firstName = firstname;
			accounts[i].lastName = lastname;
			accounts[i].cash = cash;
			accounts[i].money = money;
			accounts[i].type = static_cast<AccountType>(type);
			accounts[i].Permissions = static_cast<Permissions>(permissions);
			i++;
		}

	}

	void saveDatabase(Account accounts[], int size) {
		if (remove("members.db") != 0){
			cout << "Error deleting file";
		}
		ofstream membersdb("members.db");
		if (membersdb.is_open())
		{
			for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].account != -1) {
					if (i != 0) { 
						membersdb << endl; // Duct tape over a real issue.
					}
					
					membersdb << accounts[i].account << " " << accounts[i].username << " " << accounts[i].password
						<< " " << accounts[i].firstName << " " << accounts[i].lastName
						<< " " << accounts[i].cash << " " << accounts[i].money << " " << accounts[i].type
						<< " " << accounts[i].Permissions;
				}
			}
		}
		membersdb.close();
	}

	bool createMoney(double ammount, int customerid, Account accounts[], int size) {
		if (customerid != -1) {
			for (int i = 0; i <= size - 1; i++) {
				if (accounts[i].account == customerid) {
					accounts[i].money = accounts[i].money + ammount;
					break;
				}
			}
		}
		else {
			return false;
		}
	}

}; 

class logging {

public:

	
	void WriteLogFile(string text)
	{
		std::ofstream log_file("log_file.txt", std::ios_base::out | std::ios_base::app);

		log_file << text;
	}

	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	const std::string currentDateTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}


};
class security {

	// This will be based on a level system from 0 - 2
	// 0 Customer
	// 1 Employee
	// 2 Boss (root?)

public:

	bool login(string username, string password, Account accounts[], int size) {

		for (int i = 0; i <= size - 1; i++) {
			// Case Sensitive ALL FEILDS!
			if ((username == accounts[i].username) && (password == accounts[i].password)) {
				return true;
			}


		}
		return false;
	}

	int getAccount(string username, Account accounts[], int size) {
		for (int i = 0; i <= size - 1; i++) {
			if ((username == accounts[i].username)) {
				return accounts[i].account;
			}
		}
		return -1;
	}

	int permission(int customerid, Account accounts[], int size) {
		for (int i = 0; i <= size - 1; i++) {
			if ((customerid == accounts[i].account)) {
				return accounts[i].Permissions;
			}
		}
		return -1;
	}

	string permissionname(int permissionlvl, Account accounts[], int size) {
		if (permissionlvl == Permissions::Customer) {
			return "Customer";
		}
		else if (permissionlvl == Permissions::Employee) {
			return "Employee";
		}
		else if (permissionlvl == Permissions::Root) {
			return "Root/Administrator";
		} else {
			return "Malicious User";
		}
	}
};

// How do we do the account # thing for the current user logged in?
// Do we just load the info at start?
// Should we also ask if they want to deposit to another user?
// Transer? 

int main() {

	// Class Declarisons 
	security access;
	customer customer;
	empolyee empolyee;
	logging logging;
	root root;
	
	//logging.WriteLogFile("test");

	// Array size 2000, MAX Customers.
	 const int ARRAY_SIZE = 2000;

	// Username & Password, this is a secure system. 
	string username;
	string password;

	// Declare Struct
	Account accounts[ARRAY_SIZE];

	root.reloadDatabase(accounts, ARRAY_SIZE); // Load DB

	cout << "Welcome to Brandans Banking System!" << endl;
	cout << "Username: ";
	cin >> username;          // Usernames cannot contains spaces 
	getchar();               // Fix annoying auto input from enter.
	cout << "Password: "; 
	cin >> password; // nor can password, no catch for this though.

	// ==== Login ====
	if (access.login(username, password, accounts, ARRAY_SIZE)) {
		int id = access.getAccount(username, accounts, ARRAY_SIZE); // Gets the ID, faster to seek than searching strings, good pratice for MySQL also. 
		int Accesslvl = access.permission(id, accounts, ARRAY_SIZE);

		string input;
		int input2;
		double input3;

		while (true) {

			if (Accesslvl <= -1 || Accesslvl > 2) {
				// Prevents memory hacking... probably.
				// Well only if they dont know the permission system is 0 - 2. 
				// If they do oh well...

				cout << "Access Denied" << endl;
				getchar();
				getchar();
				return 0;
			}

			cout << endl << "Please Enter Command: ";
			cin >> input;

			if (input == "Q" || input == "q") {
				// Quit (Permissions >CUSTOMER)
				root.saveDatabase(accounts,ARRAY_SIZE);
				return 0;
			}
			else if (input == "B" || input == "b") {
				if (Accesslvl == Permissions::Customer) {
					customer.balance(id, accounts, ARRAY_SIZE);
				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					customer.balance(cust_ID, accounts, ARRAY_SIZE);
				}
				// Balance (Permissions >CUSTOMER)
			}
			else if (input == "D" || input == "d") {
				if (Accesslvl == Permissions::Customer) {
					double amount; 
					cin >> amount;
					bool success = customer.depost(id, amount, accounts, ARRAY_SIZE);
					
				if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}

				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					double amount = 0;
					cin >> amount;

					bool success = customer.depost(cust_ID, amount, accounts, ARRAY_SIZE);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
				  }
		
				}
				// Deposit (Permissions >CUSTOMER)
			}
			else if (input == "W" || input == "w") {
				if (Accesslvl == Permissions::Customer) {
					double amount;
					cin >> amount;
					bool success = customer.withdraw(id, amount, accounts, ARRAY_SIZE);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Withdraw ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					double amount = 0;
					cin >> amount;

					bool success = customer.withdraw(cust_ID, amount, accounts, ARRAY_SIZE);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Withdraw ";
						log += std::to_string(cust_ID);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				// Withdrawl (Permissions >CUSTOMER)
			}
			else if (input == "T" || input == "T") {
				if (Accesslvl == Permissions::Customer) {
					int toid;
					cin >> toid;
					int amount;
					cin >> amount;
					bool success = customer.transfer(id, amount, toid, accounts, ARRAY_SIZE);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Transfer ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				else {
					int fromid = 0;
					cin >> fromid;
					int toid = 0;
					cin >> toid;
					double amount = 0;
					cin >> amount;
					bool success = customer.transfer(fromid, amount, toid, accounts, ARRAY_SIZE);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				// Transfer (Permissions <CUSTOMER)
			}
			else if (input == "CC" || input == "Cc") {
				if (Accesslvl == Permissions::Customer) {
					customer.customercash(id, accounts, ARRAY_SIZE);
				}
				// Customer Cash (Permissions <CUSTOMER)
			}
			else if (input == "AC" || input == "Ac" || input == "ac") {
				if (Accesslvl >= Permissions::Employee) {
					string usrname;
					string psword;
					string firstname;
					string lastname;
					int permission;
					int type;
					cin >> usrname;
					cin >> psword;
					cin >> firstname;
					cin >> lastname;
					cin >> permission;
					cin >> type;

					bool success = empolyee.addCustomer(usrname, psword, firstname, lastname, static_cast<Permissions>(permission), static_cast<AccountType>(type), accounts, ARRAY_SIZE);

				}
				// Add Customer (Permissions >EMPLOYEE)
			}
			else if (input == "DC" || input == "Dc" || input == "dc") {
				if (Accesslvl >= Permissions::Employee) {
					int custid;
					cin >> custid;
					bool success = empolyee.delCustomer(custid, accounts, ARRAY_SIZE);
				}
				// Delete Customer (Permissions >EMPLOYEE)
			}
			else if (input == "SEARCH" || input == "Search" || input == "search") {
				string firstname;
				cin >> firstname;
				if (Accesslvl >= Permissions::Employee) {
					empolyee.search(firstname, accounts, ARRAY_SIZE); // Case Sensitive
				}
			}
			else if (input == "TE" || input == "Te" || input == "te") {
				if (Accesslvl >= Permissions::Root) {
					root.listEmployees(accounts, ARRAY_SIZE);
				}
				// Total Empoyees (Permissions ROOT)
			}
			else if (input == "TR" || input == "Tr" || input == "tr") {
				if (Accesslvl == Permissions::Root) {
					root.listAdmin(accounts, ARRAY_SIZE);
				}
				else {

				}
				// Total Roots (Permissions ROOT)
			}
			else if (input == "TD" || input == "Td" || input == "td") {
				if (Accesslvl == Permissions::Root) {
					root.totalDeposits();

				}
				// Total Deposits (TODAY) (Permissions ROOT)
			}
			else if (input == "TW" || input == "Tw" || input == "tw") {
				if (Accesslvl == Permissions::Root) {
					root.totalWithdrawl();
				}
				// Total Wutgdrawks (TODAY) (Permissions ROOT)
			}
			else if (input == "CM" || input == "Cm" || input == "cm") {
				if (Accesslvl == Permissions::Root) {
					int custid;
					cin >> custid;
					double amount;
					cin >> amount;

					root.createMoney(amount, custid, accounts, ARRAY_SIZE);
				}
				// Create Money (Permissions ROOT)
			}
			else if (input == "REHASH" || input == "Rehash" || input == "rehash") {
				if (Accesslvl == Permissions::Root) {
					root.reloadDatabase(accounts, ARRAY_SIZE);
				}
				// Reload Database (Permissions ROOT)
			}
			else if (input == "LOG" || input == "log" || input == "Log") {
				if (Accesslvl == Permissions::Root) {
					root.viewLog();
				}
				// Save Database (Permissions ROOT)
			}
			else if (input == "SAVE" || input == "Save" || input == "save") {
				if (Accesslvl == Permissions::Root) {
					root.saveDatabase(accounts, ARRAY_SIZE);
				}
				// Save Database (Permissions ROOT)

			} else if (input == "help" || input == "HELP" || input == "Help") {
			
				if (Accesslvl >= Permissions::Customer) {
					cout << endl <<
						"Current Commands for permission level: " << access.permissionname(Accesslvl, accounts, ARRAY_SIZE) << endl;
					if (Accesslvl >= Permissions::Employee) {
						cout << "Balance          <B> (usage B <ID>)" << endl
							<< "Depost           <D> (usage D <ID>)" << endl
							<< "Withdraw         <W> (usage W <ID>)" << endl
							<< "Transfer         <W> (usage T <FROM ID> <TO ID> <AMOUNT>)" << endl
							<< "Quit             <Q> (usage Q)" << endl;
					}
					else {
							cout << "Balance          <B> (usage B)" << endl
							<< "Depost           <D> (usage D)" << endl
							<< "Withdraw         <W> (usage W)" << endl
							<< "Transfer         <W> (usage T <ID> <AMOUNT>)" << endl
							<< "Customercash     <CC> (usage CC)" << endl
							<< "Quit             <Q> (usage Q)" << endl;
					}
				}
				//int customerid, string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype { //AC
				if (Accesslvl >= Permissions::Employee) {
					cout << "Addcustomer      <AC> (usage Addcustomer <USERNAME> <PASSWORD> <FIRSTNAME> <LASTNAME> <PERMISIONS> <ACCOUNT TYPE>)" << endl
						<< "Delcustomer      <DC (usage Delcustomer <ID>)" << endl
						<< "Search (by name) <search> (usage Search Brandan)" << endl;
				}

				if (Accesslvl == Permissions::Root) {
					cout << "Total Employees  <TE> (usage TE)" << endl
						 << "Total Roots      <TR> (usage TR)" << endl
					   	 << "Total Deposits   <TD> (usage TD)" << endl
						 << "Total Withdraws  <TW> (usage TW)" << endl
				         << "Create Money     <CM> (usage CM <ID> <AMOUNT>)" << endl
						 << "View Log         <LOG> (usage LOG) " << endl
						 << "Reload Database  <REHASH> (usage REHASH) " << endl
						 << "Save   Database  <SAVE> (usage SAVE)" << endl;
				}

				cout << endl;
			} else {
				cout << "Invalid Command, type help for list of commands" << endl << endl;
			}

		}
	} else {

		// Prevents brute force attacks, memory hacking etc... probably.. in theory. 
		cout << endl << "You have entered an invalid login credential, for your safety this application will now terminate!";
		getchar();
		return 0;
	}
}