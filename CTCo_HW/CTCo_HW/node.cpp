#include "stdafx.h"
#include "node.h"


node::node()
{
	this->next = NULL;
}

node::node(string payment_desc, double amount_of_money)
{
	this->payment_desc = payment_desc;
	this->amount_of_money = amount_of_money;
	this->next = NULL;
}

node::~node()
{
	/// Nothing to do here...
}
