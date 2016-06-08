#include "stdafx.h"
#include "linked_list.h"


linked_list::linked_list()
{
	current = head = tail = NULL;
	length = 0;
	return;
}

linked_list::linked_list(string payment_desc, int amount_of_money)
{
	current = head = tail = new node(payment_desc, amount_of_money);
	length = 1;
	return;
}

bool linked_list::IsLast()
{
	return current==tail;
}

bool linked_list::IsEnd()
{
	return current == NULL;
}

bool linked_list::IsEmpty()
{
	return length==0;
}

int linked_list::GetLength()
{
	return length;
}

void linked_list::GotoStart()
{
	current = head;
}

void linked_list::GotoLast()
{
	current = tail;
}

void linked_list::GotoNext()
{
	current = current->next;
}

bool linked_list::AddElement(node * element)
{
	if (element == NULL)
	{
		return false;
	}
	else if (!IsEmpty())
	{
		GotoLast();
		current->next = element;
		tail = element;
	}
	else
	{
		current = tail = head = element;
	}

	length++;

	return true;
}

bool linked_list::AddElement(string payment_desc, double amount_of_money)
{
	node * element = new node(payment_desc, amount_of_money);

	if (element == NULL)
	{
		return false;
	}
	else if (!IsEmpty())
	{
		GotoLast();
		current->next = element;
		tail = element;
	}
	else
	{
		current = tail = head = element;
	}

	length++;

	return true;
}

void linked_list::DeleteElement()
{
	GotoStart();
	head = current->next;
	delete current;
	length--;
	GotoStart();
}

node * linked_list::GetElement()
{
	return current;
}

linked_list::~linked_list()
{
	while (length > 0)
	{
		DeleteElement();
	}
}
