//---Specify model configuration options, settin by controller
struct model_options {
    //char ip[];
    int server_mode; //1-on 0-off
    int loss; //socket what was fuc*ed in process
    int count; //count of pockets
    int size; //size of each(?) pocket
	int model_type;//udp=1, tcp=0
	int port;
	char* ip;
};

