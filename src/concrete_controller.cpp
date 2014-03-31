#include "concrete_controller.h" 


/**
  *		Check arguments comapt with UDP server
  */
bool ConcreteController::checkUdpServer(struct model_configuration_struct *mo)
{
//	printf("Checking for Udp Server Model!\n");
	if ((mo->work_mode == WORK_MODE_SERVER) && (mo->protocol == PROTOCOL_UDP) ) {
//		printf("UDP server accepted!\n");
		return true;
	}

//	printf("UDP server not accepted!\n"); 
	return false;
}



/**
  *		Check arguments comapt with UDP client
  */
bool ConcreteController::checkUdpClient(struct model_configuration_struct *mo)
{
//	printf("Checking for Udp Client Model!\n");
	if ((mo->work_mode == WORK_MODE_CLIENT) && (mo->protocol == PROTOCOL_UDP) ) {
		//printf("UDP client accepted!\n");
		return true;
	}

//	printf("UDP client not accepted!\n"); 
	return false; 
}



/**
  *		Check arguments comapt with TCP client
  */
bool ConcreteController::checkTcpClient(struct model_configuration_struct *mo)
{
//	printf("Checking for Tcp Client Model!\n");
	if ((mo->work_mode == WORK_MODE_CLIENT) && (mo->protocol == PROTOCOL_TCP) ) {
//		printf("TCP client accepted!\n");
		return true;
	}

//	printf("TCP client not accepted!\n");
	return false;
}



/**
  *		Check arguments comapt with TCP server
  */
bool ConcreteController::checkTcpServer(struct model_configuration_struct *mo)
{
	if ((mo->work_mode == WORK_MODE_SERVER) && (mo->protocol == PROTOCOL_TCP) ) {
//		printf("TCP server accepted!\n");
		return true;
	}

//	printf("TCP server not accepted!\n"); 
	return false; 
}



/**
  *		Return model, wich user wants
  */
Model* ConcreteController::chooseModelType(struct model_configuration_struct *mod){
	Model* result = NULL;

//	printf("Thinking about model\n");

	if (checkTcpServer(mod)) {
		result = new TcpServerModel();
		return result;
	}

	if (checkUdpServer(mod)) {
		result = new UdpServerModel();
		return result;
	}

	if (checkTcpClient(mod)){
		result = new TcpClientModel();
		return result;
	}

	if (checkUdpClient(mod)){
		result = new UdpClientModel();
		return result;
	}

	return result;
}



//Constructor
ConcreteController::ConcreteController() {
	//printf("Controller ready\n");
	set_port_flag = false;
	set_system_port_flag = false;
	set_ip_flag = false;
	set_packets_count_flag = false;
	set_protocol_flag = false;
	set_working_mode_flag = false;
	set_loss_measurement_flag = false;
	set_packet_size_flag = false;
}



//---Destructor
ConcreteController::~ConcreteController() {
	printf("Controller died\n");
}



/**
  *		Print help page on screen
  *
  */
void ConcreteController::printHelpPage() {
	printf("Usage iperf_clone [-c|-s] options\n\n");
	printf("Client\\Server specific:\n");
	printf("  -p,  --port  #  	     Determine port. Should be integer in range 1001 and 65536\n");
	printf("  -j,  --system-port  #      Determine syncronization port. Should be integer in range 1001 and 65536. UDP specific\n");
	printf("  -u,  --udp 		     Use UDP protocol\n");
	printf("  -t,  --tcp 		     Use TCP protocol\n\n");

	printf("Server specific:\n");
	printf("  -s,  --server 	     Run as server. Default client mode.\n\n"); 

	printf("Client specific:\n");
	printf("  -i,  --ip  <host>          Determine IP of server.\n");
	printf("  -c,  --packets-count  #    Determine packets count, less than 1kk\n");
	printf("  -b,  --packet-size  #      Determine packet size, in bytes, less than 1Kb\n");
	printf("  -l,  --loss-measurement #  Enables loss measurement. UDP specific\n\n");

	printf("Miscellaneous:\n");
	printf("  -h,  --help                Show this page\n\n");
	printf("Report bugs undefined_now@sst.com\n");
}



/**
  * 	Function parse arguments from user input
  */
void ConcreteController::parsingArguments(int argc, char **argv, model_configuration_struct *mo){
	int opt;
	int v = 0;
	int digit_optind = 0;
	in_addr ia;
	int option_index = 0;
	int this_option_optind;


    struct option long_options[] = {
            {"port", 1, NULL, 'p'},
            {"system-port", 1, NULL, 'j'},
            {"ip", 1, NULL, 'i'},
            //{"client", 0, NULL, 'c'},
            {"loss-measurement", 0, NULL, 'l'},
			{"packet-size", 1, NULL, 'b'},
			{"packet-count", 1, NULL, 'c'},
            {"server", 0, NULL, 's'},
            {"udp", 0, NULL, 'u'},
			{"tcp", 0, NULL, 't'},
			{"help", 0, NULL, 'h'},
            {0, 0, 0, 0}
        };


	
	while ((opt = getopt_long (argc, argv, "p:j:i:lb:c:suth",long_options, &option_index)) > 0) {

		this_option_optind = optind ? optind : 1; 

        switch (opt) { 

			case 0:
				printf("параметр %s", long_options[option_index].name);
				if(optarg) {
					printf("с аргументом %s\n", optarg);
				}
				break;


			case 'p':
				checkFlagSet(set_port_flag);
				//printf ("Port was : `%d'\n", mo->port);
				if ((mo->port = atoi(optarg)) < 0) {
					printf("Error: port expected int!\n");
					printHelpPage();
					exit(1);
				} else if ((mo->port <= 1000) || (mo->port > 65536)) {
					printf("Error: port should be positive int more that 1000 and less that 65536\n");
					printHelpPage();
					exit(1);
				} 
				//printf ("Set data port:%d\n",mo->port);
				break;


			case 'j':
				checkFlagSet(set_system_port_flag);
				//printf ("System port was : `%d'\n", mo->port);
				if ((mo->system_port = atoi(optarg)) < 0) {
					printf("Error: sytem port expected int!\n");
					printHelpPage();
					exit(1);
				} else if ((mo->system_port <= 1000) || (mo->system_port > 65536)) {
					printf("Error: system port should be positive int more that 1000 and less that 65536\n");
					printHelpPage();
					exit(1);
				} 
				//printf ("Set system port :%d\n",mo->system_port);
				break;



			case 'i':
				checkFlagSet(set_ip_flag);
				//printf ("IP was:  `%s'\n", mo->ip);
				if ((v = inet_aton(optarg,&ia))) {
					mo->ip = optarg;
					printf("IP now: `%s'\n", mo->ip);
				} else {
					printf("Error: IP should be valid!\n");
					printHelpPage();
					exit(0);
				}
				break;


			case 'c':
				checkFlagSet(set_packets_count_flag);

				if ((mo->packets_count = atoi(optarg)) < 0) {
					printf("Error: packets count expected int!\n");
					printHelpPage();
					exit(1);
				} else if ((mo->packets_count <= 0)|| (mo->packets_count > 1000000)) {
					printf("Error: packets count expected non-zero, positive, and less than 1kk\n");
					printHelpPage();
					exit(1);
				}
				//printf("Packets count is %d\n", mo->packets_count);
				break;


			case 'b':
				checkFlagSet(set_packet_size_flag);

				if ((mo->packet_size = atoi(optarg)) < 0) {
					printf("Error: packet size expected int!\n");
					printHelpPage();
					exit(1);
				} else if ((mo->packet_size <= 0)|| (mo->packet_size > 1000)) {
					printf("Error: packet size expected non-zero, positive, and less than 1Kb\n");
					printHelpPage();
					exit(1);
				}
			//	printf("Packets size is %d\n", mo->packet_size);
				break;


			case 's': 
				checkFlagSet(set_working_mode_flag);
				//printf ("Server mode: on! \n");
				mo->work_mode = WORK_MODE_SERVER;
				break;


			case 'u':
				checkFlagSet(set_protocol_flag);
				//printf ("UDP mode: on! \n");
				mo->protocol = PROTOCOL_UDP; 
				break;

			case 't':
				checkFlagSet(set_protocol_flag);
				//printf ("TCP mode: on! \n");
				mo->protocol = PROTOCOL_TCP;
				break;


			case 'l': 
				checkFlagSet(set_loss_measurement_flag); 
				mo->loss_measurement = true;
				//printf("Loss measuerement set on!\n");
				break;

			case 'h':
				printHelpPage();
				exit(0);
				break;

			default:
				//printf("Error: unrecognized key\n");
				printHelpPage();
				exit(0);
		}
	}

    if (optind < argc) {
        printf ("элементы ARGV, не параметры: ");
        while (optind < argc)
        	printf ("%s ", argv[optind++]);
        printf ("\n");
    }

}




/**
  *		*DEBUG* print debug info about model_configuration_struct
  */
void printModelStruct(struct model_configuration_struct* ma) {
	printf("work_mode: %d protocol: %d port: %d\n", ma->work_mode, ma->protocol, ma->port);
	printf("ip: %s\n", ma->ip);
}



/**
  *		Main function of controller
  *		This function check parameters, make configuration struct, 
  *		Create and configure model 
  */
void ConcreteController::run(int argc, char **argv) {
	//printf("All that we see is an all that we think about\n"); 
	model_configuration_struct mod; 
	initModelStructure(&mod);
	//printModelStruct(&mod);
 	parsingArguments(argc, argv,&mod);
	if (!checkConfigStructure(&mod)) {
		printf("Error: contradiction in user options\n");
		printHelpPage();
		exit(0);
	}
//	printModelStruct(&mod);
	model = chooseModelType(&mod);
	model->configure(&mod);
}



/**
  * 	Initialize model struct with default values
  */
void ConcreteController::initModelStructure(struct model_configuration_struct *ma) {
	ma->work_mode = WORK_MODE_CLIENT;
	ma->protocol = PROTOCOL_TCP;
	ma->port = DEFAULT_PORT;
	ma->system_port = DEFAULT_SYSTEM_PORT;
	ma->ip = new char[50];
	strcpy(ma->ip, DEFAULT_IP);
	ma->packets_count = DEFAULT_PACKETS_COUNT;
	ma->packet_size = DEFAULT_PACKET_SIZE;
	ma->loss_measurement = false;
}



/**
  * 	Check setting special option flag. If set show help page and quit
  */
void ConcreteController::checkFlagSet(bool &flag) {
	if (flag) {
		printHelpPage();
		exit(0);
	} else {
		flag = true;
	}
}



/**
  * 	Return created model
  */
Model *ConcreteController::getModel() {
	return model;
}



/**
  * 	Check user input for contradictions
  */
bool ConcreteController::checkConfigStructure(struct model_configuration_struct *ma) {
	if (ma->work_mode == WORK_MODE_SERVER) {
		if (set_packets_count_flag || set_packet_size_flag) {
			return false;
		}

		if (ma->work_mode == WORK_MODE_CLIENT) {
			return false;
		}

		if (strcmp(ma->ip, DEFAULT_IP)) {
			return false;
		}
	}

	if (ma->work_mode == WORK_MODE_CLIENT) {

		if (set_loss_measurement_flag) {
			return false;
		}
	}

	if (ma->protocol == PROTOCOL_TCP) {
		if (ma->loss_measurement) {
			return false;
		}
	} 

	return true;
}
