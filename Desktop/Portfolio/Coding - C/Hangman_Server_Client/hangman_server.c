/*
Eliot Wilson -n9175504
CAB403 Assessment 1
hangman_server.c
*/
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <netinet/in.h> 
#include <unistd.h>


	#define HANDLER_THREADS 10
	#define DEFAULT_PORT 12345
	#define DATAMAX 255
	#define MAXIMUM_GUESSES 26
	#define SUCCESS 1
	#define FAILURE -1
	#define PLAYGAME 1
	#define SHOWBOARD 2
	#define END 3

pthread_mutex_t request_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;

pthread_mutex_t count_mutex;
pthread_mutex_t read_mutex;
pthread_mutex_t write_mutex;

int rc;
int sockfd;
int number_requests = 0;
int connected_requests = 0;

FILE * authFile;// = fopen("Authentication.txt","r");
FILE * hangText;// = fopen("hangman_text.txt","r");

struct request{
	int sock_fd;
	struct request* next;
};

struct request* current_requests = NULL;
struct request* last_request = NULL;


struct score_entry{
	char *name;
	int games_played;
	int games_won;
	struct score_entry *next;
};

struct score_entry* scoreboard = NULL;

int connection_actions(int sockfd);
int getBoardLength();
int checkEntry(char username[]);
void updateBoard(char username[], int complete);
void sendBoardInfo(int new_fd, struct score_entry* item);
void createEntry(char username[], int complete, int played);
void addToEntry(char username[], int complete);
void removeFromBoard(char username[]);
void reorderBoard(char username[]);
void signal_handle(int handle);


void readLock(){
	pthread_mutex_lock(&read_mutex);
	pthread_mutex_lock(&count_mutex);
	rc++;
	if(rc==1) pthread_mutex_lock( &write_mutex);
	pthread_mutex_unlock (&count_mutex);
	pthread_mutex_unlock(&read_mutex);
}

void readRelease(){
	pthread_mutex_lock(&count_mutex);
	rc--;
	if(rc==0 ) pthread_mutex_unlock( &write_mutex);
	pthread_mutex_unlock (&count_mutex);
}

void writeLock(){
	pthread_mutex_lock(&read_mutex);
	pthread_mutex_lock(&write_mutex);

}

void writeRelease(){
	pthread_mutex_unlock(&read_mutex);
	pthread_mutex_unlock(&write_mutex);
}
/*
add_connection:

Allocates the new connection to memory adds it to the current request structure
*/
void add_connection(int new_fd, pthread_mutex_t* p_mutex, pthread_cond_t* p_cond_var){
	int rc;
	struct request* new_connection;

	
	new_connection = (struct request*)malloc(sizeof(struct request));
	if(!new_connection){
		fprintf(stderr, "New Connection Failed: No Memory\n");
		exit(1);
	}
	new_connection->sock_fd = new_fd;
	new_connection->next= NULL;
	
	rc= pthread_mutex_lock(p_mutex);
	
	if(number_requests ==0){
		current_requests = new_connection;
		last_request = new_connection;
	}
	else{
		last_request->next= new_connection;
		last_request = new_connection;
	}
	number_requests++;
	
	rc= pthread_mutex_unlock(p_mutex);
	rc= pthread_cond_signal(p_cond_var);
}

/*
get_connection:

Returns the next available connection in the threadpool
*/
struct request* get_connection(pthread_mutex_t* p_mutex){
	int rc;
	struct request* new_connection;
	rc = pthread_mutex_lock(p_mutex);
	
	if(number_requests >0){
		new_connection = current_requests;
		current_requests=new_connection->next;
		if(current_requests == NULL){
			last_request = NULL;
		}
		number_requests--;
		connected_requests++;
	}
	else{
		new_connection = NULL;
	}
	
	rc=pthread_mutex_unlock(p_mutex);
	return new_connection;

}


/*
connection_handler:

Passes the connection socket file descriptor into the connection_actions function
(which runs the main server functions)
*/
void connection_handler(struct request* new_connection){ 
	int terminate = connection_actions(new_connection->sock_fd);
	if(terminate){
		close(new_connection->sock_fd);
	}
}

/*
connection_loop_handler:

Loops through the threadpool and handles each request. Else waits for a connection to handle.
*/
void* connection_loop_handler(void* data){
	int rc;
	struct request* new_connection;
	
	rc=pthread_mutex_lock(&request_mutex);
	
	while(1){
	
	if(number_requests >0){
		new_connection = get_connection(&request_mutex);
		if(new_connection){
			rc = pthread_mutex_unlock(&request_mutex);
			connection_handler(new_connection);
			free(new_connection);
			rc = pthread_mutex_lock(&request_mutex);
		}
	}
	else{
	rc = pthread_cond_wait(&got_request, &request_mutex);
	}
	}
}

/*
signal_handle:

If a SIGINT is recieved, the server is gracefully existed.
I.E. All open files are closed, structures freed and connections terminated.
*/
void signal_handle(int handle){
	struct request* new_connection;
	if (authFile != NULL){
	printf("\n Closing Authentication");
		fclose(authFile);
	}
	if (hangText != NULL){
	printf("\n Closing Text File");
		fclose(hangText);
	}
	printf("\nFreeing Scoreboard");
	free(scoreboard);
	
	printf("\nFreeing Connected Threads\n");
	while(number_requests !=0){
	
		if(number_requests >0){
			new_connection = get_connection(&request_mutex);
			if(new_connection){
				free(new_connection);
			}
		}
	}
	
	exit(1);
}

int main(int argc, char *argv[])
{
	int new_fd; 
	struct sockaddr_in my_addr;   
	struct sockaddr_in their_addr;
	socklen_t sin_size;
	int *passInt;
	int password, passTokInt, login;
	int port = DEFAULT_PORT;
	int counter;
	int thread_id[HANDLER_THREADS];
	pthread_t p_threads[HANDLER_THREADS];
	struct timespec delay;
	char *username;
	char *passTok;
	char userBuffer[DATAMAX];
	char passBuffer[DATAMAX];
	char * authLine= NULL;
	char * hangLine = NULL;
	char authDelim[6] = " \t\n";
	char passLine[DATAMAX];
	char optionBuffer[DATAMAX];
	int *optionInt;
	int option = 0;
	size_t len =0;
	ssize_t read;
	
	signal(SIGINT,signal_handle);
	
	for(counter=0; counter< HANDLER_THREADS; counter++){
		thread_id[counter] = counter;
		pthread_create(&p_threads[counter], NULL, connection_loop_handler, (void*)&thread_id[counter]);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	
	if (argc == 2) {
		port = atoi(argv[1]);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);     
	my_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) \
	== -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, HANDLER_THREADS) == -1) {
		perror("listen");
		exit(1);
	}
	
	//INITIATE MUTEXES
	rc = 0;
	pthread_mutex_init(&read_mutex, NULL);
	pthread_mutex_init(&write_mutex, NULL);
	pthread_mutex_init(&count_mutex, NULL);

	printf("Awaiting Client Connection...\n");

	while(1) {
	if(connected_requests <= HANDLER_THREADS){
			sin_size = sizeof(struct sockaddr_in);
			if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, \
			&sin_size)) == -1) {
				perror("accept");
				continue;
			}
			printf("server: got connection from %s\n", \
				inet_ntoa(their_addr.sin_addr));
			add_connection(new_fd, &request_mutex, &got_request);
		}
		if(connected_requests > HANDLER_THREADS){
			sin_size = sizeof(struct sockaddr_in);
					if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, \
					&sin_size)) == -1) {
						perror("accept");
						continue;
					}
					close(new_fd);
			printf("Threadpool Full: Connection Refused");
		}
	}
}

/*
getBoardLength:

Returns the number of entires in the scoreboard sturcture.
*/
int getBoardLength(){
	int length = 0;
	struct score_entry* entry = scoreboard;
	
	while(entry != NULL){
	entry = entry->next;
	length++;
	}
	return length;
}

/*
sendBoardInfo:

Sends the Name, Won Games, and Played games for each entiry in the scoreboard sturcture to the client
*/
void sendBoardInfo(int new_fd, struct score_entry* item){
	struct score_entry* entry = item;
	int played_games;
	int won_games;
	char *username;
	int sendInt;
	int ackBuffer[DATAMAX];
	
	while(entry != NULL){
		played_games = entry->games_played;
		won_games = entry->games_won;
		username = entry->name;
		
		if (send(new_fd, username, sizeof(username) ,0) == -1){
					perror("send");
		}
		
		if (recv(new_fd, ackBuffer, sizeof(int) ,0) == -1){
					perror("recv");
		}
		
		sendInt = htonl(played_games);
		if (send(new_fd, &sendInt, sizeof(int) ,0) == -1){
					perror("send");
		}
		
		sendInt = htonl(won_games);
		if (send(new_fd, &sendInt, sizeof(int) ,0) == -1){
					perror("send");
		}
		
		entry = entry->next;
	}
}
/*
checkEntry:

Checks if an entry exist in the scoreboard sturcture.
Returns 1 if entry exists, Else returns 0.
*/
int checkEntry(char username[]){
struct score_entry* entry = scoreboard;
	
	while(entry != NULL){
	
		if((strcmp(username, entry->name)==0)){
			return 1;
		}
		entry = entry->next;
	}
	return 0;
}

/*
createEntry:

Creates an entry in the scoreboard sturcture and allocates in the correct position
depending on its name, games played and games won.
*/
void createEntry(char username[], int complete, int played){
		struct score_entry* new_entry;
		new_entry = (struct score_entry*)malloc(sizeof(struct score_entry));
		new_entry->name = username;
		new_entry->games_played = played;
		new_entry->games_won = complete;
		new_entry->next = NULL;
		//If no entires, make first entry.
	if(getBoardLength() == 0){
			scoreboard = new_entry;
			return;
		}
	else{
			struct score_entry * current_entry = scoreboard;
			struct score_entry* previous = NULL;
			while(current_entry != NULL){
			//Check if new entry has fewer games won.
			if(new_entry->games_won < current_entry->games_won){
				new_entry->next = scoreboard;
				scoreboard=new_entry;
				return;	
			}
			//Check if new entry has equal games won
			if(new_entry->games_won == current_entry->games_won){
				//Check if new entry has less win percentage
				if(new_entry->games_won - new_entry->games_played  < current_entry->games_won - current_entry->games_played){				
				if(previous !=NULL){
						new_entry->next = current_entry;
						previous->next = new_entry;
						return;
					}
					else{
						new_entry->next = scoreboard;
						scoreboard=new_entry;
						return;
					}
				}
				//Check if new entry has greater win percentage
				if(new_entry->games_won - new_entry->games_played > current_entry->games_won - current_entry->games_played){		
				new_entry->next = current_entry->next;
				current_entry->next = new_entry;
				return;
				}
				//Check if new entry has equal win percentage
				if(new_entry->games_won - new_entry->games_played  == current_entry->games_won - current_entry->games_played){
				//Compare enty names for less than
				if((strcmp(new_entry->name, current_entry->name)) < 0){
					if(previous !=NULL){
						new_entry->next = current_entry;
						previous->next = new_entry;
						return;
					}
					else{
						new_entry->next = scoreboard;
						scoreboard=new_entry;
						return;
					}
				}
				//Compare enty names for greater than
				if((strcmp(new_entry->name, current_entry->name) > 0) &&(current_entry->next == NULL || strcmp(new_entry->name, current_entry->next->name) < 0 ) || (new_entry->games_won < current_entry->next->games_won)){
					new_entry->next = current_entry->next;
					current_entry->next = new_entry;
					return;
				}
			
			}
			}
			//Check if new entry is greater games won
				if(new_entry->games_won > current_entry->games_won && (current_entry->next ==NULL || current_entry->next->games_won > new_entry->games_won)){
					new_entry->next = current_entry->next;
					current_entry->next = new_entry;
					return;
				}
			//Iterate through scoreboard
			previous = current_entry;
			current_entry = current_entry-> next;
			}
	}
		
}

/*
addToEntry:

Updates the existing games played and won within an entry by name on the scoreboard.
*/
void addToEntry(char username[], int complete){
	struct score_entry* entry = scoreboard;
	
		while(entry != NULL){
			if((strcmp(username, entry->name)==0)){
				strcpy(entry->name, username);
				entry->games_played = entry->games_played + 1;
				entry->games_won = entry->games_won + complete;
			}
			entry = entry->next;
		}
}

/*
reorderBoard:

Removes and re-enters a node, by name, in the correct position within the scoreboard.
*/
void reorderBoard(char username[]){
	struct score_entry* reorder_entry = scoreboard;
	int won;
	int played;
	char name[DATAMAX];
		while(reorder_entry != NULL){
			if((strcmp(username, reorder_entry->name)==0)){
				
				won = reorder_entry->games_won;
				played = reorder_entry->games_played;

				removeFromBoard(username);

				break;
			}
			reorder_entry = reorder_entry->next;
		} createEntry(username,won,played);
}

/*
removeFromBoard:

Removes a node by name from the scoreboard.
*/
void removeFromBoard(char username[]){
		struct score_entry* entry = scoreboard;
		struct score_entry* previous = NULL;
		
		while(entry!= NULL){
			if((strcmp(username, entry->name)==0)){				
				if(previous == NULL){
					scoreboard=entry->next;
					free(entry);
					return;
				}
				
				if(previous && entry->next != NULL){
					previous->next =entry->next;
					free(entry);
					return;
				}
				
				if(previous && entry->next == NULL){
					previous->next =NULL;
					free(entry);
					return;
				}
				
			}
			previous=entry;
			entry = entry->next;
			}
}

/*
updateBoard:

Determines if current entries should be updated or if there is a new entry to the scoreboard.
Mutex locked to assure correct formatting of the scoreboard.
*/
void updateBoard(char username[], int complete){
	writeLock();
	if(checkEntry(username) == 1){
		addToEntry(username, complete);
		reorderBoard(username);
		writeRelease();
		return;
	}
	else{
		int played = SUCCESS;
		createEntry(username, complete, played);
		writeRelease();
		return;
		}
}

/*
connection_actions:

Completes actions required by the server. I.E Authentication, Gameplay, Scoreboard, Termination.
Returns if the actions have been termiated or if there is an uncorrectable error.
*/
int connection_actions(int new_fd){
	int *passInt;
	int password, passTokInt, login;
	int port = DEFAULT_PORT;
	char *username;
	char *passTok;
	char userBuffer[DATAMAX];
	char passBuffer[DATAMAX];
	char * authLine= NULL;
	char * hangLine = NULL;
	char authDelim[6] = " \t\n";
	char hangDelim[3] = ",\n";
	char passLine[DATAMAX];
	char optionBuffer[DATAMAX];
	int *optionInt;
	int option = 0;
	size_t len =0;
	ssize_t read;
	ssize_t hangread;

			if(recv(new_fd, userBuffer, DATAMAX, 0)==-1){
				perror("recv");
				return FAILURE;
			}
			if(recv(new_fd, passBuffer, sizeof(int), 0)==-1){
				perror("recv");
				return FAILURE;
			}
			
			passInt = (int *) passBuffer;
			password = ntohl(*passInt);
			authFile = fopen("Authentication.txt","r");
			
			
			//Check recieved username and password against entries in the Authentication File.
			while((read = getline(&authLine, &len, authFile)) != -1){
				username = strtok(authLine, authDelim);
				passTok = strtok(NULL, authDelim);
				passTokInt = atoi(passTok);
				if((strcmp(username, userBuffer)==0) && (password - passTokInt == 0)){
					login=htonl(SUCCESS);
					break;
				}
			}	
			
			rewind(authFile);
			fclose(authFile);
			authFile=NULL;
			free(authLine);
			fflush(stdout);
			//Confirm login
			if (send(new_fd, &login, sizeof(int) ,0) == -1){
				perror("send");
			}
			//Recieve client menu option
		while(1){
			if(recv(new_fd, optionBuffer, sizeof(int), 0)==-1){
				perror("recv");
				return FAILURE;
			}
			
		optionInt = (int *) optionBuffer;
		option = ntohl(*optionInt);
		
		//Play Hangman
		if(option == PLAYGAME){
			char *object;
			char *type;
			char newobject[DATAMAX];
			char newtype[DATAMAX];
			char remainBuffer[DATAMAX];
			int *remainInt;
			int used_guesses;
			int remaining;
			hangText = fopen("hangman_text.txt","r");
			int wordcount = 0;
			time_t t;
			srand((unsigned) time(&t));
			int line_count=0;
			
			//Confirm length of Hangman Text
			while((hangread = getline(&hangLine, &len, hangText)) != -1){
				line_count++;
			}
			rewind(hangText);
			
			int random_word = rand() % line_count;
			int correct_letters;
			int complete = 0;
			
			//Retrieve random word from Hangman Text
			while((hangread = getline(&hangLine, &len, hangText)) != -1){
				if(wordcount == random_word){
					object = strtok(hangLine, hangDelim);
					type = strtok(NULL, hangDelim);
					break;
				}
				wordcount++;
			}
			rewind(hangText);
			fclose(hangText);
			hangText = NULL;
			while(complete == 0){
				correct_letters = 0;
				char guessed_chars[DATAMAX];
				
				//Recieve remaining characters and guesses
				if(recv(new_fd, guessed_chars, sizeof(guessed_chars)+1, 0)==-1){
					perror("recv");
					return FAILURE;
				}
				if(recv(new_fd, remainBuffer, sizeof(int), 0)==-1){
					perror("recv");
					return FAILURE;
				}
			
				remainInt = (int *) remainBuffer;
				used_guesses = ntohl(*remainInt);
			
				int object_len = strlen(object);
				int type_len = strlen(type);
				int guesses = object_len + type_len + 10;
				if(guesses > MAXIMUM_GUESSES){
					guesses = MAXIMUM_GUESSES;
				}
				remaining = guesses-used_guesses;
			
						
				//Convert unguessed characters for Type to underscores
				for(int i = 0; type[i] != '\0'; i++){
					int flag = 0;
					for(int j = 0; guessed_chars[j] != '\0'; j++){
						if(type[i] == guessed_chars[j]){
						flag = 1;
						}
					}
					if(flag ==0){
					newtype[i] = '_';
					}
					if(flag ==1){
					newtype[i] = type[i];
					correct_letters++;
					}
					newtype[i+1] = '\0';
				}
				//Convert unguessed characters for Object to underscores
				for(int i = 0; object[i] != '\0'; i++){
					int flag = 0;
					for(int j = 0; guessed_chars[j] != '\0'; j++){
						if(object[i] == guessed_chars[j]){
						flag = 1;
						}
					}
					if(flag ==0){

					newobject[i] = '_';
					}

					if(flag ==1){
					newobject[i] = object[i];
					correct_letters++;
					}
					newobject[i+1] = '\0';
				}
			
				//Sends converted word to client
				if(send(new_fd, newobject, DATAMAX, 0)==-1){
					return FAILURE;
				}
				if(send(new_fd, newtype, DATAMAX, 0)==-1){
					return FAILURE;
				}

				//Checks if the client has succesfully guessed all characters
				if(correct_letters == (strlen(object) + strlen(type))){
					//Updates board if succesfull and terminates game
					complete = SUCCESS;
					updateBoard(userBuffer, complete);
					option = 0;
					break;
				}
				
				//Checks if the client has used all guesses
				if(remaining ==0){
					//Updates board if correct and terminates game
					updateBoard(userBuffer, complete);
					option = 0;
					break;
				}

				fflush(stdout);
			}
			
		}
		//Sends Scoreboard
		if(option == SHOWBOARD){
			readLock();
			//Sends length of scoreboard to the user 
			int length = getBoardLength();
			int length_send=htonl(length);
			if(send(new_fd, &length_send, DATAMAX, 0)==-1){
					return FAILURE;
				}
			fflush(stdout);
			
			//Sends scoreboard to the user
			sendBoardInfo(new_fd, scoreboard);
			fflush(stdout);
			readRelease();
			option = 0;
		}

		}
}

