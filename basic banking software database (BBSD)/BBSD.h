//#ifndef _BBSD_H_
//#define _BBSD_H_
// Project: Basic Banking Software Database
// Name: Brandan Tyler Lasley
// Date: 1/30/2014 18:57

// Level 0 - 2
// Balance
// Depost
// Withdrawl
// Transfer
// Total Cash (optional, level 0 ONLY)

// Level 1
// New Customer
// Remove Customer
// Search

// Level 3
// Total of employees in bank
// Total amount of money in bank
// Total Deposits in a day
// Total withdrawls in a day
// Abillity to see detailed log of all transactions
// Sort Database (optional)
// Create money (optional)
/*

NOTE: I thought I knew how to write a header file, but as of 23:07 I cannot figure it out, so it wont be included. 

class Customer
{

public:

	Customer();
	~Customer();

	void balance(int customerid, Account accounts[], int size);
	bool depost(int customerid, double amount, Account accounts[], int size);
	bool withdraw(int customerid, double amount, Account accounts[], int size);
	bool transfer(int customerid, double amount, int accountid, Account accounts[], int size);
	void customercash(int customerid, Account accounts[], int size);
};

class empolyee
{
public:
	empolyee();
	~empolyee();

	bool addCustomer(string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype, Account accounts[], int size);
	bool delCustomer(int customerid, Account accounts[], int size);
	void search(string customername, Account accounts[], int size);
};

class root
{
public:
	root();
	~root();

	void listEmployees(Account accounts[], int size);
	void listAdmin(Account accounts[], int size);
	void totalDeposits();
	void totalWithdrawl();
	void viewLog();
	void reloadDatabase(Account accounts[], int size);
	void saveDatabase(Account accounts[], int size);
	bool createMoney(double ammount, int customerid, Account accounts[], int size);
private:
	const std::string currentDateTime();
};

class logging
{
	public:
		logging();
		~logging();

		void WriteLogFile(string text);
		const std::string currentDateTime();
};

class security
{
public:
	security();
	~security();

	bool login(string username, string password, Account accounts[], int size);
	int getAccount(string username, Account accounts[], int size);
	int permission(int customerid, Account accounts[], int size);
	string permissionname(int permissionlvl, Account accounts[], int size);
};
#endif
*/