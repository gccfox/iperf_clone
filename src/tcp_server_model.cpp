#include "tcp_server_model.h"
//structure with data
struct msg{
//	int all;//number of datapockets
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


void TcpServerModel::createTcpSocket(int &lis,struct sockaddr_in add) {
	lis = socket(AF_INET, SOCK_STREAM, 0);//descriptor of listening socket
    
	if(lis < 0){ //catching error in creating of socket
        perror("socket error\n");
        exit(1);
    }
    	
	add.sin_family = AF_INET; //filling the structure
	add.sin_port = htons(DEFAULT_PORT);
	add.sin_addr.s_addr = htonl(INADDR_ANY);
    	
	if ( bind (lis , (struct sockaddr *) & add , sizeof (add) ) < 0){
		perror( "binding error\n" ); //binding of socket and seeking for mistake
    	exit(2);
	}
	else
		printf("Succesfull binding\n");
}


void TcpServerModel::acceptTcp(int lis,int &s, struct msg b)
{

	int bytes_read;
	struct timespec time1;
	struct timespec time2;
	unsigned long int hope;
	   while(1){//cyckle of listening  and accepting
 	  	clock_gettime(0, &time1);
	 	long int k;
		//printf("%d\n", time1.tv_nsec);
		k = 0;
		s = accept(lis, NULL, NULL);
        	printf("Try");
		if(s < 0){
            		perror("accepting error\n");
            		exit(3);
        	}
			else
				printf("Succesfull accepting\n");

			printf("Accepting friendly forces\n");
			printf("Reading...\n");
			printf("------------\n");
		long int g;
		g=0;	
			bytes_read = recv(s,(void *)&g, sizeof(int), 0);

                                if(bytes_read <= 0){
                                        //printf("End of Reading!\n");
					break;
                                }
                                else{
                                  	//k = k+1;
					clock_gettime(0, &time2);
					clock_gettime(0, &time1);
					printf("%d\n", time2.tv_nsec);
					         }

        	
			for(int i=0; i<g; i++){ //cyckle of reading of datapockets
            	bytes_read = recv(s,(void *)&b, sizeof(b), 0);
            		
				if(bytes_read <= 0){	
					printf("End of Reading!\n");
					//k = k-1; 
					//clock_gettime(3,&time2);
					}
				else{
					k = k+1;
					//printf("%d : %d %d %d\n", ntohs(b.that), b.self, b.size, g);	
					clock_gettime(0,&time2);
					hope =  time2.tv_sec - time1.tv_sec;
					printf("%d\n", hope);
                                        printf("%d\n", time1.tv_nsec);
					//printf("iteration -%d\n", k);
                                        	
				}
			}
		clock_gettime(0,&time2);
		printf("Время работы в секундах:\n");
	 	printf("%d\n",hope);
		printf("Пакетов %d из %d получено\n",k,g);
		unsigned int kb_speed = (k * sizeof(struct msg));
		kb_speed = kb_speed/1024;
		printf("Скорость - %d kbyte/s\n",kb_speed/hope);
		k = 0;
		clock_gettime(0,&time2);
        	close(s);
		exit(0);
	} 
}



/*
*	Main function of tcp Server
*	Place your code here
*/
void TcpServerModel::run() {
	int sock, listener;
    	struct sockaddr_in addr;
    	int bytes_read;
	struct msg buf;

	TcpServerModel::createTcpSocket(listener, addr);
    listen(listener, 1);//Listening of port

    printf("Listening...\n");

	TcpServerModel::acceptTcp(listener,sock,buf);   
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpServerModel::configure(struct configure_struct *) {

}
