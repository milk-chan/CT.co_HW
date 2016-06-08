#pragma once
#include "linked_list.h"

using namespace std;

///<summary>Describes an object, that stores all information about payments made by some person</summary>
class payments :
	public linked_list
{
private:
	string name;
	double sum;
public:

	///<summary>Creates new empty "payments" object</summary>
	payments();

	///<summary>Creates new empty "payments" object with person's name specified</summary>
	payments(string name);

	///<summary>Sets name of the person
	///<param name='name'>Name of a person</param>
	///</summary>
	void SetName(string name);

	///<summary>Returns name of a person</summary>
	string GetName();

	///<summary>Returns amount of money spent on all payments in this payment list</summary>
	double GetSum();

	///<summary>Sets amount of money spend on all payments in this payment list</summary>
	void SetSum(double sum);

	///<summary>Creates new payment and adds it to "payments"</summary>
	bool AddElement(string payment_desc, double amount_of_money);

	///<summary>Adds payment to "payments"</summary>
	bool AddElement(node * element);

	///<summary>Deletes the first payment from "payments"</summary>
	void DeleteElement();

	///<summary>Desctroys "payments"</summary>
	~payments();
};

