#include "eshop.h" // Include the header file for declarations

int main() {
    int client_socket; // Socket for the client
    struct sockaddr_in server_addr; // Structure for the server address

    // Create the client socket (TCP connection)
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) { // Check if socket creation failed
        perror("Socket creation failed"); // Print an error message
        exit(EXIT_FAILURE); // Exit the program
    }

    // Set server address parameters
    server_addr.sin_family = AF_INET; // Address family (IPv4)
    server_addr.sin_port = htons(PORT); // Set the port number (network byte order)
    server_addr.sin_addr.s_addr = INADDR_ANY; // Connect to the local machine

    // Attempt to connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed"); // Print an error message if connection fails
        exit(EXIT_FAILURE); // Exit the program
    }

    printf("Connected to server.\n"); // Print a success message for the connection

    // Loop to send multiple orders to the server
    for (int i = 0; i < ORDER_COUNT; i++) { // Repeat for a predefined number of orders
        int product_id = rand() % ITEM_COUNT; // Use ITEM_COUNT instead of PRODUCT_COUNT
        place_order(client_socket, product_id); // Call the function to place the order
        sleep(1); // Wait for 1 second before sending the next order
    }

    close(client_socket); // Close the client socket after all orders are sent
    return 0; // Exit the program
}
