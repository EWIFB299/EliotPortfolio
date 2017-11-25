CC = gcc
CFLAGS = -Wall -pedantic

all: hangman_client hangman_server

hangman_client:
	$(CC) -o hangman_client hangman_client.c $(CFLAGS)
				
hangman_server:
	$(CC) -o hangman_server hangman_server.c -lpthread $(CFLAGS)
				
