//#include "tcp_server_model.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctime>
#include <iostream>

//structure with data
struct msg{
	int all;//number of datapockets
	int that;//count of current datapocket
	char self;//data
	int size;//size of datapocket
};

/*
*	Just a constructor 
*/
//TcpServerModel::TcpServerModel() {
//	printf("Tcp Server created!\n");
//}


void TcpSocketCreating(int &lis,struct sockaddr_in add) {
	lis = socket(AF_INET, SOCK_STREAM, 0);//descriptor of listening socket
    
	if(lis < 0){ //catching error in creating of socket
        perror("socket error\n");
        exit(1);
    }
    	
	add.sin_family = AF_INET; //filling the structure
	add.sin_port = htons(3409);
	add.sin_addr.s_addr = htonl(INADDR_ANY);
    	
	if ( bind (lis , (struct sockaddr *) & add , sizeof (add) ) < 0){
		perror( "binding error\n" ); //binding of socket and seeking for mistake
    	exit(2);
	}
	else
		printf("Succesfull binding\n");
}


void TcpAccepting(int &lis,int &s, clock_t ti1, clock_t ti2, struct msg b)
{

	int bytes_read;
	   while(1){//cyckle of listening  and accepting
        	int k;
			s = accept(lis, NULL, NULL);
        
			if(s < 0){
            	perror("accepting error\n");
            	exit(3);
        	}
			else
				printf("Succesfull accepting\n");

			printf("Accepting friendly forces\n");
			printf("Reading...\n");
			printf("------------\n");
        	
			while(1){ //cyckle of reading of datapockets
            	bytes_read = recv(s,(void *)&b, sizeof(b), 0);
            	
				if(bytes_read <= 0){	
					printf("End of Reading!\n");
					break;
				}
				else{
					printf("%d\n",k);
					printf("%d\n",b.all);
					k = k+1;
					ti2 = clock();
				}
			}	
    		printf("%d\nClock is here",(ti2 - ti1)/10000);
			printf("%d\n", (b.all - k));
			ti1 = clock();
			k = 0;
        	close(s);
	} 
}

/*
*	Main function of tcp Server
*	Place your code here
*/
int main() {
	//TcpServerModel::configure();
	clock_t t1, t2;
	int y,i,k;
	int n[100];
    int sock, listener;
    struct sockaddr_in addr;
    int bytes_read;
	struct msg buf;
	k = 0;
	t1 = clock();

	TcpSocketCreating(listener, addr);
    listen(listener, 1);//Listening of port

    printf("Listening...\n");

	TcpAccepting(listener,sock,t1,t2,buf);   
return 1;
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
//void TcpServerModel::configure(struct configure_struct *) {
//
//}
