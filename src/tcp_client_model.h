#ifndef MODEL_H
	#include "model.h"
#endif

/*
*	This model characterize tcp client
*	mode
*/
class TcpClientModel : public Model {
    private:
        configure_struct conf;
        int createConnection(int &sock);
        int sendInformation(int sockfd);
        void printStatistic(int sent);
    public:
		TcpClientModel();
                void defaultConfigure();
		virtual void run();
		virtual void configure(struct configure_struct *);
};
