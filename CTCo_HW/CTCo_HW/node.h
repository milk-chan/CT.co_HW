#pragma once
//#include <cstring>

using namespace std;

/// <summary>"nodes" store information about payments
/// </summary>
class node
{
public:
	string payment_desc;
	double amount_of_money;
	node * next;

	///<summary>Creates empty "node" element</summary>
	node();

	///<summary>Creates new "node" object
	///<param name='payment_desc'>Payment description</param>
	///<param name='amount_of_money'>Amount of money spent</param>
	///</summary>
	node(string payment_desc, double amount_of_money);

	///<summary>Destroys "node"</summary>
	~node();

};