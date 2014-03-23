#pragma once
#include "model.h"
#include "udp_data_types.h"
/*#ifndef MODEL_H
	#include "model.h"
#endif*/
#define SYSTEM_SERVER_BACKLOG_SIZE		2

/*
*	This model characterize Udp Server
*	mode
*/
class UdpServerModel : public Model {

	int 						flood_data_socket;
	int							system_data_socket;
	int 						packet_count;
	int							receive_socket;
	struct sockaddr_in			flood_data_socket_config;
	struct sockaddr_in			system_data_socket_config;
	struct configure_struct 	*server_model_config;
	struct connection_init_data	init_data_packet;
	
	public:
		UdpServerModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
	
	private:
		void bindSocket(int socket, struct sockaddr_in *socket_config);

		//---Data socket(UDP) methods
		void initDataSocket();
		int createDataSocket();
		void configureDataSocket();
		void startDataServer();
		void receiveInitPacket();
		void receiveDataPacket();
		void receiveDataStream();
		
		//---System socket(TCP) methods
		void initSystemDataSocket();
		int createSystemDataSocket();
		void configureSystemDataSocket();
		void startSystemDataServer();
		void safeReceiveInitPacket();
		void safeReceiveTerminationPacket();
		
};
