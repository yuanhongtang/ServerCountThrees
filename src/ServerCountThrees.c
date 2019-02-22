/*
 ============================================================================
 Name        : ServerCountThrees.c
 Author      : Courtney Brown
 Version     :
 Copyright   : copyright 2014. All Rights Reserved.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "readInt32BitLE.h"

void doprocessing (int sock)
{
    int n;
    char buffer[256];
	FILE *ptr_threesFile;
	int readValue = 0;
	int threesCount =0;

    bzero(buffer,256);

    n = read(sock,buffer,255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    printf("ServletCountThrees Received Input: %s\n",buffer);

	ptr_threesFile = fopen("threesData.bin","rb");
	while (!feof(ptr_threesFile)) {
		readValue = readInt32BitLE(ptr_threesFile);
		if (readValue == 3) ++threesCount;
	}

	fclose(ptr_threesFile);

	fprintf(stdout,"%d",threesCount);
	fflush(stdout);

	sprintf(buffer,"ServerCountThrees Response: %d\n",threesCount);
	int msgLength = strlen(buffer);
    n = write(sock,buffer,msgLength);
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
}

int main(int argc, char *argv[] ) {

	puts("!!!Count Threes!!!"); /* prints !!!Count Threes!!! */
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;
    int pid;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                          sizeof(serv_addr)) < 0)
    {
         perror("ERROR on binding");
         exit(1);
    }
    /* Now start listening for the clients, here
     * process will go in sleep mode and will wait
     * for the incoming connection
     */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1)
    {
        newsockfd = accept(sockfd,
                (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
        /* Create child process */
        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
	    exit(1);
        }
        if (pid == 0)
        {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    } /* end of while */

	return EXIT_SUCCESS;
}
