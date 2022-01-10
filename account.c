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
#include <stdlib.h>
#include "account.h"
#include "commonHelpers.h"

//This function will receive a pointer to Account struct to store values in said struct
void getAccount(struct Account* account)
{
    printf("\nNew Account Data (Account#:%d)\n", account->acc_number);
    printf("----------------------------------------\n");

    printf("Enter the account type (A=Agent | C=Customer): ");
    account->acc_type = getCharOption("AC");

    printf("\n");

    getPerson(&account->person_details);

    if (account->acc_type == 'A')
        getUserLogin(&account->login_details);

    return;
}

//This function will receive a pointer to Person struct to store values in said struct
void getPerson(struct Person* person)
{
    int year = 0;
    size_t i;

    printf("Person Data Input\n");
    printf("----------------------------------------\n");

    year = currentYear();

    printf("Enter the person's full name (30 chars max): ");
    getCString(person->full_name, 3, COMMON_LENGTH - 1);
    printf("Enter birth year (current age must be between 18 and 110): ");
    person->birth_year = getIntFromRange(year - 110, year - 18);
    printf("Enter the household Income: $");
    person->income = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");
    getCString(person->country, 3, COMMON_LENGTH - 1);

    for (i = 0; i < strlen(person->country); i++)
        if (person->country[i] >= 'a' && person->country[i] <= 'z')
            person->country[i] = person->country[i] - 32;

    return;
}

//This function will receive a pointer to UserLogin struct to store values in said struct
void getUserLogin(struct UserLogin* login)
{
    int good_login = 0, flag = 1;
    int char_low_count = 0, char_up_count = 0, digit = 0, symbol = 0;
    size_t i, j;

    printf("\nUser Login Data Input\n");
    printf("----------------------------------------\n");

    do
    {
        flag = 1;

        printf("Enter user login (10 chars max): ");
        getCString(login->login_name, 3, 10);

        for (i = 0; i < strlen(login->login_name); i++)
        {
            if (login->login_name[i] == 32 || login->login_name[i] == 9)
            {
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            good_login = 1;

    } while (good_login != 1);

    good_login = 0;

    do
    {
        char_low_count = 0;
        char_up_count = 0;
        digit = 0;
        symbol = 0;
        char symbols[9] = "!@#$%^&*";

        printf("Enter the password (must be 8 chars in length): ");
        getCString(login->password, 8, 8);

        for (i = 0; i < strlen(login->password); i++)
        {
            if (login->password[i] >= 'a' && login->password[i] <= 'z')
                char_low_count++;
            else if (login->password[i] >= 'A' && login->password[i] <= 'Z')
                char_up_count++;
            else if (login->password[i] >= '0' && login->password[i] <= '9')
                digit++;
            else
            {
                for (j = 0; j < strlen(symbols); j++)
                {
                    if (login->password[i] == symbols[j])
                    {
                        symbol++;
                    }
                }
            }
        }

        if (char_low_count != 2 || char_up_count != 2 || digit != 2 || symbol != 2)
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character: %s\n", symbols);
        }
        else
            good_login = 1;

    } while (good_login != 1);
    return;
}

void updateAccount(struct Account* acc_update)
{
    int selection;

    do
    {
        printf("\nUpdate Account: %d (%s)\n", acc_update->acc_number, acc_update->person_details.full_name);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", acc_update->acc_type);
        printf("2) Person\n");
        printf("3) Login\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);

        if (selection == 1)
        {
            printf("\nEnter the account type (A=Agent | C=Customer): ");
            acc_update->acc_type = getCharOption("AC");

            if (acc_update->acc_type == 'A')
            {
                printf("\nAgent type accounts require a user login.  Please enter this information now:\n");
                getUserLogin(&acc_update->login_details);
            }
            else
            {
                *acc_update->login_details.login_name = '\0';
                *acc_update->login_details.password = '\0';
            }
        }
        else if (selection == 2)
        {
            updatePerson(&acc_update->person_details);
        }
        else if (selection == 3 && acc_update->acc_type == 'A')
        {
            updateUserLogin(&acc_update->login_details);
        }
        else if (selection == 3 && acc_update->acc_type != 'A')
            printf("\nERROR:  Customer account types don't have user logins!\n");

    } while (selection != 0);

    printf("\n");

    return;
}

void updatePerson(struct Person* person_update)
{
    int selection;
    size_t i;

    do
    {
        printf("\nPerson Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Full name (current value: %s)\n", person_update->full_name);
        printf("2) Household Income (current value: $%.2lf)\n", person_update->income);
        printf("3) Country (current value: %s)\n", person_update->country);
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);

        if (selection == 1)
        {
            printf("\nEnter the person's full name (30 chars max): ");
            getCString(person_update->full_name, 3, COMMON_LENGTH - 1);
        }
        else if (selection == 2)
        {
            printf("\nEnter the household Income: $");
            person_update->income = getPositiveDouble();
        }
        else if (selection == 3)
        {
            printf("\nEnter the country (30 chars max.): ");
            getCString(person_update->country, 3, COMMON_LENGTH - 1);

            for (i = 0; i < strlen(person_update->country); i++)
                if (person_update->country[i] >= 'a' && person_update->country[i] <= 'z')
                    person_update->country[i] = person_update->country[i] - 32;
        }
    } while (selection != 0);

    return;
}

void updateUserLogin(struct UserLogin* login_update)
{
    int selection;
    int good_login = 0;
    int char_low_count = 0, char_up_count = 0, digit = 0, symbol = 0;
    size_t i;

    do
    {
        printf("\nUser Login: %s - Update Options\n", login_update->login_name);
        printf("----------------------------------------\n");
        printf("1) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 1);

        if (selection == 1)
        {
            printf("\n");
            do
            {
                char_low_count = 0;
                char_up_count = 0;
                digit = 0;
                symbol = 0;
                char symbols[9] = "!@#$%^&*";

                printf("Enter the password (must be 8 chars in length): ");
                getCString(login_update->password, 8, 8);

                for (i = 0; i < strlen(login_update->password); i++)
                {
                    if (login_update->password[i] >= 'a' && login_update->password[i] <= 'z')
                        char_low_count++;
                    else if (login_update->password[i] >= 'A' && login_update->password[i] <= 'Z')
                        char_up_count++;
                    else if (login_update->password[i] >= '0' && login_update->password[i] <= '9')
                        digit++;
                    else
                        symbol++;
                }

                if (char_low_count > 2 || char_up_count > 2 || digit > 2 || symbol > 2)
                {
                    printf("SECURITY: Password must contain 2 of each:\n");
                    printf("          Digit: 0-9\n");
                    printf("          UPPERCASE character\n");
                    printf("          lowercase character\n");
                    printf("          symbol character: %s\n", symbols);
                }
                else
                    good_login = 1;

            } while (good_login != 1);
        }

    } while (selection != 0);

    return;
}

int loadAccounts(struct Account* accounts, int ACCOUNT_SIZE)
{
    int i = 0;
    FILE* fp;

    fp = fopen("accounts.txt", "r");

    if (fp != NULL)
    {
        while (i < ACCOUNT_SIZE && fscanf(fp, "%d~%c", &accounts[i].acc_number, &accounts[i].acc_type) != EOF)
        {
            if (accounts[i].acc_type == 'C')
            {
                fscanf(fp, "~%30[^~]~%d~%lf~%30[^\n]", accounts[i].person_details.full_name, &accounts[i].person_details.birth_year,
                    &accounts[i].person_details.income, accounts[i].person_details.country);
            }
            else
                fscanf(fp, "~%30[^~]~%d~%lf~%30[^~]~%8[^~]~%10[^\n]", accounts[i].person_details.full_name, &accounts[i].person_details.birth_year,
                    &accounts[i].person_details.income, accounts[i].person_details.country, accounts[i].login_details.login_name,
                    accounts[i].login_details.password);

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

int saveAccounts(struct Account* accounts, int ACCOUNT_SIZE)
{
    int i = 0;
    int j = 0;
    FILE* fp;

    fp = fopen("accounts.txt", "w");

    if (fp != NULL)
    {
        while (i < ACCOUNT_SIZE)
        {
            if (accounts[i].acc_number != 0)
            {
                fprintf(fp, "%d~%c", accounts[i].acc_number, accounts[i].acc_type);

                if (accounts[i].acc_type == 'C')
                {
                    fprintf(fp, "~%s~%d~%.2lf~%s\n", accounts[i].person_details.full_name, accounts[i].person_details.birth_year,
                        accounts[i].person_details.income, accounts[i].person_details.country);
                }
                else
                    fprintf(fp, "~%s~%d~%.2lf~%s~%s~%s\n", accounts[i].person_details.full_name, accounts[i].person_details.birth_year,
                        accounts[i].person_details.income, accounts[i].person_details.country, accounts[i].login_details.login_name,
                        accounts[i].login_details.password);
                j++;
            }
            i++;
        }
        fclose(fp);
    }
    else
    {
        exit(2);
    }
    return j;
}


