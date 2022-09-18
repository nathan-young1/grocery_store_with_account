#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/hash_table.h"
#include "../include/account.h"
#include "../include/grocery.h"

void start_app(hashtable *, cart **food_cart);

int main()
{
	srand(time(NULL));
	hashtable *accounts_table = intialize_hashtable(30);

	// create a sample_acct.
	Account sample_acct = {
		// .account_number = "29348584393",
		.account_number = "0",
		.name = "John doe",
		.balance = 40000,
		.password = "password",
		.phone_number = "07067939323"};

	// add sample_acct to hashtable.
	hashtable_insert(sample_acct.account_number, &sample_acct, accounts_table);

	// create an empty cart
	cart *food_cart = NULL;

	start_app(accounts_table, &food_cart);
	return (0);
}

void start_app(hashtable *accounts_table, cart **food_cart)
{
	printf("\n");
start:
	printf("\nWelcome\n\tWhat do you want to do today :\n\n");
	printf("1. Account mangement\n");
	printf("2. Groceries shopping\n");
	printf("3. Exit app\n");

start_choice:
	printf("\n=====> Enter desired operation : ");

	int choice;
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
	case 1:
		account_start_banking(accounts_table);
		goto start;

	case 2:
		groceries_start(accounts_table, food_cart);
		goto start;

	case 3:
		exit(EXIT_SUCCESS);
		break;

	default:
		printf("=====> Invalid choice\n");
		goto start_choice;
	}
}