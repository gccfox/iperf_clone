#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "controller.h"
#include "struct.h"
#include "tcp_client_model.h"
#include "udp_client_model.h"
#include "tcp_server_model.h"
#include "udp_server_model.h"



/*---We have one controller. 
	Main function of controller - parse options, 
	configure and run models
*/
class ConcreteController : public Controller { 

	public:
		ConcreteController();
		~ConcreteController();
		void run(int argc, char **argv);
		Model *chooseModelType(struct model_creating_struct *mod);
		bool checkTcpServer(struct model_creating_struct *mo);
		bool checkTcpClient(struct model_creating_struct *mo);
		bool checkUdpServer(struct model_creating_struct *mo);
		bool checkUdpClient(struct model_creating_struct *mo);	
		void parsingArguments(int argc, char **argv, model_creating_struct *mo);	
		void printHelpPage();
		void initModelStructure(struct model_creating_struct *mo);
		void initDefaultModelStructure(struct model_creating_struct *mo);
			//Model *get_model(struct model_creating_struct *mod);
};
