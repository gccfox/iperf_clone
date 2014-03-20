#pragma once
#include <unistd.h>
#include <stdlib.h>
#include "model.h"
/*#ifndef MODEL_H
	#include "model.h"
#endif*/
#define DEFAULT_PACKET_COUNT		120
#define DEFAULT_UDP_CLIENT_NAME		"Dexter"

/*
*	This model characterize Udp client
*	mode
*/
class UdpClientModel : public Model {
	int 						client_socket;
	struct sockaddr_in			client_socket_config;
	int 						packet_count;

	public:
		UdpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);

	private:
		void initSocket();
		int createSocket();
		void configureSocket();
		void startClient();
		void sendInitPacket();
		struct connection_init_data* formInitPacket();
		void sendDataStream();
		void sendDataPacket();
};
