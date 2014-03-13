#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize tcp Server
*	mode
*/
class TcpServerModel : public Model {
	public:
		TcpServerModel();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
