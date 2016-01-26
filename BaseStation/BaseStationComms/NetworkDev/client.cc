#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <pthread.h>

#include <iostream>
#include <errno.h>

using namespace std;

struct hostData
{
    string host;
    string port;
};

bool sendMessage = false; //Should be false
string message;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void *runClient(/*struct hostData*/ void* data)
{
    cout << "Running Client code..." << endl;
    struct hostData* h_data;
    if(!data)
    {
        cout << "passed in data bad, exiting..." << endl;
        exit(0);
    }
    h_data = (struct hostData*) data;
    string tmpHost = h_data->host;
    string tmpPort = h_data->port;    
    
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
        
    server = gethostbyname( (h_data->host).c_str() );
    
    
    if( !(h_data->port).c_str())
    {
        cout << "Port not set" << endl;
        exit(0);
    }
    portno = atoi( (h_data->port).c_str() );
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        cerr << "Socket creation error: " << errno << endl;

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);
    if ( connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1)
    {    
        cerr << "Connection error: " << errno << endl;
        exit(0);
    }
    
    bool cont = true;
    while(cont)
    {
        bzero(buffer,256);
        while( (n = recv(sockfd, buffer, 255, MSG_DONTWAIT ) == 0) && !sendMessage );
        
        if(!sendMessage && n>0) // Should be !sendMessage, means we read something
        {
            if( n == -1)
                cerr << "Read error: " << errno << endl;
            
            strtok(buffer, "\n");
            if(string(buffer) == "close") //Closes current connection
            {
                break;
            }
            else if(string(buffer) == "quit") //Quits/closes the entire server
            {
                cont = false;
            }
            printf("Here is the message: %s\n",buffer);
            
            if( (n = write(sockfd,"I got your message",18)) < 0)
                cerr << "Write error: " << errno << endl;
        }
        else if(sendMessage)//sendMessage is true, means that we need to send a message
        {
            cout << "Attempting to send: " << message << endl;
            
            if( (n = write(sockfd, message.c_str(), strlen( message.c_str() ))) == -1)
                cerr << "Write error: " << errno << endl;
            
            sendMessage = false; //Message was sent, we can lower this flag
            
            if( message == "quit" || message == "close" )
            {
                break;
            }

            bzero(buffer,256);
            if( (n = read(sockfd,buffer,255)) == -1)
                cerr << "Read error: " << errno << endl; 
            printf("%s\n",buffer);
            

        }
        
    }
    
    close(sockfd);
    cout << "Socket closed" << endl;
    delete (struct hostData*)data;
    pthread_exit(NULL);
    cout << "Thread returned" << endl;
}



int main(int argc, char *argv[])
{   
    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    hostData *h_info = new hostData;
    h_info->host = argv[1];
    h_info->port = argv[2];
    
    cout << "pre-host: " << h_info->host << endl;
    cout << "pre-Port: " << h_info->port << endl;
    
    pthread_t clientThread;
    
    pthread_create(&clientThread, NULL, runClient, (void*)h_info ); 
    
    //cout << "MAIN: Create finished" << endl;
    //runClient((void*) &h_info);
    
    while(1)
    {
        cout << "Enter your message: ";
        cin >> message;
        sendMessage = true;
        while(sendMessage);
        cout << "Message sent" << endl;
        if(message == "quit" || message == "close")
            break;
    }
    
    cout << "MAIN: Main before pthread_exit" << endl;
    pthread_exit(NULL);
    
    cout << "MAIN: Main returned" << endl;
    
    return 0;
}