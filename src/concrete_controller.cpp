//#define _BSD_SOURCE
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include "struct.h"
#include "concrete_controller.h" 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp_client_model.h"
#include "udp_client_model.h"
#include "tcp_server_model.h"
#include "udp_server_model.h"


using namespace std;
//---Controller constructor



int ConcreteController::checkUdpServer(struct model_creating_struct *m)
{
	printf("Checking for Udp Server Model!\n");
        if(m->server_mode == 1)
                if(m->model == 1)
                {
                        printf("Udp server model accepted and created!\n");
			
                       	
			return 1;
                }
                else
                {	
			return 0;
                }
        else
        {
                printf("Checking Udp server Model failed!\n");
                return 0;
        }

}

int ConcreteController::checkUdpClient(struct model_creating_struct *m)
{
	printf("Checking for Udp Client Model!\n");
        if(m->server_mode == 0)
                if(m->model == 1)
                {
                        printf("Udp client model accepted and created!\n");
                        return 1;
                }
                else
                {
			return 0;
                }
        else
        {
                printf("Checking Udp Client Model failed!\n");
                return 0;
        }


}

int ConcreteController::checkTcpClient(struct model_creating_struct *m)
{
	printf("Checking for Tcp Client Model!\n");
        if(m->server_mode == 0)
                if(m->model == 0)
                {
                        printf("Tcp Client model accepted and created!\n");
                        return 1;
                }
                else
                {
			return 0;
                }
        else
        {
                printf("Checking Tcp Client Model failed!\n");
                return 0;
        }

}
	
int ConcreteController::checkTcpServer(struct model_creating_struct *m)
{
	printf("Checking for Tcp Server Model!\n");
	if(m->server_mode == 1)
		if(m->model == 0)
		{
			printf("Tcp Server model accepted and created!\n");
			return 1;
		}
		else
		{
			return 0;
		}
	else
	{
		printf("Checking Tcp Server Model failed!\n");
		return 0;
	}
}

int fill_default(model_creating_struct &m);
int fill_default(model_creating_struct &m)
{
        m.server_mode = 0;
        m.loss = 0;
        m.count = 0;
        m.size = 0;
        m.model = 0;
        m.port = 3409;
        m.ip = "127.0.0.1";
        return 0;
};

Model* ConcreteController::MakeDecision(struct model_creating_struct *mod){
	
printf("Thinking about model\n");

if(!ConcreteController::checkTcpServer(mod)==1)
{
	if(!ConcreteController::checkUdpServer(mod)==1)
		{	if(!ConcreteController::checkTcpClient(mod)==1)
			{
				ConcreteController::checkUdpClient(mod);
				Model *udp_client = new UdpClientModel();
				return udp_client;
			}else{
				Model *tcp_client = new TcpClientModel();
			     	return tcp_client;
				}
		}else{
			Model *udp_server = new UdpServerModel();
		     	return udp_server;
			}
}else{
	Model *tcp_server = new TcpServerModel();
	return tcp_server;
	}

exit(0);
}



//Constructor
ConcreteController::ConcreteController() {
	printf("Controller ready\n");
}


//---Destructor
ConcreteController::~ConcreteController() {
	printf("Controller died\n");
}

//---Main function of controller
/*
	This function check parameters, make configuration struct, 
	Create and configure model 
*/
void ConcreteController::run(int argc, char **argv) {
	printf("All that we see is an all that we think about\n");
	

	model_creating_struct mo;
	int c;
	int v = 0;
    	int digit_optind = 0;
	in_addr ia;
	
	fill_default(mo);

    while (1) {
         int this_option_optind = optind ? optind : 1;
         int option_index = 0;

        static struct option long_options[] = {
            {"port", 2, 0, 'p'},
            {"ip", 2, 0, 'i'},
            {"server", 0, 0, 's'},
            {"udp", 0, 0, 'u'},
            {"loss", 0, 0, 'l'},
            {"count", 1, 0, 'c'},
            {"size", 1, 0, 'b'},
            {0, 0, 0, 0}
        };

	c = getopt_long (argc, argv, "p::i::sulc:b:?",long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
                printf("параметр %s", long_options[option_index].name);
                if(optarg)
                printf("с аргументом %s", optarg);
                printf("\n");
                break;
        case 'p':
            	printf ("Port was : `%d'\n", mo.port);
        	mo.port = atoi(optarg);
		//printf("%d\n");
        	printf ("Port now :%d\n",mo.port);
            	break;

	 case 'i':
            	printf ("IP was:  `%s'\n", mo.ip);
		v=inet_aton(optarg,&ia);
		if(v!=0)
	{
		mo.ip = optarg;
		printf("IP now: `%s'\n", mo.ip);

	}else
	printf("Bad argument fo ip");
            	break;

        case 's':
            	printf ("Server mode: on! \n");
                mo.server_mode = 1;
                break;

        case 'u':
            	printf ("UDP mode: on! \n");
            	mo.model = 1;
		break;
        case 'l':
            	printf ("Pocket casualties are going to be counted\n");
       		break;

	case 'b':
                mo.size = atoi(optarg);
            printf ("Pocket size:  `%s'\n", optarg);
                break;

        case 'c':
            	printf ("The number of pockets is:  `%s'\n", optarg);
		mo.count = atoi(optarg);
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
printf("%d\n", mo.model);
MakeDecision(&mo);
    exit (0);
}


