// #############################################################################################
//  Assignment: 2 
//  Milestone : 4
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "ticket.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"

//Will display the header for the table (Doesnt receive a value)
void displayAccountDetailHeader()
{
    printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
    printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");

    return;
}

//Will display the information for the table (receives an unmodifiable account pointer)
void displayAccountDetailRecord(const struct Account* account)
{
    int i;
    char* type_acc;
    char password[9];

    strcpy(password, account->login_details.password);

    for (i = 0; i < 9; i++)
        if (i % 2 != 0)
        {
            password[i] = '*';
        }

    if (account->acc_type == 'A')
        type_acc = "AGENT";
    else
        type_acc = "CUSTOMER";

    printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s", account->acc_number, type_acc,
        account->person_details.full_name, account->person_details.birth_year,
        account->person_details.income, account->person_details.country,
        account->login_details.login_name, password);
    printf("\n");

    return;
}

//Will manage the display of accounts, it will receive the accounts to be displayed and an int for the max index
void displayAllAccountDetailRecords(const struct Account account[], int max_num)
{
    int i;

    printf("\n");
    displayAccountDetailHeader();

    for (i = 0; i < max_num; i++)
    {
        if (account[i].acc_number != 0)
            displayAccountDetailRecord(&account[i]);
    }
}

//This function will be the entry point of the application, and will receive an Account array, and an int for the max index
void applicationStartup(struct AccountTicketingData* accTicketData)
{
    int array_index = 0;


    while (array_index != -1)
    {
        array_index = menuLogin(accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE);

        if (array_index != -1)
        {
            if (accTicketData->accounts[array_index].acc_type == 'A' && array_index != -2)
            {
                printf("\n");
                menuAgent(accTicketData, &accTicketData->accounts[array_index]);
            }
            else if (accTicketData->accounts[array_index].acc_type != 'A' && array_index != -2)
            {
                printf("\nERROR:  Access Denied.\n");
                pauseExecution();
            }
        }
    }

    printf("\n==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");

    return;
}
//This function will contain the Login menu, and will receive an Account array, and an int for the max index
int menuLogin(const struct Account account[], int max_num)
{
    int acc_num, array_index, selection, attempts = 3;
    int rtnValue = 0;
    char complete_exit;
    char user_login[101];
    char password[101];
    int good_login = 0;


    printf("==============================================\n");
    printf("Account Ticketing System - Login\n");
    printf("==============================================\n");
    printf("1) Login to the system\n");
    printf("0) Exit application\n");
    printf("----------------------------------------------\n");
    printf("\nSelection: ");
    selection = getIntFromRange(0, 1);

    if (selection == 1)
    {
        good_login = 0;
        do
        {
            printf("\nEnter the account#: ");
            acc_num = getPositiveInteger();

            array_index = findAccountIndexByAcctNum(acc_num, account, max_num, 0);

            printf("User Login        : ");
            getCString(user_login, 1, 100);

            printf("Password          : ");
            getCString(password, 1, 100);

            if (array_index != -1 && attempts > 0 && strcmp(user_login, account[array_index].login_details.login_name) == 0 &&
                strcmp(password, account[array_index].login_details.password) == 0)
            {
                rtnValue = array_index;
                good_login = 1;
            }
            else
            {
                attempts--;
                printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempts);
            }
        } while (good_login != 1 && attempts > 0);
    }
    else
    {
        printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
        complete_exit = getCharOption("yYnN");

        if (complete_exit == 'y' || complete_exit == 'Y')
            rtnValue = -1;
        else if (complete_exit == 'n' || complete_exit == 'N')
        {
            printf("\n");
            rtnValue = -2;
        }
    }

    return rtnValue;
}

//This function will display the agent menu, and will receive an editable array, an int for the max index, and the logged in user info
void menuAgent(struct AccountTicketingData* accTicketData, struct Account* const acc_details)
{
    int array_index;
    int ticket_index;
    int counter;
    int selection;
    int acc_num;
    int i;
    char delete_acc;
    int highest_acc;
    int is_highest = 0;
    int ticket_selection;
    int ticket_number;
    int recsSaved;

    do
    {
        printf("AGENT: %s (%d)\n", acc_details->person_details.full_name,
            acc_details->acc_number);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("5) List new tickets\n");
        printf("6) List active tickets\n");
        printf("7) List closed tickets\n");
        printf("8) Add a new ticket\n");
        printf("9) Manage a ticket\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");
        selection = getIntFromRange(0, 9);

        if (selection == 1)
        {
            array_index = findAccountIndexByAcctNum(0, accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE, 0);

            if (array_index != -1)
            {
                highest_acc = accTicketData->accounts[0].acc_number;

                do
                {
                    for (i = 0; i < accTicketData->ACCOUNT_MAX_SIZE; i++)
                    {
                        if (accTicketData->accounts[i].acc_number > highest_acc)
                            highest_acc = accTicketData->accounts[i].acc_number;

                        if (i == (accTicketData->ACCOUNT_MAX_SIZE - 1) && highest_acc == highest_acc)
                            is_highest = 1;
                    }

                } while (is_highest != 1);

                accTicketData->accounts[array_index].acc_number = highest_acc + 1;

                getAccount(&accTicketData->accounts[array_index]);
                printf("\n*** New account added! ***\n");
            }
            else
                printf("\nERROR: Account listing is FULL, call ITS Support!\n");

            pauseExecution();
        }
        else if (selection == 2)
        {
            printf("\nEnter the account#: ");
            acc_num = getPositiveInteger();

            array_index = findAccountIndexByAcctNum(acc_num, accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE, 0);

            if (array_index == -1)
                printf("ERROR: Account Not Found!\n");
            else if (array_index != -1)
            {
                updateAccount(&accTicketData->accounts[array_index]);
            }
        }
        else if (selection == 3)
        {
            printf("\nEnter the account#: ");
            acc_num = getPositiveInteger();

            if (acc_num == acc_details->acc_number)
            {
                printf("\nERROR: You can't remove your own account!\n");
                pauseExecution();
            }
            else
            {
                array_index = findAccountIndexByAcctNum(acc_num, accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE, 0);

                if (array_index != -1)
                {
                    printf("\n");
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&accTicketData->accounts[array_index]);

                    printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                    delete_acc = getCharOption("yYnN");

                    if (delete_acc == 'y' || delete_acc == 'Y')
                    {
                        ticket_index = 0;
                        counter = 0;

                        do
                        {
                            ticket_index = ticketSearchByAccNum(accTicketData->tickets, accTicketData->accounts[array_index].acc_number, ticket_index, accTicketData->TICKET_MAX_SIZE);

                            if (ticket_index != -1 && accTicketData->tickets[ticket_index].ticket_num != 0)
                            {
                                accTicketData->tickets[ticket_index].ticket_num = 0;
                                counter++;
                                ticket_index++;
                            }

                        } while (ticket_index != -1);

                        accTicketData->accounts[array_index].acc_number = 0;

                        printf("\n*** Account Removed! (%d ticket(s) removed) ***\n", counter);
                    }
                }
                else
                    printf("ERROR: Account not found!\n");

                pauseExecution();
            }
        }
        else if (selection == 4)
        {
            displayAllAccountDetailRecords(accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE);

            pauseExecution();
        }
        else if (selection == 5)
        {
            printf("\n");

            do
            {
                array_index = 0;

                ticketDisplayHeader();

                do
                {
                    array_index = ticketSearch(accTicketData->tickets, array_index, 1, 5, accTicketData->TICKET_MAX_SIZE);

                    if (array_index != -1 && accTicketData->tickets[array_index].ticket_stat != 0 &&
                        accTicketData->tickets[array_index].ticket_num != 0)
                    {
                        ticketDisplayBody(accTicketData->tickets, array_index);
                        array_index++;
                    }

                } while (array_index != -1);

                printf("------ ----- --------------- ------ ------------------------------ --------\n");

                printf("\nEnter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                scanf("%d", &ticket_selection);

                if (ticket_selection != 0)
                {
                    ticket_number = ticketSearchByNum(ticket_selection, accTicketData->tickets, 5, accTicketData->TICKET_MAX_SIZE);

                    if (ticket_number != -1)
                        printMessages(accTicketData->tickets, accTicketData->tickets->messages, ticket_number);

                    else
                        printf("\nERROR: Invalid ticket number.\n");

                    clearStandardInputBuffer();
                    pauseExecution();
                }
                else
                    printf("\n");

            } while (ticket_selection != 0);
        }
        else if (selection == 6)
        {
            printf("\n");

            do
            {
                array_index = 0;

                ticketDisplayHeader();

                do
                {
                    array_index = ticketSearch(accTicketData->tickets, array_index, 1, 6, accTicketData->TICKET_MAX_SIZE);

                    if (array_index != -1 && accTicketData->tickets[array_index].ticket_stat != 0 &&
                        accTicketData->tickets[array_index].ticket_num != 0)
                    {
                        ticketDisplayBody(accTicketData->tickets, array_index);
                        array_index++;
                    }

                } while (array_index != -1);

                printf("------ ----- --------------- ------ ------------------------------ --------\n");

                printf("\nEnter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                scanf("%d", &ticket_selection);

                if (ticket_selection != 0)
                {
                    ticket_number = ticketSearchByNum(ticket_selection, accTicketData->tickets, 6, accTicketData->TICKET_MAX_SIZE);

                    if (ticket_number != -1)
                        printMessages(accTicketData->tickets, accTicketData->tickets->messages, ticket_number);

                    else
                        printf("\nERROR: Invalid ticket number.\n");

                    clearStandardInputBuffer();
                    pauseExecution();
                }
                else
                    printf("\n");

            } while (ticket_selection != 0);
        }
        else if (selection == 7)
        {
            printf("\n");

            do
            {
                array_index = 0;

                ticketDisplayHeader();

                do
                {
                    array_index = ticketSearch(accTicketData->tickets, array_index, 0, 7, accTicketData->TICKET_MAX_SIZE);

                    if (array_index != -1 && accTicketData->tickets[array_index].ticket_stat == 0 &&
                        accTicketData->tickets[array_index].ticket_num != 0)
                    {
                        ticketDisplayBody(accTicketData->tickets, array_index);
                        array_index++;
                    }

                } while (array_index != -1);

                printf("------ ----- --------------- ------ ------------------------------ --------\n");

                printf("\nEnter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");
                scanf("%d", &ticket_selection);

                if (ticket_selection != 0)
                {
                    ticket_number = ticketSearchByNum(ticket_selection, accTicketData->tickets, 7, accTicketData->TICKET_MAX_SIZE);

                    if (ticket_number != -1)
                        printMessages(accTicketData->tickets, accTicketData->tickets->messages, ticket_number);

                    else
                        printf("\nERROR: Invalid ticket number.\n");

                    clearStandardInputBuffer();
                    pauseExecution();
                }
                else
                    printf("\n");

            } while (ticket_selection != 0);
        }
        else if (selection == 8)
        {
            addTicket(accTicketData->tickets, accTicketData->tickets->messages, accTicketData->accounts,
                accTicketData->ACCOUNT_MAX_SIZE, accTicketData->TICKET_MAX_SIZE);
            clearStandardInputBuffer();
        }
        else if (selection == 9)
        {
            editTicket(accTicketData->tickets, accTicketData->accounts, acc_details, accTicketData->TICKET_MAX_SIZE);
            printf("\n");
        }
    } while (selection != 0);

    printf("\nSaving session modifications...\n");
    recsSaved = saveAccounts(accTicketData->accounts, accTicketData->ACCOUNT_MAX_SIZE);
    printf("   %d account(s) saved.\n", recsSaved);
    recsSaved = saveTickets(accTicketData->tickets, accTicketData->TICKET_MAX_SIZE);
    printf("   %d ticket(s) saved.", recsSaved);

    printf("\n### LOGGED OUT ###\n\n");

    return;
}

//This functino will find the index of the acc_num provided, it will receive the acc number, the array to be searched, an int for the max index
//and an integer determining if it is requred to ask for acc num
int findAccountIndexByAcctNum(int acc_num, const struct Account account[], int max_num, int prompt)
{
    int i;
    int rtnValue = 0;

    if (prompt != 0)
    {
        printf("\nEnter your account#: ");
        scanf("%d", &acc_num);
    }

    for (i = 0; i < max_num; i++)
    {
        if (account[i].acc_number == acc_num)
        {
            rtnValue = i;
            break;
        }
        else
            rtnValue = -1;
    }

    return rtnValue;
}
