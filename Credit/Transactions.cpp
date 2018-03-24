//Implementation file for Transactions Class

#include "Transactions.h"
#include <iostream>
#include <iomanip>
#include <string>

Transactions::Transactions(const int &d, const std::string &ty,
	const double &am, const double &result, const double &interest)
{
	day = d;
	type = ty;
	amount = am;
	resulting_balance = result;
	accrued_interest = interest;
}

//Function that prints individual transactions
void Transactions::print() const
{
	int col_width = 20;
	std::cout << day << std::setw(col_width) << type << std::setw(col_width) <<
		amount << std::setw(col_width) << resulting_balance << std::setw(col_width) <<
		accrued_interest << std::endl;
}
