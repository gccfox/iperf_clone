#pragma once
#include "model.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <stdio.h>

#define DEFAULT_PORT	3444

/*
*	This model characterize tcp Server
*	mode
*/
class TcpServerModel : public Model {
	public:
		TcpServerModel();
		virtual void run();
		void configure(struct configure_struct *);
		void createTcpSocket(int &lis, struct sockaddr_in add); 
		void readingTcp(int lis,int &s, struct msg b);
		void receiveInitData(long int &number_of_pockets,int &s, struct msg b);
		void acceptClient(int lis, int &s);
		void printSpeed(long time, long int number_of_pockets);
		void printTimeInSec(long time);
		void printNumberOfPockets(long count ,long number);
		void printStatistic(long, long, long);

};
