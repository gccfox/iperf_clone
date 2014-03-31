#pragma once
#include "model.h"
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

/*
*	This model characterize tcp client
*	mode
*/
class TcpClientModel : public Model {
	public:
		struct timespec		start_receive_data_time, end_receive_data_time;
		TcpClientModel();
		void run();
		void configure(struct configure_struct *);
};
