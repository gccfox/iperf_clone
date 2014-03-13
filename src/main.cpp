#include <stdlib.h>
#include <stdio.h>
#include "concrete_controller.h"
#include "tcp_client_model.h"
#include "udp_client_model.h"
#include "tcp_server_model.h"
#include "udp_server_model.h"


int main(int argc, char **argv) {
	Controller *controller = new ConcreteController();
	Model *model = new UdpServerModel();
	controller->run(argc, argv);
	printf("Iperf ready\n");
	return 0;
}
