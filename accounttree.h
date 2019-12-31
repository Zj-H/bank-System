
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree 
{
public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;
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
  //print Balance
  void printBalance()const;
private:
  class Node {
  public:
    explicit Node(Account *Account)
        : Account{Account}, Right{nullptr}, Left{nullptr} {};
    Account *Account;
    Node *Right;
    Node *Left;
  };
  Node *Root;
  void preOrder(Node*temp)const;//Preorder traversal
  void postOrder(Node*temp);//postOrder traversal
  void travel(Node*temp)const;//travel all Account;
  
};
#endif // ASS5_ACCOUNTTREE_H
