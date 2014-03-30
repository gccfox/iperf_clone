#include <stdlib.h>
#include <stdio.h>
#include "tcp_client_model.h"
#include "udp_client_model.h"
#include "tcp_server_model.h"
#include "udp_server_model.h"
#include "concrete_controller.h"
#include "error_view.h"
using namespace std;

int main (int argc, char **argv) {

//Controller test
	Model *model;
	ConcreteController *controller = new ConcreteController();
	controller->run(argc, argv);
	model = controller->getModel();
	model->run();



/*
//	View test
*	View *err_view = new ErrorView();
*	err_view->print((void *)"wrong argument");
*/


//	Molient/Server
/*	Model *model = new UdpServerModel(); 
	model->run();*/

	printf("Iperf ready\n");
	return 0;
}
