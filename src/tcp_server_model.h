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
		//virtual void run();
		virtual void configure(struct configure_struct *);
		virtual void TcpSocketCreating(int &lis, struct sockaddr_in add); 
		virtual void TcpAccepting(int &lis,int &s, clock_t ti1, clock_t ti2, struct msg b);
};
