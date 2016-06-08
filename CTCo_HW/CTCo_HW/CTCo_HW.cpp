// CTCo_HW.cpp : Defines the entry point for the console application.
// Code developed in Visual Studio 2015

#include "stdafx.h"
#include "payments.h"
using namespace std;

int main();
void CreatePaymentList(payments * payment_records);

int main()
{
	// Getting data about payments
	string amount_of_participants_str;
	int amount_of_participants = 0;

	while (true) {
		cout << "Please enter amount of participants: ";
		getline(cin, amount_of_participants_str);

		// This code converts from string to number safely.
		stringstream myStream(amount_of_participants_str);
		if (myStream >> amount_of_participants)
			if (amount_of_participants > 0)
				break;
		cout << "Invalid number, please try again!" << endl;
	}
	cout << endl;

	// Creating array of payments
	payments ** payment_records = new payments*[amount_of_participants];

	// String to store input before it's being processed
	string temp;

	// Adding names to payment-lists
	for (int i = 0; i < amount_of_participants; i++)
	{
		payment_records[i] = new payments;
		cout << "Please enter name of the " << i + 1 << " participant: ";
		getline(cin, temp);
		payment_records[i]->SetName(temp);
		cout << endl;
	}

	// Fulling data into payment lists
	for (int i = 0; i < amount_of_participants; i++)
	{
		CreatePaymentList(payment_records[i]);
	}

	// Getting average sum spent across all payment-lists
	double average_amount_of_money = 0;

	for (int i = 0; i < amount_of_participants; i++)
	{
		average_amount_of_money += payment_records[i]->GetSum();
	}

	cout << "Total money spent: " << average_amount_of_money << "$" << endl;

	average_amount_of_money /= amount_of_participants;

	cout << "Average money spent by person: " << average_amount_of_money << "$" << endl;

	// Dividing payment-lists into groups
	//		1) recipients - who recieves transactions (spent more than avg)
	//		2) donors - who does transactions (spent less than avg)
	//		3) nontransfers - who doesn't do or recieve any transactions (spent = avg)
	
	int amount_of_recipients = 0;
	int amount_of_donors = 0;
	int amount_of_nontransfers = 0;

	// Getting amount of people in each group
	for (int i = 0; i < amount_of_participants; i++)
	{
		if (payment_records[i]->GetSum() > average_amount_of_money)
		{
			amount_of_recipients++;
		}
		else if (payment_records[i]->GetSum() < average_amount_of_money)
		{
			amount_of_donors++;
		}
		else
		{
			amount_of_nontransfers++;
		}
	}

	// Creating arrays for this groups
	payments ** recipient_payment_records = new payments*[amount_of_recipients];
	payments ** donor_payment_records = new payments*[amount_of_donors];
	payments ** nontransfer_payment_records = new payments*[amount_of_nontransfers];

	// Sorting payment_records into 3 groups

	int counter_recipients = 0; // Counter to know where an array element should be copied
	int counter_donors = 0;
	int counter_nontransfers = 0;

	for (int i = 0; i < amount_of_participants; i++)
	{
		if (payment_records[i]->GetSum() > average_amount_of_money)
		{
			recipient_payment_records[counter_recipients++] = payment_records[i];
		}
		else if (payment_records[i]->GetSum() < average_amount_of_money)
		{
			donor_payment_records[counter_donors++] = payment_records[i];
		}
		else
		{
			nontransfer_payment_records[counter_nontransfers++] = payment_records[i];
		}
	}

	cout << endl << "Spent more than average:" << endl;

	// Just ot test structure
	for (int i = 0; i < amount_of_recipients; i++)
	{
		cout << recipient_payment_records[i]->GetName() << ":\t" << recipient_payment_records[i]->GetSum() << "$\n";
		recipient_payment_records[i]->GotoStart();
		node * temp = recipient_payment_records[i]->GetElement();
		while (!recipient_payment_records[i]->IsEnd())
		{
			temp = recipient_payment_records[i]->GetElement();
			cout << "\t" << temp->payment_desc << ": " << temp->amount_of_money << "$\n";
			recipient_payment_records[i]->GotoNext();
		}
	}

	cout << endl << "Spent less than average:" << endl;

	for (int i = 0; i < amount_of_donors; i++)
	{
		cout << donor_payment_records[i]->GetName() << ":\t" << donor_payment_records[i]->GetSum() << "$\n";
		donor_payment_records[i]->GotoStart();
		node * temp = donor_payment_records[i]->GetElement();
		while (!donor_payment_records[i]->IsEnd())
		{
			temp = donor_payment_records[i]->GetElement();
			cout << "\t" << temp->payment_desc << ": " << temp->amount_of_money << "$\n";
			donor_payment_records[i]->GotoNext();
		}
	}

	cout << endl << "Spent as much as average:" << endl;

	for (int i = 0; i < amount_of_nontransfers; i++)
	{
		cout << nontransfer_payment_records[i]->GetName() << ":\t" << nontransfer_payment_records[i]->GetSum() << "$\n";
		nontransfer_payment_records[i]->GotoStart();
		node * temp = nontransfer_payment_records[i]->GetElement();
		while (!nontransfer_payment_records[i]->IsEnd())
		{
			temp = nontransfer_payment_records[i]->GetElement();
			cout << "\t" << temp->payment_desc << ": " << temp->amount_of_money << "$\n";
			nontransfer_payment_records[i]->GotoNext();
		}
	}

	cout << endl << "Transaction to be made:" << endl;

	bool transfer_is_done; // Used to know if transfer is already done and we can go to next iteration of do-while cycle
	int amount_of_recipients_got_money_back = 0;

	// Making tansfers...
	do
	{
		transfer_is_done = false;

		// Checking if there is transfers to be done
		// if so, geetting out from here (do-while)
		if (amount_of_recipients_got_money_back == amount_of_recipients)
			break;

		// Firstly checking for one-payment transfers...
		for (int i = 0; i < amount_of_recipients; i++)
		{
			for (int j = 0; j < amount_of_donors; j++)
			{
				if (recipient_payment_records[i] == NULL || donor_payment_records[j] == NULL)
				{
					continue;
				}
				// If there is one-payment transfer - doing it right now!
				else if ((recipient_payment_records[i]->GetSum() - average_amount_of_money) ==
					(average_amount_of_money - donor_payment_records[j]->GetSum()))
				{
					cout << donor_payment_records[j]->GetName() << " -> " <<
						recipient_payment_records[i]->GetName() << ": " <<
						average_amount_of_money - donor_payment_records[j]->GetSum() << "$" << endl;
					delete recipient_payment_records[i];
					amount_of_recipients_got_money_back++;	// One more recipient got money back!
					delete donor_payment_records[j];
					recipient_payment_records[i] = NULL;
					donor_payment_records[j] = NULL;
					
					// Transfer is done!
					transfer_is_done = true;
					break;
				}
			}
			if (transfer_is_done) break;
		}
		// Going to next iteration if transfer is done...
		if (transfer_is_done) continue;

		// If there is no any one-payment transfers, looking for person with maximum overpay and person with maximum underpay
		int maximum_recipient_overpay = 0;
		int maximum_recipient_overpay_number = 0;

		for (int i = 0; i < amount_of_recipients; i++)
		{
			if (recipient_payment_records[i] == NULL)
			{
				continue;
			}
			else if (recipient_payment_records[i]->GetSum() > maximum_recipient_overpay)
			{
				maximum_recipient_overpay = recipient_payment_records[i]->GetSum();
				maximum_recipient_overpay_number = i;
			}
		}

		int maximum_donor_underpay = INT_MAX;
		int maximum_donor_underpay_number = 0;

		for (int i = 0; i < amount_of_donors; i++)
		{
			if (donor_payment_records[i] == NULL)
			{
				continue;
			}
			else if (donor_payment_records[i]->GetSum() < maximum_donor_underpay)
			{
				maximum_donor_underpay = donor_payment_records[i]->GetSum();
				maximum_donor_underpay_number = i;
			}
		}

		// Making transfer between these people
		if (average_amount_of_money - maximum_donor_underpay < maximum_recipient_overpay - average_amount_of_money)
		{
			cout << donor_payment_records[maximum_donor_underpay_number]->GetName() << " -> " <<
				recipient_payment_records[maximum_recipient_overpay_number]->GetName() << ": " <<
				average_amount_of_money - maximum_donor_underpay << "$" << endl;

			recipient_payment_records[maximum_recipient_overpay_number]->
				SetSum(recipient_payment_records[maximum_recipient_overpay_number]->GetSum()
					- (average_amount_of_money - maximum_donor_underpay));
			delete donor_payment_records[maximum_donor_underpay_number];
			donor_payment_records[maximum_donor_underpay_number] = NULL;
		}
		else
		{
			cout << donor_payment_records[maximum_donor_underpay_number]->GetName() << " -> " <<
				recipient_payment_records[maximum_recipient_overpay_number]->GetName() << ": " <<
				maximum_recipient_overpay - average_amount_of_money << "$" << endl;
			
			donor_payment_records[maximum_donor_underpay_number]->
				SetSum(donor_payment_records[maximum_donor_underpay_number]->GetSum()
					+ (maximum_recipient_overpay - average_amount_of_money));
			delete recipient_payment_records[maximum_recipient_overpay_number];
			amount_of_recipients_got_money_back++;	// One more recipient got money back!
			recipient_payment_records[maximum_recipient_overpay_number] = NULL;
		}
	} while (amount_of_recipients_got_money_back != amount_of_recipients);
	
	cout << endl;

	system("pause");
	return 0;
}

void CreatePaymentList(payments * payment_records)
{
	string name;
	string amount_of_money_str;
	double amount_of_money;

	int counter = 1;

	cout << "Please enter description of " << payment_records->GetName() << "'s payment #" << counter << " [\"c\" to cancel]: ";
	getline(cin, name);

	while (name != "c")
	{
		while (true) {
			cout << "Please enter amount of money spent: ";
			getline(cin, amount_of_money_str);

			// This code converts from string to number safely.
			stringstream myStream(amount_of_money_str);
			if (myStream >> amount_of_money)
				if (amount_of_money > 0)
					break;
			cout << "Invalid number, please try again!" << endl;
		}
		cout << endl;
		payment_records->AddElement(name, amount_of_money);
		counter++;
		cout << "Please enter description of " << payment_records->GetName() << "'s payment #" << counter << " [\"c\" to cancel]: ";
		getline(cin, name);
	}
	cout << endl;
	return;
}