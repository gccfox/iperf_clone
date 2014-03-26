#pragma once
#include "info_types.h"
#define MODEL_H		1

//---Abstract interface for all models
class Model {
	virtual void run() {};
	virtual void configure(struct configure_struct *) {};
};
