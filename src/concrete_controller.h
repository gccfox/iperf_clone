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
#include "model_configuration.h"
#include "tcp_client_model.h"
#include "udp_client_model.h"
#include "tcp_server_model.h"
#include "udp_server_model.h"



/*---We have one controller. 
	Main function of controller - parse options, 
	configure and run models
*/
class ConcreteController : public Controller { 

		Model *model;

		bool set_port_flag;
		bool set_system_port_flag;
		bool set_ip_flag;
		bool set_packets_count_flag;
		bool set_protocol_flag;
		bool set_working_mode_flag;
		bool set_loss_measurement_flag;
		bool set_packet_size_flag;

	public:
		ConcreteController();
		~ConcreteController();
		void run(int argc, char **argv);
		Model *getModel();

	private:
		Model *chooseModelType(struct model_configuration_struct *mod);
		bool checkTcpServer(struct model_configuration_struct *mo);
		bool checkTcpClient(struct model_configuration_struct *mo);
		bool checkUdpServer(struct model_configuration_struct *mo);
		bool checkUdpClient(struct model_configuration_struct *mo);	
		void parsingArguments(int argc, char **argv, model_configuration_struct *mo);	
		void printHelpPage();
		void initModelStructure(struct model_configuration_struct *mo);
		void checkFlagSet(bool &flag);
		bool checkConfigStructure(struct model_configuration_struct *ma);
};
