#include "tcp_server_model.h"
//structure with data
struct msg{
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
*	Creating working socket of tcp Server
*	Place your code here
*/

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
	}else{
		printf("Succesfull binding\n");
		}
}

/*
*	Accepting of Client
*	Place your code here
*/

void TcpServerModel::acceptClient(int lis,int &s)
{
	s = accept(lis, NULL, NULL);
                printf("Try");
                if(s < 0){
                        perror("accepting error\n");
                        exit(3);
                }
                        else
                                printf("Succesfull accepting\n");

                        printf("Accepting friendly forces\n");

}


/*
*	Trying to get Initial Data Pocket
*	Place your code here
*/

void TcpServerModel::receiveInitData(long int &number_of_pockets,int &s, struct msg b){
int bytes_read;
bytes_read = recv(s,(void *)&number_of_pockets, sizeof(int), 0);
if(bytes_read <= 0){
		printf("Error in reading initial data\n");
        	   }else{
	        printf("Successful received initial pocket\n");
                        }
}


/*
*	Print speed of working server
*	Place your code here
*/

void TcpServerModel::printSpeed(unsigned long int time, long int number_of_pockets)
{
	 	unsigned int kb_speed = (number_of_pockets * sizeof(struct msg));
                kb_speed = kb_speed/1024;
		kb_speed = kb_speed/time;
                printf("Скорость - %d kbyte/s\n",kb_speed);
}

void TcpServerModel::printTimeInSec(unsigned long int time)
{
	 printf("Время работы в секундах:\n");
                printf("%d\n",time);

}


void TcpServerModel::printNumberOfPockets(unsigned long int count ,unsigned long int number)
{
	printf("Пакетов %d из %d получено\n",count,number);
	printf("Не дошло: %d\n", (number - count));
	unsigned long int proc = (number - count);
	printf("Процент потерь: %d %\n",proc/number);
}

/*
*	Print statistic of tcp Server
*	Place your code here
*/

void TcpServerModel::printStatistic(unsigned long int time, long int number_of_pockets,unsigned long int count)
{
	TcpServerModel::printSpeed(time,number_of_pockets);
	TcpServerModel::printTimeInSec(time);
	TcpServerModel::printNumberOfPockets(count ,number_of_pockets);
}

/*
*	Main Reading of tcp Server
*	Place your code here
*/

void TcpServerModel::readingTcp(int lis,int &s, struct msg structure_to_write)
{

	int bytes_read;
	struct timespec time1;
	struct timespec time2;
	unsigned long int hope;
	   while(1){                       //cyckle of listening  and accepting
 	  	clock_gettime(0, &time1);
	 	long int count_of_pockets;
		count_of_pockets = 0;
		long int number_of_pockets;
		number_of_pockets = 0;
		
		TcpServerModel::acceptClient(lis, s);
		
		printf("Reading...\n");
                printf("------------\n");

		 TcpServerModel::receiveInitData(number_of_pockets, s, structure_to_write); 

			clock_gettime(0, &time2);
			clock_gettime(0, &time1);

		                	
			for(int i=0; i<number_of_pockets; i++){ //cyckle of reading of datapockets
           

				
				bytes_read = recv(s,(void *)&structure_to_write, sizeof(structure_to_write), 0);
            		
				if(bytes_read <= 0){	
					printf("End of Reading!\n");
					}
				else{
					count_of_pockets = count_of_pockets+1;
					clock_gettime(0,&time2);
					hope =  time2.tv_sec - time1.tv_sec;  		                           	
				}
			}
		clock_gettime(0,&time2);
		
		TcpServerModel::printStatistic(hope, number_of_pockets, count_of_pockets);
		
		count_of_pockets = 0;
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

	TcpServerModel::readingTcp(listener,sock,buf);   
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpServerModel::configure(struct configure_struct *) {

}
