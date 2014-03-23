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

	//---TCP
	printf("UDP_client: system daemon ready\n");
	initSystemDataSocket();
	initSystemSocketConnection(); 
	safeSendInitPacket();
	//startSystemDataClient();

	//sendInitPacket();
	initDataSocket();
	sendDataStream();

	safeSendTerminationPacket();
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
void UdpClientModel::initDataSocket() {
	data_socket = createDataSocket();
	configureDataSocket();
}


/*
* 	Creates internet socket
*
*/
int UdpClientModel::createDataSocket() {
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
void UdpClientModel::configureDataSocket() {
	memset(&data_socket_config, 0, sizeof(data_socket_config));
	data_socket_config.sin_family = AF_INET;
	data_socket_config.sin_port = htons(DEFAULT_PORT);

	if (!(inet_aton(DEFAULT_IP, &data_socket_config.sin_addr))) {
		printf("UDP_client: Error, ivalid IP: error code: %d\n", errno);
		exit(1);
	}
}


/*
*	Start packet processing !deprecated
*
*/
void UdpClientModel::startDataClient() {
	char 	message_buffer[UDP_PACKET_SIZE];
	memset(&message_buffer, 0, UDP_PACKET_SIZE);
	printf("Send me!\n");
	scanf("%s", message_buffer);

	if (sendto(data_socket, (void *)message_buffer, strlen(message_buffer), 0,
		(struct sockaddr *)&data_socket_config, sizeof(data_socket_config)) < 0) {
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
	if (sendto(data_socket, (void *)init_packet, sizeof(struct connection_init_data), 0,
		(struct sockaddr *)&data_socket_config, sizeof(data_socket_config)) < 0) {
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
		printf("UDP_client: packet [%d] sent..\n", i);
	}
	printf("UDP_client: end data stream\n");
}


/*
*	Send simple data packet
*/
void UdpClientModel::sendDataPacket() {
	struct udp_data_packet	packet;

	//---Send data
	if (sendto(data_socket, (void *)&packet, sizeof(struct udp_data_packet), 0,
		(struct sockaddr *)&data_socket_config, sizeof(data_socket_config)) < 0) {
		printf("UDP_client: flood packet send error: error_code: %d\n", errno);
		exit(1);
	} 
}
		

/*
*	Send init packet with TCP protocol
*/
void UdpClientModel::safeSendInitPacket() {
	struct connection_init_data *init_data_packet = formInitPacket();
	if (send(system_data_socket, (void *)init_data_packet, sizeof(struct connection_init_data), 0) < 0) {
		printf("UDP_client: send system data fault!%d\n", errno);
		exit(2);
	}	
}

/*
*	Connects to TCP system server
*/
void UdpClientModel::initSystemSocketConnection() {
	if (connect(system_data_socket, (struct sockaddr *)&system_data_socket_config, 
		sizeof(struct sockaddr_in)) < 0) {
		printf("UDP_client: system connection error!%d\n", errno);
		exit(2);
	}
}



/*
*	Create and configure system (TCP)socket with parameters from
*	struct configure_struct
*/ 
void UdpClientModel::initSystemDataSocket() {
	system_data_socket = createSystemDataSocket();
	configureSystemDataSocket();
}


/*
* 	Creates internet system socket(TCP)
*
*/
int UdpClientModel::createSystemDataSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("UDP_Client: system socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}


/*
*	Fills the ystem socket (TCP) config structure
*
*/
void UdpClientModel::configureSystemDataSocket() {
	memset(&data_socket_config, 0, sizeof(data_socket_config));
	system_data_socket_config.sin_family = AF_INET;
	system_data_socket_config.sin_port = htons(DEFAULT_SYSTEM_PORT);

	if (!(inet_aton(DEFAULT_IP, &system_data_socket_config.sin_addr))) {
		printf("UDP_client: Error, ivalid IP: error code: %d\n", errno);
		exit(1);
	}
}


/*
*	Start system packet processing
*
*/
void UdpClientModel::startSystemDataClient() {
		printf("UDP_client: system daemon ready\n");
		initSystemDataSocket();
		initSystemSocketConnection(); 
		safeSendInitPacket();
	}


/*
*	Form terminate packet
*/
struct connection_terminate_data* UdpClientModel::formTerminationPacket() {
	struct connection_terminate_data *result = new connection_terminate_data;
	result->termination_code = 707;
	return result;
}

/*
*	Send termination packet
*/
void UdpClientModel::safeSendTerminationPacket() {
	struct connection_terminate_data *term_packet = formTerminationPacket();
	if (send(system_data_socket, (void *)term_packet, sizeof(struct connection_terminate_data), 0) < 0) {
		printf("UDP_client: send system term data fault!%d\n", errno);
		exit(2);
	}	
	printf("UDP_client: sent term packet!\n");
}
