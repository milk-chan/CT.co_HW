#include "stdafx.h"
#include "payments.h"


payments::payments() : linked_list()
{
	sum = 0;
}

payments::payments(string name) : linked_list()
{
	sum = 0;
	SetName(name);
}

void payments::SetName(string name)
{
	this->name = name;
}

string payments::GetName()
{
	return name;
}

double payments::GetSum()
{
	return sum;
}

void payments::SetSum(double sum)
{
	this->sum = sum;
}

bool payments::AddElement(string payment_desc, double amount_of_money)
{
	this->sum += amount_of_money;
	return linked_list::AddElement(payment_desc, amount_of_money);
}

bool payments::AddElement(node * element)
{
	this->sum += element->amount_of_money;
	return linked_list::AddElement(element);
}

void payments::DeleteElement()
{
	GotoStart();
	sum -= current->amount_of_money;
	linked_list::DeleteElement();
}


payments::~payments()
{
}
