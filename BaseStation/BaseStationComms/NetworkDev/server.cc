#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>

#include <pthread.h>

#include <iostream>
#include <errno.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void *runServer(/*int*/void* portVar)
{
    int port = (int)portVar;
    
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        cerr << "Socket creation error: " << errno << endl;

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1 ) 
        cerr << "Bind error: " << errno << endl;

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    bool cont = true;

    while(cont)
    {
        cout << "Starting new connection, accepting..." << endl;
        //if( (newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1)
        if( (newsockfd = accept4(sockfd, (struct sockaddr *) &cli_addr, &clilen, SOCK_NONBLOCK)) == -1)
            cerr << "Accept error: " << errno << endl;
        cout << "Connection accepted..." << endl;
        while(cont)
        {
            bzero(buffer,256);
            while( (n = read(newsockfd,buffer,255)) == 0);
            if( n == -1 && errno != 11)
                cerr << "Read error: " << errno << endl;

            if(n > 0)
            {
                strtok(buffer, "\n");
                if(string(buffer) == "close") //Closes current connection
                {
                    break;
                }
                else if(string(buffer) == "quit") //Quits/closes the entire server
                {
                    cont = false;
                }

                printf("Here is the message(s): %s\n",buffer);

                if( (n = write(newsockfd,"I got your message",18)) < 0)
                    cerr << "Write error: " << errno << endl;
            }
        }
    }
    cout << "Program closing..." << endl;
    close(newsockfd);
    close(sockfd);
    
    pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    pthread_t serverThread;
    
    int port = atoi(argv[1]);
    pthread_create(&serverThread, NULL, runServer, (void*)port );
    
    pthread_exit(NULL);
    //Does this wait for other packets to finish?    
    cout << "Exiting..." << endl;

    return 0; 
}
