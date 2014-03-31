#pragma once
#include "model.h"
#include "tcp_data_types.h"
#include <ctime>


/*
*	This model characterize tcp Server
*	mode
*/
class TcpServerModel : public Model {
		int port;
	public:
		TcpServerModel();
		virtual void run();
		void configure(struct model_configuration_struct *);
		void createTcpSocket(int &lis, struct sockaddr_in add); 
		void readingTcp(int lis,int &s, struct tcp_data_packet b);
		void receiveInitData(long int &number_of_pockets,int s);
		void acceptClient(int lis, int &s);
		void printSpeed(long time, long int number_of_pockets);
		void printTimeInSec(long time);
		void printNumberOfPockets(long count ,long number);
		void printStatistic(long, long, long);

};
