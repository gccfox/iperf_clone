#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize Udp Server
*	mode
*/
class UdpServerModel : public Model {
	public:
		UdpServerModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
