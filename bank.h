
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>
#include<queue>
#include<sstream>
#include<string.h>
using namespace std;

class Bank 
{
public:
  Bank();
  ~Bank();
  void processTransactions(const string &FileName);
  void displayAllBankBalances() const;
  void processData(string fileName);//process trade
private:
  queue<string>tradeQueue;//queue. to store all trade
  AccountTree Accounts;
};
#endif // ASS5_BANK_H
