#include "eshop.h" // Include the header file with declarations and constants

// Sends an order request for a specific product to the server
void place_order(int client_socket, int product_id) {
    // Send the product ID to the server
    if (write(client_socket, &product_id, sizeof(product_id)) < 0) {
        perror("Failed to send order"); // Print an error message if the send fails
        exit(EXIT_FAILURE); // Terminate the program
    }
    printf("Order for product ID %d sent to server.\n", product_id); // Debug message
}

// Function to handle a client connection and process their orders
void handle_client(int client_socket, struct item catalog[]) {
    int product_id; // Variable to store the product ID requested by the client

    // Continuously read product requests from the client
    while (read(client_socket, &product_id, sizeof(product_id)) > 0) {
        // Check if the requested product ID is within valid range
        if (product_id < 0 || product_id >= ITEM_COUNT) {
            printf("Invalid product ID: %d\n", product_id); // Print error message
            continue; // Skip this iteration and wait for a new request
        }

        // Get the product from the catalog using the product ID
        struct item *prod = &catalog[product_id];

        // Check if the product is in stock
        if (prod->stock > 0) {
            prod->stock--; // Reduce stock by 1, since the product is being purchased

            // Create a success message to send to the client
            char success_msg[100];
            snprintf(success_msg, sizeof(success_msg), "Product %s purchased successfully!\n", prod->name);

            // Send success message back to the client
            write(client_socket, success_msg, strlen(success_msg));
        } else {
            // Create a failure message if the product is out of stock
            char fail_msg[100];
            snprintf(fail_msg, sizeof(fail_msg), "Product %s is out of stock.\n", prod->name);

            // Send failure message back to the client
            write(client_socket, fail_msg, strlen(fail_msg));
        }

        sleep(1); // Simulate processing time (1 second delay)
    }
}


// Initialize the item catalog
void initialize_catalog(struct item catalog[]) {
    for (int i = 0; i < ITEM_COUNT; i++) { // Loop through all products
        snprintf(catalog[i].name, sizeof(catalog[i].name), "Product %d", i + 1); // Assign product name
        catalog[i].cost = (float)((i + 1) * 10);  // Assign cost
        catalog[i].stock = 2;  // Sets the initial stock for 2 for each product
    }
}
