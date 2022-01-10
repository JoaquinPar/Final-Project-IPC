// #############################################################################################
//  Assignment: 2
//  Milestone : 4
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_

int currentYear(void);

//Functino to clear the buffer of any hanging values
void clearStandardInputBuffer(void);

//Function to receive a int value
int getInteger();

//Function to receive a positive int value
int getPositiveInteger();

//Function to receive a value within specified range
int getIntFromRange(int, int);

//Function to receive a double value
double getDouble();

//Function to receive a positive double value
double getPositiveDouble();

//Fuction to receive a character from the user depending on char array sent, and returns the character selected
char getCharOption(const char[]);

//Functino to recieve a string from the user and store in char pointer specified
void getCString(char*, int, int);

//Pause execution until user enters the enter key
void pauseExecution(void);

#endif // !COMMONHELPERS_H_