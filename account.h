// #############################################################################################
//  Assignment: 2 
//  Milestone : 4
// #############################################################################################
//  Student Name  : Joaquin Paredes
//  Student ID    : 113061212
//  Student Email : japaredes-peake@myseneca.ca
//  Course Section: NHH
// #############################################################################################

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#define COMMON_LENGTH 31

struct Person {
    char full_name[COMMON_LENGTH];
    int birth_year;
    double income;
    char country[COMMON_LENGTH];
};

struct UserLogin {
    char login_name[11];
    char password[9];
};

struct Account {
    int acc_number;
    char acc_type;
    struct Person person_details;
    struct UserLogin login_details;
};

//This function will receive a pointer to Account struct to store values in said struct
void getAccount(struct Account*);

//This function will receive a pointer to Person struct to store values in said struct
void getPerson(struct Person*);

//This function will receive a pointer to UserLogin struct to store values in said struct
void getUserLogin(struct UserLogin*);

//This function will receive a pointer to a Account struct, and will be the main menu for adding accounts
void updateAccount(struct Account*);

//This function will receive a pointer to a Person struct, and will be where the user is taken to edit the person info
void updatePerson(struct Person*);

//This function will receive a pointer to a Login struct, and will be where the user is taken to edit the login info
void updateUserLogin(struct UserLogin*);

//This function is used to retrieve information from accounts.txt file and load it in the Account struct array
int loadAccounts(struct Account*, int);

//This function is used to save information from accounts.txt file and load it in the Account struct array
int saveAccounts(struct Account*, int);

#endif // !ACCOUNT_H_#pragma once
