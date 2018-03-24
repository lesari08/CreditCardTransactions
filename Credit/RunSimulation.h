//By: Leslie Aririguzo
//Class containing functions that
//run simulated credit card transactions

#pragma once

#include <iostream>
#include "CreditCard.h"
#include <vector>

class RunSimulation
{
public:
	static RunSimulation* getInstance();
	void runSampleProgram();
private:
	RunSimulation() {};
	static  RunSimulation *instance;

	//Function to display menu options
	void menu();

	//Function that contains a switch statement
	//the case statements include different methods
	//to access or manipulate card information
	void card_functions(int& choice);

	//Function that prints all existing credit cards
	//Gives user the option to switch their default card
	//giving them the ability to make payments or charges on 
	//a different card
	void printOrChangeCard();

	//Function to create a new credit card
	//Gives user two different cards to choose from 
	void createNewCard(int &type);


	std::vector<CreditCard*>card_list;
	std::vector <CreditCard*>::iterator itr;
	CreditCard* default_card;

};

