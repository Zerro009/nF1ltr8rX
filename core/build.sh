#!/usr/bin/env	bash

# Memory
gcc -c src/memory.c -o memory.o

# Data structures
gcc -c src/hash_table.c -o hash_table.o

# Network
gcc -c src/socket.c -o socket.o

# HTTP
gcc -c src/http_request.c -o http_request.o
gcc -c src/http_response.c -o http_response.o

# DB
gcc -c src/db.c -o db.o

# MVC
gcc -c src/middleware.c -o middleware.o
gcc -c src/view.c -o view.o

# Server
gcc -c src/tcp_server.c -o tcp_server.o
gcc -c src/http_server.c -o http_server.o

# Scanning
gcc -c src/scanner.c -o scanner.o

gcc -c src/main.c -o main.o

gcc -g -Wall -lm memory.o hash_table.o socket.o http_request.o http_response.o tcp_server.o http_server.o db.o middleware.o view.o scanner.o main.o $(pkg-config --cflags --libs libpq) -lncurses -o run

# Clear
rm *.o
