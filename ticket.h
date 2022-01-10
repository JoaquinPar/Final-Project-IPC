// #############################################################################################
//  Assignment: 2
//  Milestone : 4
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#ifndef TICKET_H_
#define TICKET_H_

#include "accountTicketingUI.h"

typedef struct Message {
    char acc_type;
    char name[COMMON_LENGTH];
    char message[151];
} Message;

typedef struct Ticket {
    int ticket_num;
    int acc_num;
    int ticket_stat;
    char subject[COMMON_LENGTH];
    int counter;
    struct Message messages[20];
} Ticket;

//Function which displays the header of the table for tickets
void ticketDisplayHeader();

//This function is in charge of printing the body for the table
void ticketDisplayBody(struct Ticket*, int);

//This function is in charge of printing the messages from the specified ticket by the user
void printMessages(struct Ticket*, struct Message*, int);

//This function is in charge of searching the Ticket struct array depending on the selection
//made by the user in the agent menu
int ticketSearch(struct Ticket*, int, int, int, int);

//Function searches the Ticket struct array for a match with the specified ticket number
int ticketSearchByNum(int, struct Ticket*, int, int);

//Function to search the Ticket struct array for a match with the specified account number
int ticketSearchByAccNum(struct Ticket*, int, int, int);

//This function adds a ticket to the account specified
void addTicket(struct Ticket*, struct Message*, struct Account*, int, int);

//This Function happens whenever the user chooses to edit a specific ticket, and it handles all the necesary
//processes
void editTicket(struct Ticket*, struct Account*, struct Account*, int);


void addMessage(struct Ticket*, struct Account*, struct Account*, int, int, int);

//Function which handles the necessary processes to add a message to a specific ticket
void messageSetup(struct Ticket*, struct Account*, struct Account*, char, int, int, int);

//This function loads tickets into the Ticket struct array from the file tickets.txt
int loadTickets(struct Ticket*, int);

//This function saves tickets from the Ticket struct array into the tickets.txt file
int saveTickets(struct Ticket*, int);

#endif // !TICKET_H_