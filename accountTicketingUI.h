// #############################################################################################
//  Assignment: 2
//  Milestone : 4
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#ifndef ACCOUNTTICKETING_H_
#define ACCOUNTTICKETING_H_

#include "account.h"
#include "ticket.h"

typedef struct AccountTicketingData {
    struct Account* accounts; // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    struct Ticket* tickets; // array of tickets
    const int TICKET_MAX_SIZE; // maximum elements for ticket array
} AccountTicketingData;

//Will display the header for the table (Doesnt receive a value)
void displayAccountDetailHeader();

//Will display the information for the table (receives an unmodifiable account pointer)
void displayAccountDetailRecord(const struct Account*);

//This function will be the entry point of the application, and will receive an Account array, and an int for the max index
void applicationStartup(struct AccountTicketingData*);

//This function will contain the Login menu, and will receive an Account array, and an int for the max index
int menuLogin(const struct Account[], int);

//This function will display the agent menu, and will receive an editable array, an int for the max index, and the logged in user info
void menuAgent(struct AccountTicketingData*, struct Account* const);

//This functino will find the index of the acc_num provided, it will receive the acc number, the array to be searched, an int for the max index
//and an integer determining if it is requred to ask for acc num
int findAccountIndexByAcctNum(int, const struct Account[], int, int);

//Will manage the display of accounts, it will receive the accounts to be displayed and an int for the max index
void displayAllAccountDetailRecords(const struct Account[], int);

#endif // !ACCOUNTTICKETING_H_