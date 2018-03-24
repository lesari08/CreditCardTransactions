//Class to keep records of credit card transactions

#pragma once

#include <iostream>
class Transactions {
public:
	Transactions(const int &d, const std::string &t, const double &am,
		const double &res, const double &interest);

	//Print individual transaction objects
	void print() const;

private:

	int day;
	std::string type;
	double amount;
	double resulting_balance;
	double accrued_interest;


};