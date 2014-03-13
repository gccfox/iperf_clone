#include "model.h"

//---Interface for all controllers
class Controller {
	public:
		virtual void run(int argc, char **argv) {};
		virtual Model *get_model() {};
};
