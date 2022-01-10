// #############################################################################################
//  Assignment: 2 
//  Milestone : 2
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"

void ticketDisplayHeader()
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");

    return;
}

void ticketDisplayBody(struct Ticket* tickets, int index)
{
    char* status;

    if (tickets[index].ticket_stat == 1)
        status = "ACTIVE";
    else
        status = "CLOSED";

    printf("%06d %05d %-15s %-6s %-30s %5d\n", tickets[index].ticket_num, tickets[index].acc_num,
        tickets[index].messages->name, status, tickets[index].subject, tickets[index].counter);

    return;
}

void printMessages(struct Ticket* tickets, struct Message* messages, int index)
{
    int i;
    char* status;
    char* type_acc;
    int new_line = 0;

    if (tickets[index].ticket_stat == 1)
        status = "ACTIVE";
    else
        status = "CLOSED";

    printf("\n================================================================================\n");
    printf("%06d (%-6s) Re: %s\n", tickets[index].ticket_num, status, tickets[index].subject);
    printf("================================================================================\n");

    for (i = 0; i < 20; i++)
    {
        if (strcmp(tickets[index].messages[i].message, "") == 0)
            break;
        else
        {
            if (tickets[index].messages[i].acc_type == 'A')
                type_acc = "AGENT";
            else
                type_acc = "CUSTOMER";

            if (new_line == 0)
            {

            }
            else
                printf("\n");

            printf("%s (%s):\n", type_acc, tickets[index].messages[i].name);

            if (tickets[index].messages[i].acc_type == 'A' || tickets[index].messages[i].acc_type == 'C')
                printf("   %s\n", tickets[index].messages[i].message);

            new_line++;
        }
    }
    return;
}

int ticketSearch(struct Ticket* tickets, int prev_index, int num_to_search, int selection, int size)
{
    int i;
    int rtnValue = 0;

    if (selection == 5)
    {
        for (i = prev_index; i < size; i++)
        {
            if (tickets[i].ticket_stat != 0 && tickets[i].counter == num_to_search &&
                tickets[i].ticket_num != 0)
            {
                rtnValue = i;
                break;
            }
            else
            {
                rtnValue = -1;
            }
        }
    }
    else if (selection == 6)
    {
        for (i = prev_index; i < size; i++)
        {
            if (tickets[i].ticket_stat != 0 && tickets[i].ticket_stat == num_to_search &&
                tickets[i].ticket_num != 0)
            {
                rtnValue = i;
                break;
            }
            else
            {
                rtnValue = -1;
            }
        }
    }
    else if (selection == 7)
    {
        for (i = prev_index; i < size; i++)
        {
            if (tickets[i].ticket_num != 0 && tickets[i].ticket_stat == num_to_search)
            {
                rtnValue = i;
                break;
            }
            else
            {
                rtnValue = -1;
            }
        }
    }
    else if (selection == 8)
    {
        for (i = prev_index; i < size; i++)
        {
            if (tickets[i].ticket_num == 0)
            {
                rtnValue = i;
                break;
            }
            else
            {
                rtnValue = -1;
            }
        }
    }

    return rtnValue;
}

int ticketSearchByNum(int ticket_num, struct Ticket* tickets, int option, int size)
{
    int i;
    int rtnValue = 0;

    if (option == 5)
    {
        for (i = 0; i < size; i++)
        {
            if (tickets[i].ticket_num == ticket_num && tickets[i].ticket_stat == 1 &&
                tickets[i].counter == 1)
            {
                rtnValue = i;
                break;
            }
            else
                rtnValue = -1;
        }
    }
    else if (option == 6)
    {
        for (i = 0; i < size; i++)
        {
            if (tickets[i].ticket_num == ticket_num && tickets[i].ticket_stat == 1)
            {
                rtnValue = i;
                break;
            }
            else
                rtnValue = -1;
        }
    }
    else if (option == 7)
    {
        for (i = 0; i < size; i++)
        {
            if (tickets[i].ticket_num == ticket_num && tickets[i].ticket_stat == 0)
            {
                rtnValue = i;
                break;
            }
            else
                rtnValue = -1;
        }
    }

    return rtnValue;
}

int ticketSearchByAccNum(struct Ticket* tickets, int account_num, int past_index, int size)
{
    int i;
    int rtnValue = 0;

    for (i = past_index; i < size; i++)
    {
        if (tickets[i].acc_num == account_num)
        {
            rtnValue = i;
            break;
        }
        else
            rtnValue = -1;
    }

    return rtnValue;
}

void addTicket(struct Ticket* tickets, struct Message* messages, struct Account* accounts, int acc_size,
    int ticket_size)
{
    int highest_ticket;
    int is_highest = 0;
    int ticket_index = 0;
    int add_ticket = 0;
    char confirm;
    int account_num;
    int index;
    int i;

    printf("\nEnter the account#: ");
    scanf("%d", &account_num);

    index = findAccountIndexByAcctNum(account_num, accounts, acc_size, 0);

    for (i = 0; i < acc_size; i++)
    {
        if (accounts[i].acc_type != 'A' && accounts[i].acc_number == account_num)
            break;
        else if (accounts[i].acc_type == 'A' && accounts[i].acc_number == account_num)
        {
            printf("\nERROR: Agent accounts can't have tickets!\n");
            add_ticket = 1;
            break;
        }
        else if (i == acc_size - 1)
        {
            printf("\nERROR: Account not found!\n");
            add_ticket = 1;
        }
    }

    if (add_ticket == 0)
    {
        printf("\n");
        displayAccountDetailHeader();
        displayAccountDetailRecord(&accounts[index]);

        clearStandardInputBuffer();

        printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
        confirm = getCharOption("yYnN");

        if (confirm == 'y' || confirm == 'Y')
        {
            ticket_index = ticketSearch(tickets, ticket_index, 0, 8, ticket_size);

            highest_ticket = tickets[0].ticket_num;

            do
            {
                for (i = 0; i < ticket_size; i++)
                {
                    if (tickets[i].ticket_num > highest_ticket)
                        highest_ticket = tickets[i].ticket_num;

                    if (i == (ticket_size - 1) && highest_ticket == highest_ticket)
                    {
                        is_highest = 1;
                    }
                }
            } while (is_highest != 1);

            tickets[ticket_index].ticket_num = highest_ticket + 1;

            strcpy(tickets[ticket_index].messages->name, accounts[index].person_details.full_name);
            tickets[ticket_index].acc_num = accounts[index].acc_number;

            printf("\nNew Ticket (Ticket#:%06d)\n", tickets[ticket_index].ticket_num);
            printf("----------------------------------------\n");
            printf("Enter the ticket SUBJECT (30 chars. maximum): ");
            scanf(" %30[^\n]", tickets[ticket_index].subject);
            printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
            clearStandardInputBuffer();
            scanf(" %150[^\n]", tickets[ticket_index].messages[0].message);

            tickets[ticket_index].ticket_stat = 1;

            printf("\n*** New ticket created! ***\n");
        }
    }
    pauseExecution();

    return;
}

void editTicket(struct Ticket* tickets, struct Account* accounts, struct Account* const acc_details, int size)
{
    int ticket_number;
    int ticket_found = 0;
    int selection = 0;
    int index = 0;
    int i;
    char* status;
    char close_active;

    printf("\nEnter ticket number: ");
    scanf("%d", &ticket_number);

    for (i = 0; i < size; i++)
    {
        if (tickets[i].ticket_num == ticket_number)
        {
            index = i;
            ticket_found = 1;
            break;
        }
    }

    if (ticket_found != 0)
    {
        do
        {
            if (tickets[index].ticket_stat == 1)
                status = "ACTIVE";
            else
                status = "CLOSED";

            printf("\n----------------------------------------\n");
            printf("Ticket %06d - Update Options\n", tickets[index].ticket_num);
            printf("----------------------------------------\n");
            printf("Status  : %s\n", status);
            printf("Subject : %s\n", tickets[index].subject);
            printf("Acct#   : %d\n", tickets[index].acc_num);
            printf("Customer: %s\n", tickets[index].messages->name);
            printf("----------------------------------------\n");
            printf("1) Add CUSTOMER message\n");
            printf("2) Add AGENT message\n");
            printf("3) Close ticket\n");
            printf("4) Re-activate ticket\n");
            printf("0) Done\n");
            printf("Selection: ");
            selection = getIntFromRange(0, 4);

            if (selection == 1)
            {
                addMessage(tickets, accounts, acc_details, size, index, selection);
            }
            else if (selection == 2)
            {
                addMessage(tickets, accounts, acc_details, size, index, selection);
            }
            else if (selection == 3)
            {
                if (tickets[index].ticket_stat == 0)
                {
                    printf("\nERROR: Ticket is already closed!\n");

                }
                else
                {
                    printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                    close_active = getCharOption("yYnN");

                    if (close_active == 'y' || close_active == 'Y')
                    {
                        tickets[index].ticket_stat = 0;

                        printf("\n*** Ticket closed! ***\n");
                    }
                }
            }
            else if (selection == 4)
            {
                if (tickets[index].ticket_stat == 1)
                {
                    printf("\nERROR: Ticket is already active!\n");

                }
                else
                {
                    printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
                    close_active = getCharOption("yYnN");

                    if (close_active == 'y' || close_active == 'Y')
                    {
                        tickets[index].ticket_stat = 1;

                        printf("\n*** Ticket re-activated! ***\n");
                    }
                }
            }
        } while (selection != 0);
    }

    return;
}

void addMessage(struct Ticket* tickets, struct Account* accounts, struct Account* acc_details, 
    int size, int index, int selection)
{
    int i;
    int message_i = 0;

    for (i = 0; i < size; i++)
    {
        if (i == size - 1 && strcmp(tickets[index].messages[i].message, "") != 0)
        {
            message_i = -1;
        }
        else if (message_i != -1 && strcmp(tickets[index].messages[i].message, "") == 0)
        {
            message_i = i;
            break;
        }
    }
    if (tickets[index].ticket_stat != 0)
    {
        if (message_i != -1)
        {
            printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
            scanf(" %150[^\n]", tickets[index].messages[message_i].message);
            clearStandardInputBuffer();

            if (selection == 1)
                messageSetup(tickets, accounts, acc_details, 'C', message_i, size, index);
            else
                messageSetup(tickets, accounts, acc_details, 'A', message_i, size, index);
        }
        else
            printf("\nERROR: Message limit has been reached, call ITS Support!\n");
    }
    else
        printf("\nERROR: Ticket is closed - new messages are not permitted.\n");

    return;
}

void messageSetup(struct Ticket* tickets, struct Account* accounts, struct Account* acc_details, 
    char acc_type, int message_i, int size, int index)
{
    int acc_index;

    tickets[index].messages[message_i].acc_type = acc_type;

    acc_index = findAccountIndexByAcctNum(tickets[index].acc_num, accounts, size, 0);

    if (acc_type == 'C')
    {
        strcpy(tickets[index].messages[message_i].name, accounts[acc_index].person_details.full_name);
        tickets[index].messages[message_i].acc_type = 'C';
    }
    else
    {
        strcpy(tickets[index].messages[message_i].name, acc_details->person_details.full_name);
        tickets[index].messages[message_i].acc_type = 'A';
    }

    tickets[index].counter++;

    return;
}

int loadTickets(struct Ticket* tickets, int TICKET_SIZE)
{
    int i = 0;
    int j = 0;

    FILE* fp;

    fp = fopen("tickets.txt", "r");

    if (fp != NULL)
    {
        while (i < TICKET_SIZE && fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tickets[i].ticket_num, &tickets[i].acc_num, &tickets[i].ticket_stat,
            tickets[i].subject, &tickets[i].counter) != EOF)
        {
            while (j < tickets[i].counter)
            {
                fscanf(fp, "%c|%30[^|]|%150[^|]|", &tickets[i].messages[j].acc_type, tickets[i].messages[j].name, tickets[i].messages[j].message);
                j++;
            }
            j = 0;
            i++;
        }
        fclose(fp);
    }
    else
    {
        exit(2);
    }

    return i;
}

int saveTickets(struct Ticket* tickets, int TICKET_SIZE)
{
    int i = 0;
    int j = 0;
    int x = 0;

    FILE* fp;

    fp = fopen("tickets.txt", "w");

    if (fp != NULL)
    {
        while (i < TICKET_SIZE)
        {
            if (tickets[i].ticket_num != 0)
            {

                fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticket_num, tickets[i].acc_num, tickets[i].ticket_stat,
                    tickets[i].subject, tickets[i].counter);

                while (j < tickets[i].counter)
                {
                    fprintf(fp, "%c|%s|%s|", tickets[i].messages[j].acc_type, tickets[i].messages[j].name, tickets[i].messages[j].message);
                    j++;
                }
                fprintf(fp, "\n");
                j = 0;
                x++;
            }
            i++;
        }
        fclose(fp);
    }
    else
    {
        exit(2);
    }

    return x;
}