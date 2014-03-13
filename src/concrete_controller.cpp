#include "concrete_controller.h" 

//---Controller constructor
ConcreteController::ConcreteController() {
	printf("Controller ready\n");
}


//---Destructor
ConcreteController::~ConcreteController() {
	printf("Controller died\n");
}

//---Main function of controller
/*
	This function check parameters, make configuration struct, 
	Create and configure model 
*/
void ConcreteController::run(int argc, char **argv) {
	printf("All that we see is an all that we think about\n");
	for (int i = 0; i < argc; i++) {
		printf("arg[%d] = %s\n", i, (char *)(*(argv + i)));
	}
}


//---Return type of model, that we will use
Model *ConcreteController::get_model() {
	printf("Controller: i send model\n");
	return NULL;
}
