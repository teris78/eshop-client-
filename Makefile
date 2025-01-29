# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SERVER_SRC = server.c eshop.c
CLIENT_SRC = client.c eshop.c

# Executables
SERVER_EXE = server
CLIENT_EXE = client

# Default target
all: $(SERVER_EXE) $(CLIENT_EXE)

# Compile the server
$(SERVER_EXE): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXE) $(SERVER_SRC)

# Compile the client
$(CLIENT_EXE): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXE) $(CLIENT_SRC)


# Clean compiled files
clean:
	rm -f $(SERVER_EXE) $(CLIENT_EXE)
