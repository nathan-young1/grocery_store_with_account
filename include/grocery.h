#ifndef GROCERY_HEADER
#define GROCERY_HEADER
#include "hash_table.h"

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

int print_cart_content(cart *food_cart);
void print_avaliable_foods(food *avaliable_foods, int avaliable_food_length);
void add_to_cart(food desired_food, cart **food_cart);
void checkout(cart **food_cart, hashtable *accounts_table);
void purchase_food(cart **food_cart);
void groceries_start(hashtable *accounts_table, cart **food_cart);

#endif