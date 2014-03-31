#pragma once
#define MODEL_CLIENT_TCP	0
#define MODEL_SERVER_TCP	1
#define MODEL_CLIENT_UDP	2
#define MODEL_SERVER_UDP	3

#define WORK_MODE_UNDEFINED 0
#define WORK_MODE_SERVER	1
#define WORK_MODE_CLIENT	2

#define PROTOCOL_UNDEFINED  0
#define PROTOCOL_UDP		1
#define PROTOCOL_TCP		2

#define DEFAULT_PORT		3409	
#define DEFAULT_IP			"127.0.0.1"


//---Specify model configuration options, settin by controller
struct model_creating_struct{
/*    int loss; //socket what was fuc*ed in process
    int count; //count of pockets
    int size; //size of each(?) pocket
	int model;//udp=1, tcp=0
	char* ip;*/
	int port;
	int work_mode;
	int protocol;
	char* ip;
	int packets_count;
};


