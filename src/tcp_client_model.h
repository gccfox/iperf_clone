#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize tcp client
*	mode
*/
class TcpClientModel : public Model {
	public:
		TcpClientModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
