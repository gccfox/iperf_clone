#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
//#include <cstring>
#include "struct.h"
#pragma once
using namespace std;
int fill_default(model &m);
int fill_default(model &m)
{
	m.server_mode = 0;
	m.loss = 0;
	m.count = 0;
	m.size = 0;
	m.model = 0;
	m.port = 3409;
	m.ip = "127.0.0.1";
 //	strcpy(m.ip,s.c_str());
	return 0;
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
    model mo;
	int c;
    int digit_optind = 0;

	fill_default(mo);
	//printf("%d\n",stats.port);
	printf("%d\n",mo.port);
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
printf("%d\n",mo.port);

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
	printf ("Port now :%d\n",mo.port);
            break;

        case 'i':
            printf ("IP:  `%s'\n", optarg);
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

    exit (0);
}

/*
//---Return type of model, that we will use
Model *ConcreteController::get_model() {
	printf("Controller: i send model\n");
	return NULL;
} */
