#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize Udp client
*	mode
*/
class UdpClientModel : public Model {
	public:
		UdpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
