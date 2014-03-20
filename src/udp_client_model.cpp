#include "udp_client_model.h"
#include <arpa/inet.h>
#include <stdio.h>

/*
*	Just a constructor 
*/
UdpClientModel::UdpClientModel() {
	printf("Udp client created!\n");
	packet_count = DEFAULT_PACKET_COUNT;
}


/*
*	Main function of Udp client
*	Place your code here
*/
void UdpClientModel::run() {
	initSocket();
//	startClient(); 
	sendInitPacket();
	sendDataStream();
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


/*
*	Send init data to server
*/
void UdpClientModel::sendInitPacket() {
	struct connection_init_data *init_packet = formInitPacket();
	printf("UDP_client: sending init packet!\n");

	//---Send packet
	if (sendto(client_socket, (void *)init_packet, sizeof(struct connection_init_data), 0,
		(struct sockaddr *)&client_socket_config, sizeof(client_socket_config)) < 0) {
		printf("UDP_client: init data send error: error_code: %d\n", errno);
		exit(1);
	}
	printf("UDP_client: init packet sent..\n");
}


/*
*	From init packet and
*	return pointer to them
*/
struct connection_init_data* UdpClientModel::formInitPacket() {
	struct connection_init_data *result = new connection_init_data;
	result->packet_count = packet_count;
	memset(result->client_name, 0, sizeof(char) * CLIENT_NAME_SIZE);
	strcpy(result->client_name, DEFAULT_UDP_CLIENT_NAME); 
	return result;
}


/*
*	Starts to flood net by packets
*
*/
void UdpClientModel::sendDataStream() {
	printf("UDP_client: start data stream\n");
	for (int i = 0; i < packet_count; i++) {
		sendDataPacket();
		printf("UDP_client: packet sent..\n");
	}
	printf("UDP_client: end data stream\n");
}


/*
*	Send simple data packet
*/
void UdpClientModel::sendDataPacket() {
	struct udp_data_packet	packet;

	//---Send data
	if (sendto(client_socket, (void *)&packet, sizeof(struct udp_data_packet), 0,
		(struct sockaddr *)&client_socket_config, sizeof(client_socket_config)) < 0) {
		printf("UDP_client: flood packet send error: error_code: %d\n", errno);
		exit(1);
	} 
}
