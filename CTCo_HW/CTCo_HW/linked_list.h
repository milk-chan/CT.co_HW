#pragma once
#include "node.h"

///<summary>"linked_list" is a class that implements one-directional linked-list with "node" type elements</summary>
class linked_list
{
protected:
	node * current;
	node * head;
	node * tail;
	int length;

public:
	///<summary>Creates new empty "linked_list" object</summary>
	linked_list();

	///<summary>Creates new "linked_list" with one "node" element
	///<param name='name'>Person's name</param>
	///<param name='payment_desc'>Payment description</param>
	///<param name='amount_of_money'>Amount of money spent</param>
	///</summary>
	linked_list(string payment_desc, int amount_of_money);

	///<summary>Checks if pointer is pointing to the last element in the list</summary>
	bool IsLast();

	///<summary>Checks if pointer is pointing to NULL - the end of list is reached</summary>
	bool IsEnd();

	///<summary>Checks if the list is empty</summary>
	bool IsEmpty();

	///<summary>Returns length of the list</summary>
	int GetLength();

	///<summary>Moves pointer to the first element of the list</summary>
	void GotoStart();

	///<summary>Moves pointer to the last element of the list</summary>
	void GotoLast();

	///<summary>Moves pointer to the next element of the list</summary>
	void GotoNext();

	///<summary>Adds "node" element to the end of the list</summary>
	bool AddElement(node * element);

	///<summary>Creates "node" element and appends it to the end of the list</summary>
	bool AddElement(string payment_desc, double amount_of_money);

	///<summary>Deletes first element from the list</summary>
	void DeleteElement();

	///<summary>Returns pointer to pointed element in the list</summary>
	node * GetElement();

	///<summary>Destroys "linked-list"</summary>
	~linked_list();
};

