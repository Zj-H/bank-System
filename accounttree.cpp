#include "accounttree.h"
// empty

AccountTree::AccountTree()
{
	Root = NULL;
}

// Delete all nodes in BST
AccountTree::~AccountTree()
{
	clear();//delete
}

// Insert new account
bool AccountTree::insert(Account *Account) 
{	
	Node*n = new Node(Account);
	n->Left = NULL;
	n->Right = NULL;
	if (isEmpty() == true)
	{
		Root = n;
		return true;
	}
		
	else
	{	
		string id = n->Account->getAccountId();
		Node*temp = Root;
		Node*precursor = NULL;
		while (temp!=NULL)
		{
			precursor = temp;
			if (temp->Account->getAccountId().compare(id)>0)
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		if ((precursor->Account->getAccountId().compare(id)>0))
			precursor->Left = n;
		else
			precursor->Right = n;
	}
	return true;

}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const 
{
	string id =to_string(AccountNumber);//int to string
	Node*temp = Root;
	bool flag = false;
	while (temp!=NULL)
	{	
		if ((temp->Account->getAccountId().compare(id)==0))
		{
			Account = temp->Account;
			flag = true;
			break;
		}
		
		if ((temp->Account->getAccountId().compare(id)>0))
			temp = temp->Left;
		else
			temp = temp->Right;
	}
	return flag;
}

// Display information on all accounts
void AccountTree::display() const 
{
	preOrder(Root);

}

// delete all information in AccountTree
void AccountTree::clear() 
{
	postOrder(Root);
}

// check if tree is empty
bool AccountTree::isEmpty() const 
{	
	if (Root == NULL)
		return true;
	else
		return false;
}
//preOrder traversal   to print account info
void AccountTree::preOrder(Node*temp) const
{	
	
	if (temp != NULL)
	{
		cout << temp->Account->getFirstName() << " " << temp->Account->getLastName();
		cout << " Account ID: " << temp->Account->getAccountId() << endl;
		preOrder(temp->Left);
		preOrder(temp->Right);
	}
	
}
//postOrder traversal  to delete node.  free memory
void AccountTree::postOrder(Node*temp)
{
	if (temp != NULL)
	{
		postOrder(temp->Right);
		postOrder(temp->Left);
		delete temp->Account;
		delete temp;
		temp = NULL;
	}
}
//traversal to print balance
void AccountTree::travel(Node*temp)const
{
	ofstream out;
	out.open("BankTransOut.txt", ios::app);
	if (temp != NULL)
	{
		out << temp->Account->getFirstName() << " " << temp->Account->getLastName();
		out << " Account ID: " << temp->Account->getAccountId() << endl;
		for (int i = 0; i < 10; i++)
		{
			out << "\t"<<funds[i] << ": $"<<temp->Account->getBanlace(i) << endl;
		}
		out << endl;
		travel(temp->Left);
		travel(temp->Right);
	}
	out.close();
}

void AccountTree::printBalance()const
{
	travel(Root);
}