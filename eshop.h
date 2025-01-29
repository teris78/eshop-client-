#ifndef SHOP_H // Include guard to prevent multiple inclusions of this file
#define SHOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // Library for internet sockets
#include <time.h> // Library for time functions

// Port number for the server to listen to
#define PORT 8080
#define ITEM_COUNT 20 // Total number of products in the e-shop catalog
#define ORDER_COUNT 10 // Total number of orders a client can place

// Define struct item instead of struct product
struct item {
    char name [50]; // Name or description of the product
    float cost; // Cost of the product
    int stock; // Quantity available in stock for the product
};

// Function declarations
void initialize_catalog(struct item catalog[]); // Initialize the product catalog
void handle_client(int client_socket, struct item catalog[]); // Handles client orders
void place_order(int client_socket, int product_id); // Sends an order request to the server

#endif
