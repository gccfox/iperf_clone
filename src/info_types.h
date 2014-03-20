#pragma once
#include <string.h>
#define INFO_TYPES_H	1
#define DEFAULT_PORT	7650
#define DEFAULT_IP		"127.0.0.1"


//---Specify model configuration options, settin by controller
struct model_options {
	int model_type;
	char *ip_address;
	int port;

	model_options() {
		model_type = 0;
		port = DEFAULT_PORT;
		ip_address = new char[16];
		strcpy(ip_address, DEFAULT_IP);
	}
};

