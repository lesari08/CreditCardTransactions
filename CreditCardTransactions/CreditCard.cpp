//implementation file for CreditCard Class

#include <iostream>
#include <string>
#include <cmath>
#include "CreditCard.h"
#include <random>
#include <time.h>
#include <iomanip>

#include "Transactions.h"

CreditCard::CreditCard(double& rate, double& limit)
{
	apr = rate;
	credit_limit = limit;

	card_balance = 0.0;
	accrued_interest = 0.0;
	days_since_opening = 0;
	day_of_last_interest_update = 0;
	days_in_year = 365;

	//generate a random credit card number
	srand(time(0));

	int num = 0;
	for (int i = 0; i < LENGTH_OF_CARD_NO; i++) {
		num = num + pow(rand() % 10 + 10, i);
	}
	card_number = num;

}


void CreditCard::calculateInterest()
{
	accrued_interest = accrued_interest + card_balance * (apr / days_in_year) * (days_since_opening - day_of_last_interest_update);

	checkForApplyingInterest(days_since_opening);

	day_of_last_interest_update = days_since_opening;

}

//Function that saves each transaction (charges and payments)
//Saves each in a new transaction object. that new object will then be added
//to a transaction list for future retrieval
void CreditCard::keepRecordOfTransaction(std::string transaction, double & amount)
{
	Transactions *temp;

	temp = new Transactions(days_since_opening, transaction, amount, card_balance, accrued_interest);

	transaction_list.push_back(temp);

	int col_width = 20;
	std::string interest_applied_status;
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	//retrieve the 0 or 1 returned from the boolean variable, 
   //then represent the false in the form of a string
	interest_applied_status = (interest_applied_this_month == true) ? "true" : "false";

}


double CreditCard::getCardBalance()
{
	calculateInterest();
	return card_balance;
}
//Function that checks if it is time to add the accrued interest
//to the total card balance based on the day
void CreditCard::checkForApplyingInterest(int& day)
{
	if (day >= 0)
	{
		if (days_since_opening > 29 && (interest_applied_this_month == false))
		{
			card_balance = card_balance + accrued_interest;
			interest_applied_this_month = true;
		}
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
	}
}



double CreditCard::getAccruedInterest() const
{
	return accrued_interest;
}

double CreditCard::getApr() const
{
	return apr;
}

int CreditCard::getCardNumber() const
{
	return card_number;
}

double CreditCard::getCardLimit() const
{
	return credit_limit;
}

void CreditCard::setDaysSinceOpening(int& day)
{
	//check if the day passed into the function has already passed
	//If so to ask the user to re-enter a new data
	while (day < days_since_opening)
	{
		std::cout << "Our records indicate that more days have passed then what has been entered" << std::endl;
		std::cout << "Please re-enter the number of days that have passed since the account's opening" << std::endl;
		std::cin >> day;
	}
	days_since_opening = day;
}


void CreditCard::charge(double& amount)
{
	if (amount <= (credit_limit - card_balance))
	{
		//Calculate the current interest before the card balance is updated
		calculateInterest();

		card_balance = card_balance + amount;

		keepRecordOfTransaction("charge", amount);

		std::cout << "Charge of:$" << amount << " completed" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Denied: charge exceeds funds available" << std::endl;
	}
}

void CreditCard::payment(int& day, double& amount)
{
	if (amount > 0)
	{
		//Calculate the current interest before the card balance is updated
		calculateInterest();

		if (amount <= card_balance)
		{
			card_balance = card_balance - amount;
			std::cout << "Payment completed " << std::endl;
		}
		else
		{
			card_balance = 0;
			std::cout << "Balance is now zero but client has overpaid! " << std::endl;
		}

		keepRecordOfTransaction("payment", amount);
	}

}
//Function that prints the card holders transaction history
//Output contains columns for day of transaction, type of transaction, amount involved
//balance after transaction, accrued interest, and a whether or not the interest has been applied
//to the card's total balance 
void CreditCard::printHistory()
{
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	calculateInterest();

	int col_width = 20;

	std::cout << "Overview for Card Number:" << card_number << std::endl;
	std::cout << "Day" << std::setw(col_width) << "Transaction" << std::setw(col_width / 2) <<
		"Amount" << std::setw(col_width / 2) << "Balance" << std::setw(col_width) <<
		"Accrued Interest" << std::endl << std::endl;

	for (int i = 0; i < transaction_list.size(); i++)
	{
		transaction_list.at(i)->print();
	}

	std::cout << "Current Balance:" << card_balance << std::endl << std::endl;
	std::cout << "Current credit Limit:" << credit_limit << std::setw(10) << "APR:" <<
		apr << std::endl << std::endl;


}

void CreditCard::checkForLeapYear(int & yr)
{
	if (yr % 4 == 0)
	{
		if (yr % 100 == 0)
		{
			if (yr % 400 == 0) {
				//leap year
				days_in_year = 366;
			}
		}
		else
			days_in_year = 366;
	}
}

CreditCard::~CreditCard()
{
	//deallocate the memory used by the transaction list pointer objects
	for (std::vector<Transactions*>::iterator it = transaction_list.begin(); it != transaction_list.end(); ++it)
	{
		delete (*it);
	}
	transaction_list.clear();
}