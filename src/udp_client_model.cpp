#include "udp_client_model.h"
#include <arpa/inet.h>
#include <stdio.h>

/*
*	Just a constructor 
*/
UdpClientModel::UdpClientModel() {
	printf("Udp client created!\n");
}


/*
*	Main function of Udp client
*	Place your code here
*/
void UdpClientModel::run() {
	initSocket();
	startClient(); 
}



/*
*	This function provides pre configuration
*	Do not touch now
*/
void UdpClientModel::configure(struct configure_struct *configuration_struct) {
	if (configuration_struct == NULL) {
		printf("UDP_Client: model config error!\n");
		exit(1);
	}

}



/*
*	Create and configure socket with parameters from
*	struct configure_struct
*/ 
void UdpClientModel::initSocket() {
	client_socket = createSocket();
	configureSocket();
}


/*
* 	Creates internet socket
*
*/
int UdpClientModel::createSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("UDP_Client: socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}


/*
*	Fills the config structure
*
*/
void UdpClientModel::configureSocket() {
	memset(&client_socket_config, 0, sizeof(client_socket_config));
	client_socket_config.sin_family = AF_INET;
	client_socket_config.sin_port = htons(DEFAULT_PORT);

	if (!(inet_aton(DEFAULT_IP, &client_socket_config.sin_addr))) {
		printf("UDP_client: Error, ivalid IP: error code: %d\n", errno);
		exit(1);
	}
}



/*
*	Start packet processing
*
*/
void UdpClientModel::startClient() {
	char 	message_buffer[UDP_PACKET_SIZE];
	memset(&message_buffer, 0, UDP_PACKET_SIZE);
	printf("Send me!\n");
	scanf("%s", message_buffer);

	if (sendto(client_socket, (void *)message_buffer, strlen(message_buffer), 0,
		(struct sockaddr *)&client_socket_config, sizeof(client_socket_config)) < 0) {
		printf("UDP_client: sending error: error_code: %d\n", errno);
		exit(1);
	}
}
