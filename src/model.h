#include "info_types.h"
#define MODEL_H		1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
//---Abstract interface for all models
class Model {
  public: 
	virtual void run() {};
	virtual void configure(struct configure_struct *) {};
};
