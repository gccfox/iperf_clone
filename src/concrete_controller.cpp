//#define _BSD_SOURCE
#include "concrete_controller.h" 


//-----Trying to create Udp Server
bool ConcreteController::checkUdpServer(struct model_configuration_struct *mo)
{
	printf("Checking for Udp Server Model!\n");
	if ((mo->work_mode == WORK_MODE_SERVER) && (mo->protocol == PROTOCOL_UDP) ) {
		printf("UDP server accepted!\n");
		return true;
	}

	printf("UDP server not accepted!\n"); 
	return false;
}



//-----Trying to create Udp Client
bool ConcreteController::checkUdpClient(struct model_configuration_struct *mo)
{
	printf("Checking for Udp Client Model!\n");
	if ((mo->work_mode == WORK_MODE_CLIENT) && (mo->protocol == PROTOCOL_UDP) ) {
		printf("UDP client accepted!\n");
		return true;
	}

	printf("UDP client not accepted!\n"); 
	return false; 
}



//-----Trying to create Tcp Client
bool ConcreteController::checkTcpClient(struct model_configuration_struct *mo)
{
	printf("Checking for Tcp Client Model!\n");
	if ((mo->work_mode == WORK_MODE_CLIENT) && (mo->protocol == PROTOCOL_TCP) ) {
		printf("TCP client accepted!\n");
		return true;
	}

	printf("TCP client not accepted!\n");
	return false;
}



//-----Trying to create Tcp Server	
bool ConcreteController::checkTcpServer(struct model_configuration_struct *mo)
{
	if ((mo->work_mode == WORK_MODE_SERVER) && (mo->protocol == PROTOCOL_TCP) ) {
		printf("TCP server accepted!\n");
		return true;
	}

	printf("TCP server not accepted!\n"); 
	return false; 
}



//----Creating Model
Model* ConcreteController::chooseModelType(struct model_configuration_struct *mod){
	Model* result = NULL;

	printf("Thinking about model\n");

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
	printf("Controller ready\n");
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
	printf("  -p,  --port  #  	  Determine port. Should be integer in range 1001 and 65536\n");
	printf("  -u,  --udp 		  Use UDP protocol\n");
	printf("  -t,  --tcp 		  Use TCP protocol\n\n");

	printf("Server specific:\n");
	printf("  -s,  --server 	  Run as server\n\n"); 

	printf("Client specific:\n");
	printf("  -i,  --ip  <host>      Determine IP of server.\n");
	printf("  -c,  --client  	  Run as client\n");
	printf("  -l,  --packets-count  # Determine count of packets\n\n");

	printf("Miscellaneous:\n");
	printf("  -h,  --help Show this page\n\n");
	printf("Report bugs undefined_now@sst.com\n");
}



//----Function to parse the string of arguments
void ConcreteController::parsingArguments(int argc, char **argv, model_configuration_struct *mo){
	int opt;
	int v = 0;
	int digit_optind = 0;
	in_addr ia;
	int option_index = 0;
	int this_option_optind;

	bool set_port_flag = false;
	bool set_ip_flag = false;
	bool set_packets_count_flag = false;
	bool set_protocol_flag = false;
	bool set_working_mode_flag = false;

    struct option long_options[] = {
            {"port", 1, NULL, 'p'},
            {"ip", 1, NULL, 'i'},
            {"client", 0, NULL, 'c'},
            {"length", 1, NULL, 'l'},
            {"server", 0, NULL, 's'},
            {"udp", 0, NULL, 'u'},
			{"tcp", 0, NULL, 't'},
			{"help", 0, NULL, 'h'},
            {0, 0, 0, 0}
        };


	
	while ((opt = getopt_long (argc, argv, "p:i:csutl:h",long_options, &option_index)) > 0) {

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
				printf ("Port was : `%d'\n", mo->port);
				if ((mo->port = atoi(optarg)) < 0) {
					printf("Error: poert expected int!\n");
					exit(1);
				} else if ((mo->port <= 1000) || (mo->port > 65536)) {
					printf("Error: port should be positive int more that 1000 and less that 65536\n");
					exit(1);
				} 
				printf ("Port now :%d\n",mo->port);
				break;


			case 'i':
				checkFlagSet(set_ip_flag);
				printf ("IP was:  `%s'\n", mo->ip);
				if ((v = inet_aton(optarg,&ia))) {
					mo->ip = optarg;
					printf("IP now: `%s'\n", mo->ip);
				} else {
					printf("Error: IP should be valid!\n");
					exit(0);
				}
				break;


			case 'c':
				checkFlagSet(set_working_mode_flag);
				printf("Client mode on\n");
				mo->work_mode = WORK_MODE_CLIENT;
				break;


			case 's': 
				checkFlagSet(set_working_mode_flag);
				printf ("Server mode: on! \n");
				mo->work_mode = WORK_MODE_SERVER;
				break;


			case 'u':
				checkFlagSet(set_protocol_flag);
				printf ("UDP mode: on! \n");
				mo->protocol = PROTOCOL_UDP; 
				break;

			case 't':
				checkFlagSet(set_protocol_flag);
				printf ("TCP mode: on! \n");
				mo->protocol = PROTOCOL_TCP;
				break;


			case 'l': 
				checkFlagSet(set_packets_count_flag); 
				int tmp;
				if ((tmp = atoi(optarg)) < 0) {
					printf("Error: number of packets should be int!\n");
					exit(1);
				} else if (tmp <= 0) {
					printf("Error: number of packets should be positive, non-zero!\n");
					exit(1);
				}

				mo->packets_count = tmp;
				printf ("Length is set up to %d packets\n", mo->packets_count);
				break;

			case 'h':
				printHelpPage();
				exit(0);
				break;

			default:
				printf("Unrecognized key %c %i \n", opt, opt);
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



//---Main function of controller
/*
	This function check parameters, make configuration struct, 
	Create and configure model 
*/
void ConcreteController::run(int argc, char **argv) {
	printf("All that we see is an all that we think about\n"); 
	model_configuration_struct mod; 
	initModelStructure(&mod);
	//printModelStruct(&mod);
 	parsingArguments(argc, argv,&mod);
//	printModelStruct(&mod);
	model = chooseModelType(&mod);
	model->configure(&mod);
}


/**
  * 	Initialize model struct with default values
  */
void ConcreteController::initModelStructure(struct model_configuration_struct *ma) {
	ma->work_mode = WORK_MODE_SERVER;
	ma->protocol = PROTOCOL_UDP;
	ma->port = DEFAULT_PORT;
	ma->ip = new char[50];
	strcpy(ma->ip, DEFAULT_IP);
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
