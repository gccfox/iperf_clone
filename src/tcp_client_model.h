#pragma once
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize tcp client
*	mode
*/
class TcpClientModel : public Model {
	public:
		struct timespec				start_receive_data_time, end_receive_data_time;
		TcpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
