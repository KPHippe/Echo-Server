/*
 Kyle Hippe
 Assignment 1
 Echo Server
 386 Fall 2018
 9/19/18
 c gnu compiler
 textbook
 Client side sends a message to server side, server side receives message and sends it back (echoes) to the client.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256


int main()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int len;
	int s, new_s;
	
	/* build address data structure */
	
	bzero((char*)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERVER_PORT);
	
	/*setup passive open*/
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("simplex-talk:socket");
		exit(1);
	}
	
	if ((bind(s, (struct sockaddr*)&sin, sizeof(sin))) < 0){
		perror("simplex-talk: bind");
		exit(1);
	}

	listen(s, MAX_PENDING);
	
	/* wait for connection, then receive and print text*/
	
	while(1){
		printf("inside while(1)\n");
		if ((new_s = accept(s, (struct sockaddr*) &sin, &len)) < 0){
			perror("simplex-talk:accept");
			exit(1);
		}
		printf("received connection\n");
		while (len = recv(new_s, buf, sizeof(buf), 0))
			fputs(buf, stdout);
		close (new_s);
		
		/*send portion*/
		
		buf[MAX_LINE -1] = '\0';
		len = strlen(buf) + 1;
		send(s, buf, len, 0);
	}
}
