#pragma once

#include "Transactions.h"
#include <fstream>
#include <vector>

class CreditCard
{
public:
	CreditCard(double& rate, double& limit);
	~CreditCard();

	double getCardBalance();

	//Function that checks to see whether enough days have passed to add accrued interest
	//to the customer's balance
	//Input: current day since account opening
	//Output: balance changes if at least 30 days have passed, else no variables change;
	double getAccruedInterest() const;
	double getApr() const;
	int getCardNumber() const;
	double getCardLimit() const;
	void setDaysSinceOpening(int& day);
	void charge(double& amount);
	void payment(int& day, double& amount);
	void printHistory();
	static const int LENGTH_OF_CARD_NO = 8;
  
private:
	int card_number;
	double card_balance;
	double apr;
	double accrued_interest;
	double credit_limit;
	
	int days_since_opening;
	int day_of_last_interest_update;
	bool interest_applied_this_month = false;
	int days_in_year;
	std::vector<Transactions*> transaction_list;
	
	/*******************private functions*******************/
	/*****************************************************/
	void checkForApplyingInterest(int& day);
	void calculateInterest();

	//Function that saves payments and charges 
	//into transaction objects
	void keepRecordOfTransaction(std::string transaction, double& amount);

	//Function to check it the current year is a leap year. 
	//If so, changes the variable 'days_in_year'
	void checkForLeapYear(int& yr);
	
};

