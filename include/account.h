#ifndef ACCOUNT_HEADER
#define ACCOUNT_HEADER
#include <stdbool.h>
#include "hash_table.h"

typedef struct Account
{
    char password[20];
    char phone_number[20];
    char account_number[20];
    char name[20];
    int balance;
} Account;

void account_start_banking(hashtable *accounts_table);
void display_account_balance(Account *account);
void account_deposit(Account *account);
void account_withdraw(Account *account);
bool password_auth(char *password, Account *account);
Account *get_account(char *account_number, hashtable *table);
void account_register(hashtable *table);
Account *account_login(hashtable *table);
bool delete_account(char *account_number, hashtable *table);
void print_account_details(Account *account);

#endif