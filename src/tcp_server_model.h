#pragma once
#ifndef MODEL_H
	#include "model.h"
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

#endif

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
		void acceptTcp(int &lis,int &s, clock_t ti1, clock_t ti2, struct msg b);
};
