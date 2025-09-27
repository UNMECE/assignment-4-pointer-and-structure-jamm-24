#include <stdio.h>
#include "item.h"
#include <string.h>
#include <stdlib.h>

//function implementation
void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index){
	item_list[index].price = price;

	//allocate memory for sku
	item_list[index].sku = (char *)malloc(strlen(sku) + 1);
	if(item_list[index].sku == NULL){
		perror("Failed to allocate memory for sku");
		return;

	}
	strcpy(item_list[index].sku, sku);

	//allocate memory for name
	item_list[index].name = (char *)malloc(strlen(name) + 1);
	if(item_list[index].name == NULL){
		perror("Failed to allocate memory for name");
		free(item_list[index].sku);
		return;
	}
	strcpy(item_list[index].name, name);

	//allocate memory for category
	item_list[index].category = (char *)malloc(strlen(category) + 1);
	if(item_list[index].category == NULL){
		perror("Failed to allocate memory for category");
		free(item_list[index].sku);
		free(item_list[index].name);
		return;
	}
	strcpy(item_list[index].category, category);
}
void free_items(Item *item_list, int size){
	for(int i=0; i<size; i++){
		free(item_list[i].sku);
		free(item_list[i].name);
		free(item_list[i].category);
	}
	free(item_list); //free array
	}
double average_price(Item *item_list, int size){
	if(size == 0){
		return 0;
	}
	double total_price = 0;
	for(int i=0; i<size; i++){
		total_price += item_list[i].price;
	}
	return total_price/size;
}
void print_items(Item *item_list, int size){
	printf("  Grocery Store Items  \n");
	for(int i=0; i<size; i++){
		printf("Item %d:\n", i + 1);
		printf(" Name: %s\n", item_list[i].name);
		printf(" SKU: %s\n", item_list[i].sku);
		printf(" Category: %s\n", item_list[i].category);
		printf(" Price: %.2f\n", item_list[i].price);
	}
	printf("\n");
}
int main(int argc, char *argv[]){
	int num_items = 5;
	//allocate space for an array of 5 items
	Item *grocery_items = (Item *)malloc(num_items * sizeof(Item));
	if(grocery_items == NULL){
		printf("Failed to aloocate memory for grocery_items array");
		return EXIT_FAILURE;
	}
	//5 different items
	add_item(grocery_items, 3.00, "SKU001", "Produce", "Orange", 0);
        add_item(grocery_items, 4.00, "SKU002", "Dairy", "Milk", 1);
	add_item(grocery_items, 3.00, "SKU003", "Bakery", "Bread", 2);
        add_item(grocery_items, 25.00, "SKU004", "Meat", "Steak", 3);
	add_item(grocery_items, 4.50, "SKU005", "Snacks", "Oreo Cookies", 4);
	
	//print items
	print_items(grocery_items, num_items);

	//calculate and print the average
	double avg_price = average_price(grocery_items, num_items);
	printf("Average price of items: %.2f\n", avg_price);

	//command line argument for sku search
	if(argc > 1){
		char *search_sku = argv[1];
		int found_index = -1;
		int ct = 0;

		//using the short-circuiting while loop
		while (ct < num_items && strcmp(grocery_items[ct].sku, search_sku) !=0){
			ct++;
		}
		if(ct < num_items){
			found_index = ct;
			printf("\nItem with SKU '%s' found:\n", search_sku);
			printf(" SKU: %s\n", grocery_items[found_index].sku);
			printf(" Name: %s\n", grocery_items[found_index].name);
			printf(" Category: %s\n", grocery_items[found_index].category);
			printf(" Price: %.2f\n", grocery_items[found_index].price);
		} else {
			printf("\nItem with SKU '%s' not found.\n", search_sku);
		}
	} else {
		printf("\nNo SKU provided for search. Usage: ./main <sku>\n");
	}
	//free allocated memory
	free_items(grocery_items, num_items);

	return 0;
}




