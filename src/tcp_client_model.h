#pragma once
#include "model.h"
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

/*
*	This model characterize tcp client
*	mode
*/
class TcpClientModel : public Model {
	int port;
	int packets_count;
	char* host_ip_address;

   	private:
        int createConnection(int &sock);
        int sendInformation(int sockfd);
        void printStatistic(int sent);

    public:
		TcpClientModel();
        void defaultConfigure();
		void run();
		void configure(struct model_configuration_struct *);
};
