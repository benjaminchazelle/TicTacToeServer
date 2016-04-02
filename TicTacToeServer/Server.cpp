#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#include <string>
#include <iostream>

#ifdef WIN32

	#include <winsock2.h> 
	#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
	#define close(s) closesocket(s)

#elif defined (linux) 

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
	typedef struct in_addr IN_ADDR;

#else 

	#error not defined for this platform

#endif


#define PORT 3490	
#define MAX_CLIENTS 30	 
#define MAXDATASIZE 1024

typedef struct Arguments {

	int socket;
	struct sockaddr_in addr;

} Arguments;


void* Server::onClientTalk(void *_args) {

	Arguments *args = (Arguments*)(_args);

	char date_string[] = "NOW"; 

	int new_fd = args->socket;
	struct sockaddr_in their_addr = args->addr;

	if (new_fd < 0) {
		perror("ERROR on accept");
		exit(1);
	}


	if(send(new_fd, date_string, strlen(date_string), 0) < 0) {
		perror("ERROR writing to socket");
		exit(1);
	}


	pthread_exit(NULL);

	return _args;
}

Server::Server(void)
{

}


void Server::start() {


	#ifdef WIN32

		WSADATA wsa;

		int err = WSAStartup(MAKEWORD(2, 2), &wsa);

		if(err < 0)
		{
			puts("WSAStartup failed !");
			exit(EXIT_FAILURE);
		}

		int sin_size = sizeof(struct sockaddr);

	#else

		unsigned int sin_size = sizeof(struct sockaddr);

	#endif

	int opt = 1;
	int master_socket, new_socket , client_socket[MAX_CLIENTS], activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;
	char buffer[MAXDATASIZE]; 
	fd_set readfds;
	char message[] = "ECHO Daemon v1.0 \r\n";


	for (i = 0; i < MAX_CLIENTS; i++) 
	{
		client_socket[i] = 0;
	}

	//create a master socket
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
	{
		perror("Master socket failed");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections 
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
	{
		perror("Setsockopt failed");
		exit(EXIT_FAILURE);
	}

	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//bind the socket to localhost
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	//try to specify maximum of 3 pending connections for the master socket
	if (listen(master_socket, 3) < 0)
	{
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	std::cout << "Server is listening on port " << PORT << std::endl;

	//accept the incoming connection

	std::cout << "Waiting for connections ..." << std::endl;

	while(true) 
	{
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

		//add child sockets to set
		for ( i = 0 ; i < MAX_CLIENTS ; i++) 
		{
			//socket descriptor
			sd = client_socket[i];

			//if valid socket descriptor then add to read list
			if(sd > 0) {
				FD_SET( sd , &readfds);
			}

			//highest file descriptor number, need it for the select function
			if(sd > max_sd) {
				max_sd = sd;
			}
		}

		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0) && (errno!=EINTR)) 
		{
			perror("Select error");
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds)) 
		{

			if((new_socket = accept(master_socket, (struct sockaddr *)&address, &sin_size)) == -1)
			{
				perror("Accept failed");
				exit(EXIT_FAILURE);
			}

			//inform user of socket number - used in send and receive commands

			std::cout << "New connection #" << new_socket << " from" <<  inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;

			//send new connection greeting message
			if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
			{
				perror("Send failed");
			}

			std::cout << "Welcome message sent successfully" << std::endl;

			//add new socket to array of sockets
			for (i = 0; i < MAX_CLIENTS; i++) 
			{
				//if position is empty
				if( client_socket[i] == 0 )
				{
					client_socket[i] = new_socket;
					std::cout << "Adding to list of sockets as " << i << "\n" << std::endl;

					break;
				}
			}
		}

		//else its some IO operation on some other socket :)
		for (i = 0; i < MAX_CLIENTS; i++) 
		{
			sd = client_socket[i];

			if (FD_ISSET( sd , &readfds)) 
			{
				//Check if it was for closing , and also read the incoming message
				if ((valread = recv( sd , buffer, MAXDATASIZE, 0)) < 0)
				{

					//Somebody disconnected , get his details and print
					getpeername(sd , (struct sockaddr*)&address , &sin_size);

					std::cout << "Client #" << i << " ("<< inet_ntoa(address.sin_addr) <<":"<< ntohs(address.sin_port) << ") disconnected" << std::endl,

						//Close the socket and mark as 0 in list for reuse
						close( sd );
					client_socket[i] = 0;

				}
				//Echo back the message that came in
				else
				{
					//set the string terminating NULL byte on the end of the data read
					buffer[valread] = '\0';

					Arguments args;
					args.socket = sd;
					args.addr = address;
					pthread_t thread;

					pthread_create(&thread, NULL, Server::onClientTalk, &args);

					std::cout << "Echo message sent successfully from client #" << i << " : " << buffer << std::endl;
				}
			}
		}
	}



}


Server::~Server(void)
{
}




