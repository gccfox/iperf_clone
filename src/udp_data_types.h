#pragma once
//---Contains main connection info
struct connection_init_data {
	int 	packet_count;
	char	client_name[CLIENT_NAME_SIZE];
};

//---Contains system data
struct connection_terminate_data {
	int termination_code;
};


//---Udp apcket struct
struct udp_data_packet {
	char	flood_data[UDP_FLOOD_DATA_SIZE];
};
