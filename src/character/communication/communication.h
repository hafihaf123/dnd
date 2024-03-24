#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int createSocket();

int bindServerSocket(int sockfd);

int acceptClientConnection(int sockfd);

char * receiveMessage(int sockfd);

int communicationMain();

int createRoom();

int joinRoom();

#endif // COMMUNICATION_H