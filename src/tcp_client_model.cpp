/*
*	Just a constructor 
*/
#define CLIENT_PORT 3409
#include "tcp_client_model.h"
#include <netinet/in.h>
struct sending
{
    int all;
    int that;
    int size;
    char self;
}me;


TcpClientModel::TcpClientModel() {
	printf("Tcp client created!\n");
}


void TcpClientModel::defaultConfigure(){
    //TcpClientModel.conf.ip = "192.168.1.4";
    //TcpClientModel.conf.numberOfPackages = 16;    
}

/*
*	Main function of tcp client
*	Place your code here
*/
void TcpClientModel::run() {
    TcpClientModel::defaultConfigure();
    int i;
    int count = 0;
    int sockfd;
    struct sockaddr_in addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("Socket error");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CLIENT_PORT);
    if(inet_aton(conf.ip, &addr.sin_addr) == 0)
    {
        perror("Address error");
        exit(1);
    }
    if(connect(sockfd, (struct sockaddr *)& addr, sizeof(addr)) <0)
    {
        perror("connection error \n"); 
        exit(1);
    }

    me.all = conf.numberOfPackages;
    for(i = 0; i <= conf.numberOfPackages; i++)
    {
        me.that = i;
        me.self = 'S';
        me.size = sizeof(me.self);
        if(send(sockfd, (void *)&me, sizeof(me),0) == -1)
            printf("Send error with package number %d\n", i);
        else
            count++;
    }
    printf("Try send packages - %d\n", i);
    printf("Sent without errors - %d\n", count);
    count = i - count;
    printf("Lost packages - %d\n", count);
    close(sockfd);
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpClientModel::configure(struct configure_struct *) {
}
