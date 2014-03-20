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
	initSocket();	
	startServer();
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

void UdpServerModel::initSocket() {
	server_socket = createSocket();
	configureSocket();
	bindSocket(server_socket, &server_socket_config); 
}


/*
* 	Creates internet socket
*
*/
int UdpServerModel::createSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("UDP_server: socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}


/*
*	Fills the config structure
*
*/
void UdpServerModel::configureSocket() {
	memset(&server_socket_config, 0, sizeof(server_socket_config));
	server_socket_config.sin_family = AF_INET;
	server_socket_config.sin_port = htons(DEFAULT_PORT);
	server_socket_config.sin_addr.s_addr = htonl(INADDR_ANY);
}



/*
*	Binds socket
*/
void UdpServerModel::bindSocket(int socket, struct sockaddr_in *socket_config) {
	if (bind(socket, (struct sockaddr *)socket_config, sizeof(*socket_config)) < 0) {
		printf("UDP_server: socket bind error! Error code %d\n", errno);
		exit(2);
	}
}


/*
*	Start packet processing
*
*/
void UdpServerModel::startServer() {
	char 	message_buffer[UDP_PACKET_SIZE];
	printf("UDP_server: started..\n"); 

	memset(message_buffer, 0, sizeof(char) * UDP_PACKET_SIZE);
	if (recvfrom(server_socket, message_buffer, UDP_PACKET_SIZE, 0, NULL, NULL) < 0) {
		printf("UDP_server: message receive error! Error code %d\n", errno);
		exit(3);
	}

	printf("Udp_server: catched message: '%s'\n", message_buffer);
}
