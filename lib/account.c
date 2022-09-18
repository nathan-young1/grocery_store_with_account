#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hash_table.h"

#define BaseAccountNumber 29348584393
#define clearInputBuffer() while (getchar() != '\n');
#define exit_app() exit(0);

typedef struct Account
{
    char password[20];
    char phone_number[20];
    char account_number[20];
    char name[20];
    int balance;
} Account;

void display_account_balance(Account *account)
{
    printf("\n=======> Current account balance: %d\n\n", account->balance);
}

bool deposit_operation(int deposit_amount, Account *account)
{
    // Cannot deposit a negaitive number.
    if (deposit_amount < 0)
        return false;
    account->balance = account->balance + deposit_amount;
    return true;
}

bool withdraw_operation(int withdraw_amount, Account *account)
{
    // Cannot withdraw a negaitive number.
    if (withdraw_amount < 0)
        return false;

    if (withdraw_amount > account->balance)
        return false;

    account->balance = account->balance - withdraw_amount;
    return true;
}

void account_withdraw(Account *account)
{
    printf("How much do you want to withdraw : ");
    int desired_withdrawal_amount;
    scanf("%d", &desired_withdrawal_amount);

    bool withdraw_status = withdraw_operation(desired_withdrawal_amount, account);
    if (withdraw_status == false)
    {
        printf("\n=======> You cannot withdraw $%d from account balance of $%d\n\n", desired_withdrawal_amount, account->balance);
        clearInputBuffer();
        return;
    }
    else
    {
        printf("\n=======> Withdrawal was successful!!! ");
        display_account_balance(account);
    }
}

void account_deposit(Account *account)
{
    printf("How much do you want to deposit : ");
    int desired_deposit_amount;
    scanf("%d", &desired_deposit_amount);

    bool deposit_status = deposit_operation(desired_deposit_amount, account);
    if (deposit_status == false)
    {
        printf("\n=======> You cannot deposit $%d to your account\n\n", desired_deposit_amount);
        clearInputBuffer();
        return;
    }
    else
    {
        printf("\n=======> Deposit was successful!!! ");
        display_account_balance(account);
    }
}

bool password_auth(char *password, Account *account)
{
    if (strcmp(password, account->password) == 0)
        return true;
    return false;
}

Account *get_account(char *account_number, hashtable *table)
{
    entry *dict_item = hashtable_lookup(account_number, table);

    // if the account does not exist in the dictionary.
    if (dict_item == NULL)
        return NULL;

    return (Account *)dict_item->value;
}

Account *account_login(hashtable *table)
{
    char account_number_entered[20];
    char password_entered[20];
    printf("\t=======Login to Account=======\t\n");

account_number_input:
    printf("Enter Account number : ");
    scanf("%s", account_number_entered);
    entry *item = hashtable_lookup(account_number_entered, table);

    // when account number is not in the dictionary.
    if (item == NULL)
    {
        printf("\n=====> Account Number --- %s --- DOES NOT EXIST\n\n", account_number_entered);
        clearInputBuffer();
        goto account_number_input;
    }

    Account *acct_from_dict = (Account *)item->value;

password_input:
    printf("Enter Password : ");
    scanf("%s", password_entered);
    if (password_auth(password_entered, acct_from_dict) == false)
    {
        printf("\n=====> Wrong Password !!!!\n\n");
        clearInputBuffer();
        goto password_input;
    }
    return acct_from_dict;
}

void account_register(hashtable *table)
{
    Account *new_account = (Account *)malloc(sizeof(Account));
    printf("\t==========Creation Of Account=======\t\n");

    printf("Enter account Name : ");
    scanf("%s", new_account->name);

    printf("\nEnter phone number : ");
    scanf("%s", new_account->phone_number);

    printf("\nEnter password : ");
    scanf("%s", new_account->password);

    // convert int account number to string and stores it.
    sprintf(new_account->account_number, "%ld", rand() + BaseAccountNumber);

    hashtable_insert(new_account->account_number, new_account, table);

    printf("\n=====>\tAccount %s Has been created successfully.\n\n", new_account->account_number);
    // check later.
    clearInputBuffer();
}

bool delete_account(char *account_number, hashtable *table)
{
    bool delete_is_successful = hashtable_delete(account_number, table);
    return delete_is_successful;
}

void print_account_details(Account *account)
{
    printf("\n\t=============Account Details============\n");
    printf("\n\tName : %s\n", account->name);
    printf("\tAccount number : %s\n", account->account_number);
    printf("\tPhone Number : %s\n", account->phone_number);
    printf("\tBalance : $%d\n\n", account->balance);
}

void account_start_banking(hashtable *accounts_table)
{
    printf("\t=============Welcome to Emirates Bank==========\t\n\n");

onboarding:
    printf("Available Operations: \n");
    printf("1: Create an Account\n");
    printf("2: Login to my Account\n");
    printf("3: Exit\n");

    printf("Input number beside desired operation : ");
    int user_choice;
    scanf("%d", &user_choice);
    printf("\n");

    switch (user_choice)
    {
    case 1:
        account_register(accounts_table);
        goto onboarding;
    case 2:
        Account *acct_from_dict = account_login(accounts_table);

        printf("\n=====> Welcome %s\n\n", acct_from_dict->name);
    logged_in_operations:
        printf("What operation do you want to perform :");
        printf("\n1: Withdrawal");
        printf("\n2: Deposit");
        printf("\n3: Check My Balance");
        printf("\n4: Print Details");
        printf("\n5: Delete My Account");
        printf("\n6: Logout");

        printf("\n\nInput number beside desired operation : ");
        scanf("%d", &user_choice);

        switch (user_choice)
        {
        case 1:
            account_withdraw(acct_from_dict);
            goto logged_in_operations;
        case 2:
            account_deposit(acct_from_dict);
            goto logged_in_operations;
        case 3:
            display_account_balance(acct_from_dict);
            goto logged_in_operations;
        case 4:
            print_account_details(acct_from_dict);
            goto logged_in_operations;
        case 5:
            delete_account(acct_from_dict->account_number, accounts_table);
            printf("\n======> Deletion of Account %s is successful\n", acct_from_dict->account_number);
            printf("\tThanks for banking with us.\n\n");
            goto onboarding;
        case 6:
            printf("\n=====> Account %s Has been logged out successfully\n\n", acct_from_dict->account_number);
            goto onboarding;

        default:
            printf("\n=====> Please Input a valid operation.\n\n");
            goto logged_in_operations;
            break;
        }
        break;
    case 3:
        printf("\tThanks for banking with us\n\n");
        break;

    default:
        printf("\n=====> Please Input a valid operation.\n\n");
        goto onboarding;
        break;
    }
}

