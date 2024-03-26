#include "communication.h"
#include "utils.h"

#define PORT 9002
#define BUFFER_SIZE 1024

int createSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("socket creation failed");
    return sockfd;
}

int bindServerSocket(int sockfd) {
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        error("socket binding failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int acceptClientConnection(int sockfd) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int clientSockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
    if (clientSockfd < 0)
        error("socket accepting failed");
    return clientSockfd;
}

char * receiveMessage(int sockfd) {
    char *message = NULL;
    ssize_t bytesReceived;
    ssize_t totalBytes = 0;

    do {
        message = realloc(message, totalBytes + BUFFER_SIZE + 1);
        if (message == NULL) {
            error("memory allocation for message failed");
            return NULL;
        }
        
        bytesReceived = recv(sockfd, message + totalBytes, BUFFER_SIZE, 0);
        if (bytesReceived < 0) {
            error("read from socket failed");
            return NULL;
        }

        printf("Received %ld bytes\n", bytesReceived);
        
        totalBytes += bytesReceived;
    } while (bytesReceived == BUFFER_SIZE);
    
    message[totalBytes] = '\0';
    return message;
}

int communicationMain() {
    int status;
    
    printf("Choose mode:\n");
    printf("1. Create a room\n");
    printf("2. Join a room\n");

    int mode = getNumberInput("\n-> ");

    switch (mode)
    {
    case 1:
        status = createRoom();
        break;
    
    case 2:
        status = joinRoom();
        break;

    default:
        error("invalid mode choice");
        status = EXIT_FAILURE;
    }
    
    return status;
}

int createRoom() {
    printf("Creating server socket\n");
    int sockfd = createSocket();
    if (sockfd < 0)
        return EXIT_FAILURE;

    printf("Binding server socket\n");
    if (bindServerSocket(sockfd) == EXIT_FAILURE) {
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Listening\n");
    listen(sockfd, 5);

    printf("Accepting client connection\n");
    int clientSockfd = acceptClientConnection(sockfd);
    if (clientSockfd < 0) {
        close(sockfd);
        close(clientSockfd);
        return EXIT_FAILURE;
    }

    while (1)
    {
        printf("Receiving message\n");
        char *receivedMessage = receiveMessage(clientSockfd);
        if (receivedMessage == NULL) {
            error("failed to receive a message");
            free(receivedMessage);
            continue;
        }

        printf("Received: %s\n", receivedMessage);
        if (strcmp(receivedMessage, "exit") == 0) {
            free(receivedMessage);
            break;
        }
        free(receivedMessage);

        char *messageToSend = getStringInput("You: ");
        if (send(clientSockfd, messageToSend, strlen(messageToSend), 0) < 0) {
            error("sending the message failed");
            free(messageToSend);
            continue;
        }
        if (strcmp(messageToSend, "exit") == 0) {
            free(messageToSend);
            break;
        }
        free(messageToSend);
    }

    printf("Closing sockets\n");
    close(sockfd);
    close(clientSockfd);
    return EXIT_SUCCESS;
}

int joinRoom() {
    char *host = getStringInput("Enter the host to connect to: ");

    int sockfd = createSocket();

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, host, &serverAddress.sin_addr) <= 0) {
        error("invalid host address");
        free(host);
        close(sockfd);
        return EXIT_FAILURE;
    }
    free(host);

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        error("connection failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    while (1)
    {
        char *messageToSend = getStringInput("You: ");
        if (send(sockfd, messageToSend, strlen(messageToSend), 0) < 0) {
            error("sending the message failed");
            free(messageToSend);
            continue;
        }
        if (strcmp(messageToSend, "exit") == 0) {
            free(messageToSend);
            break;
        }
        free(messageToSend);
        
        printf("Receiving message\n");
        char *receivedMessage = receiveMessage(sockfd);
        if (receivedMessage == NULL) {
            error("failed to receive a message");
            free(receivedMessage);
            continue;
        }

        printf("Received: %s\n", receivedMessage);
        if (strcmp(receivedMessage, "exit") == 0) {
            free(receivedMessage);
            break;
        }
        free(receivedMessage);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}