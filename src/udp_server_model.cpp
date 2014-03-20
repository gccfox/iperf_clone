#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udp_server_model.h"

/*
*	Just a constructor 
*/
UdpServerModel::UdpServerModel() {
	printf("Udp Server created!\n");
}


/*
*	Main function of Udp Server
*	Place your code here
*/
void UdpServerModel::run() {
	initDataSocket();	
//	startServer();
	receiveInitPacket();
	receiveDataStream();
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void UdpServerModel::configure(struct configure_struct *configuration_struct) {
	if (configuration_struct == NULL) {
		printf("UDP_server: model config error!\n");
		exit(1);
	}

}



/*
*	Create and configure socket with parameters from
*	struct configure_struct
*/

void UdpServerModel::initDataSocket() {
	flood_data_socket = createDataSocket();
	configureDataSocket();
	bindDataSocket(flood_data_socket, &flood_data_socket_config); 
}


/*
*	Create and configure system socket with parameters from
*	struct configure_struct system_data_config
*/

void UdpServerModel::initSystemDataSocket() {
	system_data_socket = createSystemDataSocket();
	configureSystemDataSocket();
	bindSystemDataSocket(system_data_socket, &system_data_socket_config); 
}


/*
* 	Creates internet socket
*
*/
int UdpServerModel::createDataSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("UDP_server: data socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}


/*
* 	Creates internet system TCP socket
*
*/
int UdpServerModel::createSystemDataSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("UDP_server: system socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}


/*
*	Fills the config structure
*
*/
void UdpServerModel::configureDataSocket() {
	memset(&flood_data_socket_config, 0, sizeof(flood_data_socket_config));
	flood_data_socket_config.sin_family = AF_INET;
	flood_data_socket_config.sin_port = htons(DEFAULT_PORT);
	flood_data_socket_config.sin_addr.s_addr = htonl(INADDR_ANY);
}


/*
*	Fills the system socket config structure(TCP)
*
*/
void UdpServerModel::configureSystemDataSocket() {
	memset(&system_data_socket_config, 0, sizeof(system_data_socket_config));
	system_data_socket_config.sin_family = AF_INET;
	system_data_socket_config.sin_port = htons(DEFAULT_SYSTEM_PORT);
	system_data_socket_config.sin_addr.s_addr = htonl(INADDR_ANY);
}


/*
*	Binds socket
*/
void UdpServerModel::bindDataSocket(int socket, struct sockaddr_in *socket_config) {
	if (bind(socket, (struct sockaddr *)socket_config, sizeof(*socket_config)) < 0) {
		printf("UDP_server: socket bind error! Error code %d\n", errno);
		exit(2);
	}
}


/*
*	Connect system socket
*/
void UdpServerModel::bindSystemDataSocket(int socket, struct sockaddr_in *socket_config) {
	if (bind(socket, (struct sockaddr *)socket_config, sizeof(*socket_config)) < 0) {
		printf("UDP_server: socket bind error! Error code %d\n", errno);
		exit(2);
	}
}



/*
*	Starts listening in another thread for system messages
*
*/
void UdpServerModel::startSystemDataServer() {
	printf("System data server on air..\n");
}


/*
*	Start packet processing
*
*/
void UdpServerModel::startDataServer() {
	/*char 	message_buffer[UDP_PACKET_SIZE];
	printf("UDP_server: started..\n"); 

	memset(message_buffer, 0, sizeof(char) * UDP_PACKET_SIZE);
	if (recvfrom(flood_data_socket, message_buffer, UDP_PACKET_SIZE, 0, NULL, NULL) < 0) {
		printf("UDP_server: message receive error! Error code %d\n", errno);
		exit(3);
	}

	printf("Udp_server: catched message: '%s'\n", message_buffer);*/
	printf("UDP_server: started..\n"); 
	initDataSocket();	
	receiveInitPacket();
	receiveDataStream(); 
}


/*
*	Receive initialization packet
*
*/
void UdpServerModel::receiveInitPacket() {
	printf("UDP_server: waiting for init packet..\n"); 

	memset(&init_data_packet, 0, sizeof(connection_init_data));
	if (recvfrom(flood_data_socket, (void *)&init_data_packet, sizeof(connection_init_data),
			0, NULL, NULL) < 0) {
		printf("UDP_server: message receive error! Error code %d\n", errno);
		exit(3);
	}

	printf("Udp_server: get init packet packet count: %d client name: %s\n", init_data_packet.packet_count, init_data_packet.client_name);

	//---Save expected count of stream
	packet_count = init_data_packet.packet_count;
}


/*
*	Receive udp data packet
*/
void UdpServerModel::receiveDataPacket() {
	struct udp_data_packet		packet;	
	struct sockaddr_in			packet_info;
	socklen_t					packet_info_length = sizeof(struct sockaddr_in);

	if (recvfrom(flood_data_socket, (void *)&packet, sizeof(struct udp_data_packet),
			0, (struct sockaddr *)&packet_info, &packet_info_length) < 0) {
		printf("UDP_server: message receive error! Error code %d\n", errno);
		exit(3);
	}
	printf("UDP_server: data received: IP %s\n", inet_ntoa(packet_info.sin_addr));
}
		

/*
*	Receives all data stream
*
*/
void UdpServerModel::receiveDataStream() {
	printf("UDP_server: start receiving data stream, expected %d packets\n", packet_count);

	for (int i = 0; i < packet_count; i++) {
		receiveDataPacket();
	}
	printf("UDP_server: end of data stream\n");
}
