#include"account.h"


Account::Account()
{	//init
	for (int i = 0; i < 10; i++)
		balance[i] = 0;
}
Account::~Account()
{
	
}
void Account::setAccountId(string id)
{
	accountId = id;
}
void Account::setFirstName(string name)
{
	firstName = name;
}
void Account::setLastName(string name)
{
	lastName = name;
}

void Account::setTradeRecords(int index,string record)
{
	if (index >= 10 || index < 0)
		return;
	record = "\t" + record;
	records[index] =records[index]+'\n' + record;
}
void Account::setBalance(int index, int count)
{	
	if (index >= 10 || index < 0)
		return;
	balance[index] += count;
}
string Account::getFirstName()
{
	return firstName;
}

string Account::getLastName()
{
	return lastName;
}
string Account::getAccountId()
{
	return accountId;
}
int Account::getBanlace(int index)
{
	return balance[index];
}
void Account::printTrade(ofstream &out,int type)
{
	out << "Displaying Transaction History for " << firstName << " " << lastName << " 's " ;
	out << funds[type] << ": $" << balance[type];
	out << records[type] << endl;
}
void Account::printAllTrade(ofstream&out)
{	
	out << "Displaying Transaction History for " << firstName << " " << lastName << " by fund."<<endl;

	for (int i = 0; i < 10; i++)
	{
		out << funds[i] << ": $" << balance[i];
		out << records[i];
		out << endl;
	}
}
