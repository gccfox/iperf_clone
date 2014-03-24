#include <stdlib.h>
#include <stdio.h>
#include "controller.h"

/*---We have one controller. 
	Main function of controller - parse options, 
	configure and run models
*/
class ConcreteController : public Controller { 

	public:
		ConcreteController();
		~ConcreteController();
		void run(int argc, char **argv);
		Model *get_model();
		struct conf{};

};
