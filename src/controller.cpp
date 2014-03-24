#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
//#include "concrete_controller.h" 

//Structure wich must fuck the iperf out
struct conf
{
	char* port;
	//char ip[];	
	int server_mode; //1-on 0-off
	int udp_mode; //1-on 0-off
	int loss; //socket what was fuc*ed in process
	char* count; //count of pockets
	char* size; //size of each(?) pocket
};
/*
//---Controller constructor
ConcreteController::ConcreteController() {
	printf("Controller ready\n");
}


//---Destructor
ConcreteController::~ConcreteController() {
	printf("Controller died\n");
}
*/
//---Main function of controller
/*
	This function check parameters, make configuration struct, 
	Create and configure model 
*/

int main (int argc, char **argv) {
    int c;
    int digit_optind = 0;
    conf stats;

	stats.udp_mode = 0;
	stats.server_mode = 0;
	//stats.ip = "127.0.0.1";
	stats.port =stats.port + '3409';
	printf("%d\n",stats.port);
    while (1) {
         int this_option_optind = optind ? optind : 1;
	 int option_index = 0;

        c = getopt (argc, argv, "p::i::sulc:b:?");
        if (c == -1)
            break;

        switch (c) {
        case 'p':
            printf ("Port was : `%d'\n", stats.port);
	stats.port = optarg;
	printf ("Port now :%s\n",optarg);
            break;

        case 'i':
            printf ("IP:  `%s'\n", optarg);
            break;

        case 's':
            printf ("Server mode: on! \n");
		stats.server_mode = 1;            
		break;

        case 'u':
            printf ("UDP mode: on! \n");
            stats.udp_mode = 1;
		break;

	case 'l':
            printf ("Pocket casualties are going to be counted\n");    
	break;

	 case 'b':
            printf ("Pocket size:  `%s'\n", optarg);
            stats.size = optarg;
		break;
        
        case 'c':
            printf ("The number of pockets is:  `%s'\n", optarg);
            stats.count = optarg;
		break;

	case '?':
	printf("Unknown key. Please, be sure, you know what you do\n");
            break;

        default:
	break;
           
        }
    }

    if (optind < argc) {
        printf ("элементы ARGV, не параметры: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    exit (0);
}

/*
//---Return type of model, that we will use
Model *ConcreteController::get_model() {
	printf("Controller: i send model\n");
	return NULL;
} */
