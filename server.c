#include "eshop.h" // Include the header file for declarations

int main() {
    struct item catalog[ITEM_COUNT]; // Create an array for the item catalog
    initialize_catalog(catalog); // Initialize the catalog with default items

    int server_socket, client_socket; // Sockets for the server and client
    struct sockaddr_in server_addr, client; // Structures for server and client addresses
    socklen_t addr_size; // Size of the client address structure

    server_socket = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (server_socket < 0) { // Check if socket creation failed
        perror("Socket creation failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate the program
    }

    server_addr.sin_family = AF_INET; // Set address family to IPv4
    server_addr.sin_port = htons(PORT); // Convert port number to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { // Bind socket to address
        perror("Bind failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate the program
    }
    printf("Server is running and waiting for clients...\n"); // Inform that the server is running

    if (listen(server_socket, 5) < 0) { // Start listening for incoming connections
        perror("Listen failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate the program
    }

    while (1) { // Infinite loop to handle multiple clients
        addr_size = sizeof(client); // Set the size of the client address structure
        client_socket = accept(server_socket, (struct sockaddr*)&client, &addr_size); // Accept a client connection

        if (client_socket < 0) { // Check if accepting the client failed
            perror("Accept failed"); // Print error message
            continue; // Continue to the next iteration
        }

        printf("Client connected.\n"); // Inform that a client has connected

        if (fork() == 0) { // Create a child process to handle the client
            handle_client(client_socket, catalog); // Process client requests
            close(client_socket); // Close the client socket
            exit(0); // Terminate the child process
        }

        close(client_socket); // Close the client socket in the parent process
    }

    close(server_socket); // Close the server socket
    return 0; // Exit the program
}
