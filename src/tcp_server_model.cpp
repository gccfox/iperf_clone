#include "tcp_server_model.h"
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
TcpServerModel::TcpServerModel() {
	printf("Tcp Server created!\n");
}


/*
*	Main function of tcp Server
*	Place your code here
*/
void TcpServerModel::run() {
	TcpServerModel::configure();
	clock_t t1, t2;
	int y,i,k;
	int n[100];
    int sock, listener;
    struct sockaddr_in addr;
    int bytes_read;
	struct msg buf;
	k = 0;
	t1 = clock();

    listener = socket(AF_INET, SOCK_STREAM, 0);//descriptor of listening socket
    
	if(listener < 0){ //catching error in creating of socket
        perror("socket error\n");
        exit(1);
    }
    	
	addr.sin_family = AF_INET; //filling the structure
	addr.sin_port = htons(3409);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	
	if ( bind (listener , (struct sockaddr *) & addr , sizeof (addr) ) < 0){
		perror( "binding error\n" ); //binding of socket and seeking for mistake
    	exit(2);
	}
	else
		printf("Succesfull binding\n");

    listen(listener, 1);//Listening of port

    printf("Listening...\n");
    while(1){//cyckle of listening  and accepting
        	
			sock = accept(listener, NULL, NULL);
        
			if(sock < 0){
            	perror("accepting error\n");
            	exit(3);
        	}
			else
				printf("Succesfull accepting\n");

			printf("Accepting friendly forces\n");
			printf("Reading...\n");
			printf("------------\n");
        	
			while(1){ //cyckle of reading of datapockets
            	bytes_read = recv(sock,(void *)&buf, sizeof(buf), 0);
            	
				if(bytes_read <= 0){	
					printf("End of Reading!\n");
					break;
				}
				else{
					printf("%d\n",k);
					printf("%d\n",buf.all);
					k = k+1;
					t2 = clock();
				}
			}	
    		printf("%d\nClock is here",(t2 - t1)/10000);
			printf("%d\n", (buf.all - k));
			t1 = clock();
			k = 0;
        	close(sock);
	} 
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpServerModel::configure(struct configure_struct *) {

}
