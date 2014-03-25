#pragma once
#include <unistd.h>
#include <stdlib.h>
#include "model.h"
#include "udp_data_types.h"
#define DEFAULT_PACKET_COUNT		10000
#define DEFAULT_UDP_CLIENT_NAME		"Dexter"

/*
*	This model characterize Udp client
*	mode
*/
class UdpClientModel : public Model {
	int 						data_socket;
	int 						system_data_socket;
	struct sockaddr_in			data_socket_config;
	struct sockaddr_in			system_data_socket_config;
	int 						packet_count;

	public:
		UdpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);

	private:

		//---Data transfer(UDP) methods
		void initDataSocket();
		int createDataSocket();
		void configureDataSocket();
		void startDataClient();
		void sendInitPacket();
		struct connection_init_data* formInitPacket();
		struct connection_terminate_data* formTerminationPacket();
		void sendDataStream();
		void sendDataPacket(int num);

		//---System socket(TCP) methods
		void initSystemDataSocket();
		int createSystemDataSocket();
		void configureSystemDataSocket();
		void bindSystemDataSocket(int socket, struct sockaddr_in *socket_config);
		void startSystemDataClient();
		void safeSendInitPacket();
		void safeSendTerminationPacket();
		void initSystemSocketConnection();

        //---
        void freeResources();
};
