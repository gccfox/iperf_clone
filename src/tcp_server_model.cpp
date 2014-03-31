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
	printf("TCP_server: accepting client");
	s = accept(lis, NULL, NULL);
	if (s < 0) {
			perror("accepting error\n");
			exit(3);
	} else {
		printf("Succesfull accepting\n");
	}

	printf("Accepting friendly forces\n");

}


/*
*	Trying to get Initial Data Pocket
*	Place your code here
*/

void TcpServerModel::receiveInitData(long int &number_of_pockets,int &s, struct msg b){
	int bytes_read;
	bytes_read = recv(s,(void *)&number_of_pockets, sizeof(int), 0);
	if (bytes_read <= 0){
		printf("Error in reading initial data\n");
    } else {
		printf("Successful received initial pocket\n");
	}
}


/*
*	Print speed of working server
*	Place your code here
*/

void TcpServerModel::printSpeed(long time, long number_of_pockets)
{
	double kb_speed = (number_of_pockets * sizeof(struct msg)) * 1000 / 1024 / time;
	/*printf("speed: %d : %d %u %lu\n", number_of_pockets, kb_speed, kb_speed, kb_speed);
	kb_speed = kb_speed * 1000 / 1024;
	kb_speed = kb_speed / time;*/
	if (kb_speed < 1000) {
		printf("Скорость - %.4f Kbytes/s\n",kb_speed);
	} else {
		kb_speed /= 1024;
		printf("Скорость - %.4f Mbytes/s\n",kb_speed);
	}
}

void TcpServerModel::printTimeInSec(long time)
{
	printf("Время работы в milli секундах:\n");
	printf("%lu\n",time); 
}


void TcpServerModel::printNumberOfPockets(long count ,long number)
{
	printf("Пакетов %d из %d получено\n",count,number);
	printf("Не дошло: %d\n", (number - count));
	long proc = (number - count);
	printf("Процент потерь: %d %\n",proc/number);
}

/*
*	Print statistic of tcp Server
*	Place your code here
*/

void TcpServerModel::printStatistic(long time, long int number_of_pockets,long count)
{
	printSpeed(time,number_of_pockets);
	printTimeInSec(time);
	printNumberOfPockets(count ,number_of_pockets);
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
	long hope;
//while(true) {                       //cyckle of listening  and accepting
	long int count_of_pockets;
	count_of_pockets = 0;
	long int number_of_pockets;
	number_of_pockets = 0;
	
	acceptClient(lis, s);
	receiveInitData(number_of_pockets, s, structure_to_write); 

	clock_gettime(CLOCK_REALTIME, &time1);

	for(int i=0; i<number_of_pockets; i++) { //cyckle of reading of datapockets
	   bytes_read = recv(s,(void *)&structure_to_write, sizeof(structure_to_write), 0);
				
		if (bytes_read <= 0) {	
			printf("End of Reading!\n");
		} else {
			count_of_pockets = count_of_pockets+1;
		}
	}
	clock_gettime(CLOCK_REALTIME, &time2);
	hope =  (time2.tv_sec * 1000 + time2.tv_nsec / 1000000) - (time1.tv_sec * 1000 + time1.tv_nsec / 1000000);
	
	printStatistic(hope, number_of_pockets, count_of_pockets);
	
	count_of_pockets = 0;
	close(s);
//	exit(0);
//} 
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
