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
#include <time.h>
#include <string.h>
#include "commonHelpers.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

// As demonstrated in the course notes:
//https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {

        ; // On purpose: do nothing
    }
}

// Function will get a valid integer from keyboard, if no integer is
// provided, a error will be displayed.
int getInteger()
{
    char newLine = 'x';
    int number;

    while (newLine != '\n')
    {
        scanf("%d%c", &number, &newLine);

        if (newLine != '\n')
        {
            clearStandardInputBuffer();

            printf("ERROR: Value must be an integer: ");
        }
    }

    return number;
}

int getPositiveInteger()
{
    char newLine = 'x';
    int number = 0;

    while (number < 1 || newLine != '\n')
    {
        scanf("%d%c", &number, &newLine);

        if (newLine != '\n')
        {
            clearStandardInputBuffer();

            printf("ERROR: Value must be a positive integer greater than zero: ");
        }

        else if (number < 1)
            printf("ERROR: Value must be a positive integer greater than zero: ");
    }

    return number;
}

int getIntFromRange(int low_bound, int high_bound)
{
    int number = 0;

    do
    {
        number = getInteger();

        if (number < low_bound || number > high_bound)
            printf("ERROR: Value must be between %d and %d inclusive: ", low_bound, high_bound);

    } while (number < low_bound || number > high_bound);

    //printf("\n");

    return number;
}

double getDouble()
{
    char newLine = 'x';
    double double_num = 0;

    while (newLine != '\n')
    {
        scanf("%lf%c", &double_num, &newLine);

        if (newLine != '\n')
        {
            clearStandardInputBuffer();

            printf("ERROR: Value must be a double floating-point number: ");
        }
    }

    return double_num;
}

double getPositiveDouble()
{
    char newLine = 'x';
    double double_num = 0;

    double_num = getDouble();
    newLine = '\n';

    while (double_num < 1 || newLine != '\n')
    {
        if (newLine != '\n')
        {
            clearStandardInputBuffer();

            printf("ERROR: Value must be a positive double floating-point number: ");
        }
        else if (double_num < 1)
            printf("ERROR: Value must be a positive double floating-point number: ");

        scanf("%lf%c", &double_num, &newLine);
    }

    return double_num;
}

char getCharOption(const char char_options[])
{
    char charValue = '\0';
    char newLine = 'x';
    int i, runned = 0, flag = 0;

    while (newLine != '\n' || !flag)
    {
        runned = 0;

        scanf("%c%c", &charValue, &newLine);

        if (newLine != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", char_options);
            clearStandardInputBuffer();
            runned = 1;
        }
        else
            for (i = 0; char_options[i] != 0; i++)
                if (charValue == char_options[i])
                {
                    flag = 1;
                    break;
                }
        if (!flag && runned == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", char_options);
        }
    }

    return charValue;
}

void getCString(char* string, int min_chars, int max_chars)
{
    char temp[51] = { 0 };
    int length = 0;

    scanf("%[^\n]", temp);

    length = strlen(temp);

    while (length < min_chars || length > max_chars)
    {
        if (min_chars == max_chars && (length < min_chars || length > max_chars))
        {
            printf("ERROR: String length must be exactly %d chars: ", max_chars);
            clearStandardInputBuffer();
        }
        else if (min_chars == 3 && (max_chars == 10 || max_chars == 6) &&
            (length < min_chars || length > max_chars))
        {
            printf("ERROR: String length must be no more than %d chars: ", max_chars);
            clearStandardInputBuffer();
        }
        else if (min_chars == 4 && (max_chars == 30 || max_chars == 6) &&
            (length < min_chars || length > max_chars))
        {
            printf("ERROR: String length must be between %d and %d chars: ", min_chars, max_chars);
            clearStandardInputBuffer();
        }

        scanf("%[^\n]", temp);
        length = strlen(temp);
    }
    strcpy(string, temp);

    clearStandardInputBuffer();

    return;
}
// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("\n<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}