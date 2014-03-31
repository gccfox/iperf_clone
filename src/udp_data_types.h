#pragma once
#define DEFAULT_PACKET_COUNT		100000
#define DEFAULT_UDP_CLIENT_NAME		"Dexter"

//#define UDP_PACKET_SEND_DELAY_MS		1
//---Contains main connection info
struct connection_init_data {
	int 	packets_count;
	char	client_name[CLIENT_NAME_SIZE];
};

//---Contains system data
struct connection_terminate_data {
	int termination_code;
};


//---Udp apcket struct
struct udp_data_packet {
	char	flood_data[UDP_FLOOD_DATA_SIZE];
    int     number;
};
