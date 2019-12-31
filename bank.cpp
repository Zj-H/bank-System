
#include "bank.h"

// empty


Bank::Bank() = default;

Bank::~Bank() = default;
//
void Bank::processTransactions(const string &FileName) 
{
	ifstream in;
	string str;

	in.open(FileName);
	if (in.is_open() == false)
	{
		cout << "can't open file --- " << FileName << endl;
		return;
	}
	while (!in.eof())
	{
		getline(in, str);
		tradeQueue.push(str);
		
	}
	in.close();
	processData(FileName);
	
}

void Bank::displayAllBankBalances() const
{	
	Accounts.printBalance();
}

void Bank::processData(string fileName)
{
	vector<string>splitStrings;//store string 
	ofstream out;
	out.open("BankTransOut.txt");
	out << "The command line argument(s) was " << fileName<<endl;
	Account*tempAccount=NULL;
	string str;
	string temp;
	char ch;
	string id;
	string type="";
	int int_id=0;
    unsigned size = tradeQueue.size();
	for (unsigned i = 0; i <size; i++)
	{	
		str = tradeQueue.front();
		splitStrings.clear();
		ch= str[0];
		istringstream iss(str);
		while (getline(iss, temp, ' '))//split string 
		{
			splitStrings.push_back(temp);
		
		}
		if (ch != 'O')
		{	
			
			id = splitStrings[1].substr(0, 4);//get AccountId
			type = splitStrings[1].substr(4, 2);
			int_id = atoi(id.c_str());//string to int
			if (Accounts.retrieve(int_id, tempAccount) == false)
			{
				out << "ERROR: Could not find Account " << id << " Transfer cancelled." << endl;
				tradeQueue.pop();
				continue;
			}
		}

		if (type.length() > 1)
		{	
			out << "ERROR:No such fund--"<<type << endl;
			tradeQueue.pop();
			continue;
		}
		switch (ch)
		{
		case 'O':
		{	
			type = "";
			id = splitStrings[3].substr(0, 4);
			int_id = atoi(id.c_str());
			Account *newAccount = new Account;
			if (Accounts.retrieve(int_id, newAccount) == true)
			{
				out << "ERROR:Account " << id << " is already open. Transaction refused." << endl;
			}
			else
			{	
				newAccount->setAccountId(id);
				newAccount->setFirstName(splitStrings[1]);
				newAccount->setLastName(splitStrings[2]);
				Accounts.insert(newAccount);
			}
			break;
			
		}
		case 'D':
		{
				int index = type[0] - 48;
				int count = atoi(splitStrings[2].c_str());
				tempAccount->setBalance(index, count);
				break;
		}
		case 'W':
		{
				int index = type[0] - 48;
				int count = atoi(splitStrings[2].c_str());
				int balance = tempAccount->getBanlace(index);
				if (balance < count)
				{	
					int cover = count - balance;
					if (index == 2 && (tempAccount->getBanlace(3) >= cover))
					{
						tempAccount->setBalance(2, -balance);
						tempAccount->setBalance(3, -cover);
						string r = "W " + id;
						r = r +" "+ to_string(cover);
						tempAccount->setTradeRecords(3, r);
					}
					else
						str = str + "(Failed)";
				}
					
				else
					tempAccount->setBalance(index, -count);
				break;
		}
		case 'T':
		{
			Account*transferAccount;
			string transferId = splitStrings[3].substr(0, 4);
			string transferType = splitStrings[3].substr(4, 2);
			int t_id = atoi(transferId.c_str());
			if (Accounts.retrieve(t_id, transferAccount) == false)
			{
				out << "ERROR: Could not find Account " << transferId << " Transfer cancelled." << endl;
				break;
			}
			if (transferType.length() > 1)
			{
				out << "ERROR:No such fund" << transferType << endl;
				break;
			}
			int t_index = transferType[0] - 48;
			int index = type[0] - 48;
			int count = atoi(splitStrings[2].c_str());
			int balance = tempAccount->getBanlace(index);

			if (count > balance)
				str += "(Failed)";
			else
			{	
				tempAccount->setBalance(index, -count);
				transferAccount->setBalance(t_index, count);
				string r = "D " + transferId;
				r = r + " " + splitStrings[2];
				transferAccount->setTradeRecords(t_index, r);
			}
			
			break;
		}
		
		case 'H':
		{	
			
			Accounts.retrieve(int_id, tempAccount);
			if(type.length()==0)
				tempAccount->printAllTrade(out);
			else
				tempAccount->printTrade(out,type[0] - 48);
			type = "";
			break;
		}
		default:
			break;
		}
		if (type.length()== 1)
		{
			
			Accounts.retrieve(int_id, tempAccount);
			tempAccount->setTradeRecords(type[0] - 48, str);
		}
		tradeQueue.pop();
	}
	out.close();
}