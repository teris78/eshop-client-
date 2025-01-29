# eshop-client



PURPOSE OF THE PROJECT:
This project implements an electronic store (e-shop) that allows multiple clients 
to place product orders over the internet. Communication between the server and clients 
is done using internet sockets.

Functionality:
- The server manages a product catalog and processes orders.
- Each client sends product purchase requests to the server.
- If the product is available, the order is successfully completed.
- If the product is out of stock, the client receives a relevant message.
- The server runs continuously and serves multiple clients simultaneously.



REPOSITORY CONTENTS:

Project Files:
- Makefile   → Defines the compilation rules for the program.
- server.c   → Server-side implementation.
- client.c   → Client-side implementation.
- eshop.h    → Header file containing function declarations and data structures.
- eshop.c    → Implements the core functions of the e-shop.


Instructions : 
- insert commands in the following order :
- make
- ./server
- open a new terminal window
- ./client
To remove compiled files :
- make clean
