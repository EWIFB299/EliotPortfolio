/*
Eliot Wilson -n9175504
CAB403 Assessment 1
hangman_client.c
*/
#include <errno.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

	#define DEFAULT_PORT 12345
	#define DATAMAX 255
	#define PLAYGAME 1
	#define SHOWBOARD 2
	#define END 3
	#define MAXIMUM_GUESSES 26

void* displayBoard(int sockfd);
void* playHangman(int sockfd, char userprint[]);

int main(int argc, char *argv[]) {
	int sockfd, numbytes, i=0;  
	char buf[DATAMAX];
	char username[DATAMAX];
	char logBuffer[DATAMAX];
	char invalidInput;
	int password;
	int port = DEFAULT_PORT;
	int *logInt;
	int login = 0;
	int menuOption =0;
	struct hostent *he;
	struct sockaddr_in their_addr;

	if ((he=gethostbyname(argv[1])) == NULL) {
		herror("gethostbyname");
		exit(1);
	}
	
	if (argc == 3) {
		port = atoi(argv[2]);
	}


	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}


	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(port);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
	sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	printf("============================================\n");
	printf("Welcome to the Online Hangman Gaming System \n");
	printf("============================================\n");
			
	printf("\nYou are required to logon with your registered Username and Password");
	printf("\nPlease enter your username -- >");
	scanf("%s", username);
	printf("\nPlease enter your password-- >");	
	scanf("%d", &password);
	int netPassword = htonl(password);
	
	send(sockfd, username, sizeof(username), 0);
	send(sockfd, &netPassword, sizeof(int), 0);
	
	while(1){
		//Recieves login status	
		if(recv(sockfd, logBuffer, sizeof(int), 0)==-1){
				perror("recv");
				exit(1);
			}
			
		logInt = (int *) logBuffer;
		login = ntohl(*logInt);
		
		//Checks if login was succesfull
		if(login == 0){
		printf("\nInvalid Login details. The game will now close\n");
		close(sockfd);
		return 0;
		}
		
		if(login ==1){
		printf("\nLogin Successful\n");
		break;
		}
	}
	
	while(1){
	printf("\nPlease Enter a Selection \n");			
	printf("<1> Play Hangman\n");
	printf("<2> Show Leaderboard\n");
	printf("<3> Quit\n");
	
				printf("\nSelect Option 1-3-- >");	
				scanf("%d", &menuOption);
				while((invalidInput = getchar()) != '\n');
				
			if (menuOption!= END && menuOption != SHOWBOARD && menuOption != PLAYGAME){
				printf("\nInvalid Selection\n");
				menuOption = 0;
			}
			
			//Play Hangman			
			if(menuOption== PLAYGAME){
				playHangman(sockfd, username);
				menuOption = 0;
				}
				
			//Show Scoreboard
			if(menuOption== SHOWBOARD){
				displayBoard(sockfd);
				menuOption = 0;
				}
			
			//Exit Game
			if(menuOption== END){
				printf("\nThank you for playing!\n");
				close(sockfd);
				return 0;
				}
			
			fflush(stdin);
	}
			
	close(sockfd);

	return 0;
}

/*
displayBoard:

Recieves the board information from the server and prints each node.
*/
void* displayBoard(int sockfd){
	int gamechoice = htonl(SHOWBOARD);
	int boardlength;
	int *intConvert;
	int matches_won;
	int matches_played;
	char nameBuffer[DATAMAX];
	char sizeBuffer[DATAMAX];
	char wonBuffer[DATAMAX];
	char playedBuffer[DATAMAX];
	//Sends the client choice to the sever
	if (send(sockfd, &gamechoice, sizeof(int) ,0) == -1){
			perror("send");
	}

	//Recieves the length of the scoreboard
	if(recv(sockfd, sizeBuffer, DATAMAX, 0)==-1){
			perror("recv");
	}
	
	intConvert = (int *) sizeBuffer;
	boardlength = ntohl(*intConvert);
	//Checks if board length is empty
	if(boardlength == 0){
		printf("=============================================================================\n");
		printf("\nThere is no information currently stored in the leaderboard. Try again later \n");
		printf("\n=============================================================================\n");
	}
	
	if(boardlength > 0){
	//Iterates for the board length and prints the scoreboard
	for(int i = 0; i < boardlength; i++){
		
		//Recieves entry name
		if(recv(sockfd, nameBuffer, DATAMAX, 0)==-1){
				perror("recv");
		}
		int acknowledge = htonl(1);
		
		//Sends an acknowledgement that the name was recieved
		if (send(sockfd, &acknowledge, sizeof(int) ,0) == -1){
					perror("send");
		}
		
		//Recieves number of games played
		if(recv(sockfd, playedBuffer, sizeof(int), 0)==-1){
				perror("recv");
		}
	
		intConvert = (int *) playedBuffer;
		matches_played = ntohl(*intConvert);
		
		//Recieves number of games won
		if(recv(sockfd, wonBuffer, sizeof(int), 0)==-1){
				perror("recv");
		}
		
		intConvert = (int *) wonBuffer;
		matches_won = ntohl(*intConvert);

		printf("\n=============================================================================\n");
		printf("\nPlayer - %s \n", nameBuffer);
		printf("Matches Won - %d \n", matches_won);
		printf("Matches Played - %d \n", matches_played);
		printf("\n=============================================================================");
		
		//Resets the buffer
		memset(nameBuffer, 0, DATAMAX);
		memset(wonBuffer, 0, DATAMAX);
		memset(playedBuffer, 0, DATAMAX);
	}
	}
}

/*
playHangman:

Plays the game of hangman.
*/
void* playHangman(int sockfd, char userprint[]){
	char guessed_letters[DATAMAX] = "";
	char guess[DATAMAX];
	char typeBuffer[DATAMAX];
	char objectBuffer[DATAMAX];
	int gamechoice = htonl(PLAYGAME);
	int used_guesses = 0;
	int guesses;
	char completeBuffer[DATAMAX];
	int *completeInt;
	int complete;
	int remain_send;
	if (send(sockfd, &gamechoice, sizeof(int) ,0) == -1){
			perror("send");
	}
	while(1){
	int flag = 0;
	//Send Recieve Game Information
	send(sockfd, guessed_letters, sizeof(guessed_letters), 0);
	
	remain_send = htonl(used_guesses);
	send(sockfd, &remain_send, sizeof(int), 0);

	
	if(recv(sockfd, objectBuffer, DATAMAX, 0)==-1){
				perror("recv");
				exit(1);
			}
	if(recv(sockfd, typeBuffer, DATAMAX, 0)==-1){
				perror("recv");
				exit(1);
			}
			
	//Set Number of Guesses
	int object_len = strlen(objectBuffer);
	int type_len = strlen(typeBuffer);
	guesses = object_len + type_len + 10;
	if(guesses > MAXIMUM_GUESSES){
		guesses = MAXIMUM_GUESSES;
	}
	int remaining = guesses-used_guesses;
	
	//Player Runs out of Guesses
	if(remaining == 0){
	printf("\nGame Over, %s", userprint);
	printf("\nYou have run out of guesses. The Hangman got you!");
	printf("\n=============================================================================\n\n");
	break;
	}
	//Check Number of Correct Letters
		int correct_letters = 0;
	for(int i = 0; objectBuffer[i] != '\0'; i++){
			for(int j = 0; guessed_letters[j] != '\0'; j++){
					if(objectBuffer[i] == guessed_letters[j]){
					correct_letters++;
					}
			}
				
	}
	for(int i = 0; typeBuffer[i] != '\0'; i++){
			for(int j = 0; guessed_letters[j] != '\0'; j++){
					if(typeBuffer[i] == guessed_letters[j]){
					correct_letters++;
					}
			}
				
	}
	//Display Game Info
	printf("\nGuessed Letters: %s\n", guessed_letters);
	printf("Number of Guesses left: %d \n", remaining);
	printf("Word: %s  %s\n", typeBuffer, objectBuffer);
	//Check if all Letters Guessed
		if(correct_letters == (strlen(objectBuffer) + strlen(typeBuffer))){
		printf("\nGame Over\n\n");
		printf("\nWell Done, %s, You have won Hangman", userprint);
		printf("\n=============================================================================\n");
		break;
	}
	//Make Guess
	printf("\nEnter your guess -");
	int len = strlen(guessed_letters);
	scanf("%s", &guess);
	for(int i = 0; guessed_letters[i] != '\0'; i++){
		if(guess[0] == guessed_letters[i]){
			flag =1;
		}		
	}
	if(flag ==0){
		guessed_letters[len] = guess[0];
		guessed_letters[len+1] = '\0';
	}
	used_guesses++;
	}
}
