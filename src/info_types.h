#pragma once
#include <string.h>
#define INFO_TYPES_H		1
#define DEFAULT_PORT		7650
#define DEFAULT_SYSTEM_PORT		12300
#define DEFAULT_IP			"127.0.0.1"
#define CLIENT_NAME_SIZE	128
#define UDP_FLOOD_DATA_SIZE	256


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


//---Contains main connection info
struct connection_init_data {
	int 	packet_count;
	char	client_name[CLIENT_NAME_SIZE];
};


//---Udp apcket struct
struct udp_data_packet {
	char	flood_data[UDP_FLOOD_DATA_SIZE];
};
