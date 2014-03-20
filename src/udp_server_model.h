#pragma once
#include "model.h"
/*#ifndef MODEL_H
	#include "model.h"
#endif*/

/*
*	This model characterize Udp Server
*	mode
*/
class UdpServerModel : public Model {

	int 						server_socket;
	struct sockaddr_in			server_socket_config;
	struct configure_struct 	*server_model_config;
	
	public:
		UdpServerModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
	
	private:
		void initSocket();
		int createSocket();
		void configureSocket();
		void bindSocket(int socket, struct sockaddr_in *socket_config);
		void startServer();
};
