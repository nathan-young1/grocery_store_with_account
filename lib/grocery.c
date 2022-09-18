#include <stdio.h>
#include <stdlib.h>
#include "../include/hash_table.h"
#include "../include/account.h"
#define clearInputBuffer() while (getchar() != '\n');

typedef struct food
{
	int price;
	char *food_name;

} food;

typedef struct cart
{
	food item;
	int number_of_item;
	struct cart *next_food_in_cart;
} cart;

void print_avaliable_foods(food *avaliable_foods, int avaliable_food_length)
{
	for (int i = 1; i <= avaliable_food_length; i++)
	{
		printf("%d. %s\t$%d\n", i, avaliable_foods[i - 1].food_name, avaliable_foods[i - 1].price);
	}
}

void add_to_cart(food desired_food, cart **food_cart)
{
	printf("\nEnter the number of %s('s) you want : ", desired_food.food_name);
	int number_of_desired_groceries;
	scanf("%d", &number_of_desired_groceries);
	if (number_of_desired_groceries > 0)
	{
		printf("\n========> %d %s('s) added to cart\n", number_of_desired_groceries, desired_food.food_name);
		// Add item to cart.
		cart *new_item = malloc(sizeof(cart));
		new_item->item = desired_food;
		new_item->number_of_item = number_of_desired_groceries;

		// make the new item point to the existing item in the cart.
		new_item->next_food_in_cart = *food_cart;

		// make the new item the head of the linked list.
		*food_cart = new_item;
	}
}

void purchase_food(cart **food_cart)
{
	food avaliable_foods[10] = {
		{.food_name = "Egusi", .price = 450},
		{.food_name = "Beans", .price = 600},
		{.food_name = "Garri", .price = 950},
		{.food_name = "Carrot", .price = 1200},
		{.food_name = "Plantain", .price = 300},
		{.food_name = "Tomato", .price = 380},
		{.food_name = "Pepper", .price = 120},
		{.food_name = "Indomie", .price = 260},
		{.food_name = "Potato", .price = 670},
		{.food_name = "Banana", .price = 890},
	};

food_menu:
	clearInputBuffer();

	int avaliable_food_length = sizeof(avaliable_foods) / sizeof(food);
	printf("\nWhat food do you want to buy:\n\n");
	print_avaliable_foods(avaliable_foods, avaliable_food_length);

	printf("\n0. Go back to main menu\n\n");

choice_of_food:
	printf("=====> Enter choice : ");

	int food_choice;
	scanf("%d", &food_choice);

	if (food_choice == 0)
		return;

	if (food_choice > avaliable_food_length || food_choice < 1)
	{
		printf("\n=====> Invalid choice\n\n");
		clearInputBuffer();
		goto choice_of_food;
	}

	food desired_food = avaliable_foods[food_choice - 1];

	buy_food:
	printf("\nFood Name: %s\n", desired_food.food_name);
	printf("Price: %d\n", desired_food.price);

	printf("\n1. Add to cart");
	printf("\n2. Back to food menu\n");

	printf("\n=====> Enter choice : ");

	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		add_to_cart(desired_food, food_cart);
		goto food_menu;

	case 2:
		goto food_menu;

	default:
		printf("\n=====> Invalid choice\n");
		clearInputBuffer();
		goto buy_food;
	}
}

// Will print the cart content and return the total_price.
int print_cart_content(cart *food_cart)
{
	int total_price = 0;
	if (food_cart == NULL)
	{
		printf("\n==================================\n");
		printf("\tThe cart is empty");
		printf("\n==================================\n");
	}
	else
	{
		printf("\n==================================\n");
		printf("\tCart Content:");
		printf("\n==================================");

		// Loop through the cart.
		for (cart *cart_item = food_cart; cart_item != NULL; cart_item = cart_item->next_food_in_cart)
		{
			int price = cart_item->item.price * cart_item->number_of_item;
			printf("\n\nItem name: %s", cart_item->item.food_name);
			printf("\nItem price: %d", cart_item->item.price);
			printf("\nNumber of item: %d", cart_item->number_of_item);
			printf("\nPrice: $%d", price);

			// Add to total price.
			total_price += price;
		}

		printf("\n\n=======> Total Price: $%d\n", total_price);
	}
	return total_price;
}

void checkout(cart **food_cart, hashtable *accounts_table)
{
	int total_price = print_cart_content(*food_cart);
	if (total_price == 0)
		return;

	char accountNumber[20];
	char accountPassword[20];
payment:
	printf("\nEnter payment account number : ");
	scanf("%s", accountNumber);
	printf("Enter account password : ");
	scanf("%s", accountPassword);

	bool crediential_is_valid = false;

	entry *item = hashtable_lookup(accountNumber, accounts_table);
	if (item != NULL)
	{
		bool auth_result = password_auth(accountPassword, (Account *)item->value);
		crediential_is_valid = auth_result;
	}

	if (!crediential_is_valid)
	{
		printf("\n\tInvalid credientials !!!!");
		printf("\n\tEnter the right account details !!!\n");
		clearInputBuffer();
		goto payment;
	}

	Account *account = (Account *)item->value;
	if (account->balance < total_price)
	{
		printf("\n\tYour account balance is $%d while your total price is $%d", account->balance, total_price);
		printf("\n\tSo you cannot afford to buy the items in your cart.\n");
	}
	else
	{
		account->balance -= total_price;
		printf("\nYou have successfully paid!!!!!");
		printf("\nRemaining account balance: $%d", account->balance);
		printf("\nThanks for shopping with us.");
		// clear the food cart.
		*food_cart = NULL;
	}

	printf("\n========== BYE BYE ==========\n");
}

void groceries_start(hashtable *accounts_table, cart **food_cart)
{

grocery_store:
	printf("\n==============================\n");
	printf("\tGrocery Store");
	printf("\n==============================\n");

	printf("1. Purchase food\n");
	printf("2. Display cart content\n");
	printf("3. Checkout\n");
	printf("4. Exit grocery store\n");

grocery_choice:
	printf("\n=====> Enter desired operation : ");

	int choice;
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		purchase_food(food_cart);
		break;

	case 2:
		print_cart_content(*food_cart);
		break;

	case 3:
		checkout(food_cart, accounts_table);
		break;

	case 4:
		return;

	default:
		printf("\n=====> Invalid choice\n");
		clearInputBuffer();
		goto grocery_choice;
	}
	goto grocery_store;
}
