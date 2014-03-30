#pragma once
#include <string.h>
#define MODEL_CLIENT_TCP		0
#define MODEL_SERVER_TCP		1
#define MODEL_CLIENT_UDP		2
#define MODEL_SERVER_UDP		3

#define WORK_MODE_UNDEFINED 	0
#define WORK_MODE_SERVER		1
#define WORK_MODE_CLIENT		2

#define PROTOCOL_UNDEFINED  	0
#define PROTOCOL_UDP			1
#define PROTOCOL_TCP			2

#define DEFAULT_PORT			3409	
#define DEFAULT_SYSTEM_PORT		12300
#define DEFAULT_IP				"127.0.0.1"
#define CLIENT_NAME_SIZE		128
#define UDP_FLOOD_DATA_SIZE		256




//---Specify model configuration options, settin by controller
struct model_configuration_struct{
	int port;
	int system_port;
	int work_mode;
	int protocol;
	char* ip;
	int packets_count;
};



