#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
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
	//initDataSocket();	
//	startServer();
//	receiveInitPacket();
//	receiveDataStream();
	printf("System data server on air..\n");
	initSystemDataSocket();
	listen(system_data_socket, SYSTEM_SERVER_BACKLOG_SIZE);

	//---Wait for connection
	safeReceiveInitPacket();

	printf("UDP_server: started..\n"); 
	//receiveDataStream(); 

    //---Start stread for udp data
	initDataSocket();	
    startDataReceiveThread();

    //---Get term packet
	safeReceiveTerminationPacket();
    pthread_cancel(flood_data_thread);
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
	bindSocket(flood_data_socket, &flood_data_socket_config); 
}


/*
*	Create and configure system socket with parameters from
*	struct configure_struct system_data_config
*/

void UdpServerModel::initSystemDataSocket() {
	system_data_socket = createSystemDataSocket();
	configureSystemDataSocket();
	bindSocket(system_data_socket, &system_data_socket_config); 
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
    fcntl(socket_fd, F_SETFL, O_NONBLOCK);
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
void UdpServerModel::bindSocket(int socket, struct sockaddr_in *socket_config) {
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
	initSystemDataSocket();
	listen(system_data_socket, SYSTEM_SERVER_BACKLOG_SIZE);
	safeReceiveInitPacket();
}


/*
*	Start packet processing, this method is static
*   just for C threads compatibility. UNSAFE
*   @obj    is and pointer to "this"
*/
void *UdpServerModel::startDataServer(void *obj) {
    UdpServerModel *this_object = static_cast<UdpServerModel *>(obj);

	printf("UDP_server: udp serving in thread started..\n"); 
	//this_object->initDataSocket();	
	this_object->receiveDataStream(); 
    return NULL;
}


/**
  *     Creates thread, that will listen UDP socket to
  *     receive data
  *
  */
void UdpServerModel::startDataReceiveThread() {
    int thread_err_code = 0;
    if (thread_err_code = pthread_create(&flood_data_thread, NULL, startDataServer, static_cast<void *>(this))) {
            printf("UDP_server: flood receiving thread: creation error!%d\n", errno);
            exit(1);
    }
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
*	Receives all data stream
*
*/
void UdpServerModel::receiveDataStream() {
    //---Create list of socket decriptors
    fd_set              udp_socket_set;
    struct timeval      udp_socket_sleep_interval;
    FD_SET(receive_socket, &udp_socket_set);
    udp_socket_sleep_interval.tv_sec = 0;
    udp_socket_sleep_interval.tv_usec = 400;


	printf("UDP_server: start receiving data stream, expected %d packets\n", packet_count);

	for (int i = 0; i < packet_count; i++) {
		printf("UDP_server: wait for packet %d!\n", i);
        //---Checks fulfilling of socket
        select(1, &udp_socket_set, NULL, NULL, &udp_socket_sleep_interval);
        if (FD_ISSET(receive_socket, &udp_socket_set)) {
    		receiveDataPacket();
        }
	}
	printf("UDP_server: end of data stream\n");
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
*	Receives init packet with TCP protocol
*
*/
void UdpServerModel::safeReceiveInitPacket() {
	//int receive_socket;
	if ((receive_socket = accept(system_data_socket, NULL, NULL)) < 0) {
		printf("UDP_server: system socket: packet socket creation error!%d\n", errno);
		exit(2);
	}

	if (recv(receive_socket, (void *)&init_data_packet, sizeof(struct connection_init_data), 0) < 0) {
		printf("UDP_server: system socket: receive init data error! %d\n", errno);
		exit(2);
	}
	
	printf("Udp_server: get init packet packet count: %d client name: %s\n", init_data_packet.packet_count, init_data_packet.client_name);

	//---Save expected count of stream
	packet_count = init_data_packet.packet_count;
}


/*
*	Receives termination packet
*/
void UdpServerModel::safeReceiveTerminationPacket() {
//	int 								receive_socket;
	struct connection_terminate_data	terminate_packet;

	//---Get socket
/*	if ((receive_socket = accept(system_data_socket, NULL, NULL)) < 0) {
		printf("UDP_server: system socket: packet socket creation error!%d\n", errno);
		exit(2);
	}*/

	printf("UDP_server: catch input socket!\n");

	//---Receive terminate packet
	if (recv(receive_socket, (void *)&terminate_packet, sizeof(struct connection_terminate_data), 0) < 0) {
		printf("UDP_server: system socket: receive init data error! %d\n", errno);
		exit(2);
	}
	
	printf("Udp_server: get termination packet with code %d\n", terminate_packet.termination_code);
}
