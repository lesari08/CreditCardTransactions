//By: Leslie Aririguzo
//Date: 3/23/17
//Title: Driver program to simulate credit card transactions

/*This Menu driven program asks the user for the hypothetical number of days
*that have passed since they opened their credit card. The program will then allow
*the user to make charges, payments, and queries about the account as well as open a new account */


#include "RunSimulation.h"

int main()
{

   RunSimulation* run_simulation_singleton = RunSimulation::getInstance();

   run_simulation_singleton->runSampleProgram();

	return 0;
}
