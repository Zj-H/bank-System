
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H
#include<vector>
#include<fstream>
#include<string>
using namespace std;
class Account 
{
public:
	Account();
	~Account();
	//set function
	void setFirstName(string name);
	void setLastName(string name);
	void setAccountId(string id);
	void setBalance(int index, int count);
	void setTradeRecords(int index,string record);
	//get function
	string getFirstName();
	string getLastName();
	string getAccountId();

	int getBanlace(int index);
	void printTrade(ofstream&out,int type);//print appoint trade
	void printAllTrade(ofstream&out);//print all trade

	string funds[10] =
	{
		"Money Market",
		"Prime Money Market",
		"Long - Term Bond",
		"Short-Term Bond",
		"500 Index Fund",
		"Capital Value Fund",
		"Growth Equity Fund",
		"Growth Index Fund",
		"Value Fund",
		"Value Stock Index"
	};
private:
	string  accountId;
	string  firstName;
	string  lastName;
	string records[10];//store all trade
	int balance[10];//store balance
};

#endif // ASS5_ACCOUNT_H
