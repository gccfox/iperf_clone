#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "controller.h"
#include "struct.h"


/*---We have one controller. 
	Main function of controller - parse options, 
	configure and run models
*/
class ConcreteController : public Controller { 

	public:
		ConcreteController();
		~ConcreteController();
		void run(int argc, char **argv);
		Model *makeDecision(struct model_creating_struct *mod);
		int checkTcpServer(struct model_creating_struct *mod);
		int checkTcpClient(struct model_creating_struct *mod);
		int checkUdpServer(struct model_creating_struct *mod);
		int checkUdpClient(struct model_creating_struct *mod);	
		void parsingArguments(int argc, char **argv, model_creating_struct *mo);	
		//Model *get_model(struct model_creating_struct *mod);
};
