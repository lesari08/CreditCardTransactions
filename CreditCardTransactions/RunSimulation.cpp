//Implementation file for RunSimulation class

#include "RunSimulation.h"
#include "CreditCard.h"
#include <iomanip>
#include <iostream>

RunSimulation* RunSimulation::instance = 0;

RunSimulation* RunSimulation::getInstance()
{
	if (instance == 0)
	{
		instance = new RunSimulation();
	}

	return instance;
}


void RunSimulation::runSampleProgram()
{
	double sample_apr = .35;
	double sample_limit = 1000;
	int choice = 0;

	//create a sample credit card
	default_card = new CreditCard(sample_apr, sample_limit);

	//push new card into our list
	card_list.push_back(default_card);

	std::cout << std::setw(50) << "Credit Card Management System" << std::endl;
	std::cout << std::setw(40) << std::internal << "Welcome" << std::endl << std::endl;

	//do...while loop contains the bulk of the simulation 
	//When loop ends (whenever a user enters 9), the program is over
	do {
		//menu() prints credit card options
		//the user can choose from
		menu();
		std::cin >> choice;

		if (choice != 9)
		{
			card_functions(choice);
		}

	} while (choice != 9);

	std::cout << "Goodbye" << std::endl;
}

void RunSimulation::menu()
{
	std::cout << "*****Menu options*****" << std::endl;
	std::cout << "Default card number: " << default_card->getCardNumber() << std::endl << std::endl;
	std::cout << "To check balance: Enter 1" << std::endl;
	std::cout << "To charge the card: Enter 2" << std::endl;
	std::cout << "To make a payment: Enter  3" << std::endl;
	std::cout << "To check accrued interest: Enter 4" << std::endl;
	std::cout << "To view account history: Enter 5" << std::endl;
	std::cout << "To apply for a brand new card: Enter 6" << std::endl;
	std::cout << "To switch your default card or to show all your active cards: Enter 7" << std::endl;
	std::cout << "\nTo Exit: Enter 9" << std::endl;
}

void RunSimulation::card_functions(int& choice)
{
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	//variable to save the number of days since account opening
	int days;
	double charge_amount;
	double payment;
	CreditCard *temp;
	int switch_selection;


	std::cout << "Enter number of days since account opening" << std::endl;
	std::cin >> days;
	default_card->setDaysSinceOpening(days);
	switch (choice)
	{
	case 1:  //1:check balance
		std::cout << "Current Balance: " << default_card->getCardBalance() << std::endl << std::endl;
		break;

	case 2: //2: Charge card
		std::cout << "How much would you like to charge to your credit card?" << std::endl;
		std::cin >> charge_amount;
		default_card->charge(charge_amount);
		break;

	case 3:  //3: Make payment
		std::cout << "Enter payment amount" << std::endl;
		std::cin >> payment;
		default_card->payment(days, payment);
		break;
	case 4:  //4: Print accrued interest
		std::cout << "Accrued Interest is: " << default_card->getAccruedInterest() << std::endl << std::endl;
		break;

	case 5:  //5: Print overview
		default_card->printHistory();
		break;
	case 6: //apply for a new card

		std::cout << "Enter 1 to apply for the Golden Members Card ($1000 Limit, 35%APR)" << std::endl;
		std::cout << "Enter 2 to apply for the Platinum Club Card ($5000 Limit, 40% APR)" << std::endl;
		std::cin >> switch_selection;
		createNewCard(switch_selection);
		break;
	case 7: //All cards
		printOrChangeCard();
		break;
	default:
		std::cout << "invalid Entry" << std::endl;
	}

}
//Function that prints each existing credit card user
//Then asks user if they would like to use a different card as their default
void RunSimulation::printOrChangeCard()
{
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	int col_width = 10;
	int entered_number;
	char choice;

	//true when the user enters an existing card number when prompted 
	bool valid_card_number = false;

	//print header for credit card list
	std::cout << std::setw(col_width) << "Card Number" << std::setw(col_width) << "APR" << std::setw(col_width) <<
		"Card Limit" << std::setw(col_width) << "Current Balance" << std::endl;

	//Print all credit cards
	for (int i = 0; i < card_list.size(); i++)
	{
		std::cout << std::setw(col_width) << card_list.at(i)->getCardNumber() <<
			std::setw(col_width) << card_list.at(i)->getApr() << std::setw(col_width) <<
			card_list.at(i)->getCardLimit() << std::setw(col_width) << card_list.at(i)->getCardBalance() <<
			std::endl;
	}
	std::cout << "Would you like to change your default card? Enter Y for yes" << std::endl;
	std::cout << "Enter any other key for No " << std::endl;
	std::cin >> choice;
	if (toupper(choice) == 'Y')
	{
		std::cout << "Please enter the card number that you want to use" << std::endl;
		std::cin >> entered_number;
		for (int i = 0; i < card_list.size(); i++)
		{
			if (entered_number == card_list.at(i)->getCardNumber())
			{
				default_card = card_list.at(i);
				valid_card_number = true;
			}
		}

		if (!valid_card_number)
		{
			std::cout << "Sorry, the number you entered is incorrect" << std::endl;
		}
	}

}

//Function that creates a new credit card object
//then saves the object into a list of existing credit cards
void RunSimulation::createNewCard(int &card_type)
{
	CreditCard *temp;
	double gold_apr = .35;
	double platinum_apr = .40;
	double gold_limit = 1000;
	double platinum_limit = 5000;

	//Validation loop to make sure 
	//a valid card choice was entered
	while (card_type < 1 || card_type > 2)
	{
		std::cout << "Invalid option: Please re-enter your choice" << std::endl;
		std::cin >> card_type;
	}

	temp = (card_type == 1) ? new CreditCard(gold_apr, gold_limit) : new CreditCard(platinum_apr, platinum_limit);

	//add new card to credit card list
	card_list.push_back(temp);

	std::cout << "Congrats you've been approved!" << std::endl;
	std::cout << "Your credit card number for this new card is:" << std::endl;
	std::cout << temp->getCardNumber() << std::endl << std::endl;
}
