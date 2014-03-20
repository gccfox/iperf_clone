#pragma once
#include <unistd.h>
#include <stdlib.h>
#include "model.h"
/*#ifndef MODEL_H
	#include "model.h"
#endif*/

/*
*	This model characterize Udp client
*	mode
*/
class UdpClientModel : public Model {
	int 				client_socket;
	struct sockaddr_in	client_socket_config;

	public:
		UdpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);

	private:
		void initSocket();
		int createSocket();
		void configureSocket();
		void startClient();
};
