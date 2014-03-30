#include "udp_server_model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>


/**
  *     Handler, that kill current thread used to kill UDP data
  *     receiving thread, while time out, due to errors(maybe)
  */
void killingUdpThreadHandler(int) {
    printf("UDP_server: killing UDP thread\n");
    pthread_exit(NULL);
}



/**
  *		Just a constructor 
  */
UdpServerModel::UdpServerModel() {
	printf("Udp Server created!\n");
    packets_expected = 0;
    packets_received = 0;
    receive_time_sec = 0;
    //start_receive_time_sec = end_receive_time_sec = 0;
	end_udp_data_flag = 0;
	port = DEFAULT_PORT;
	system_port = DEFAULT_SYSTEM_PORT;
}



/**
  *		Main function of Udp Server
  *		Place your code here
  */
void UdpServerModel::run() {
    int*    udp_thread_result = new int;
	
	//---Init sockets for data and control messages
	initDataSocket();	

	//---Wait for connection
	prepareControlDataSocket();
	safeReceiveInitPacket(); 


	//---Snap start time
	getCurrentTime(&start_receive_data_time);

    //---Start stread for udp data
    startDataReceivingThread();

    //---Get term packet and set finalizing flag 
	safeReceiveTerminationPacket();
	end_udp_data_flag = 1;
		
    //pthread_cancel(flood_data_thread);
    pthread_join(flood_data_thread, (void **)udp_thread_result);

	//---Snap end time
	getCurrentTime(&end_receive_data_time);

    printStatistic();
    freeResources();
}



/**
  *		This function provides pre configuration
  *		Do not touch now
  */
void UdpServerModel::configure(struct model_configuration_struct *configuration_struct) {
	if (configuration_struct == NULL) {
		printf("UDP_server: model config error!\n");
		exit(1);
	}
	printf("UDP_server: configuration!\n"); 
	port = configuration_struct->port; 
	system_port = configuration_struct->system_port;
}



/**
  *		Create and configure socket with parameters from
  *		struct configure_struct
  */ 
void UdpServerModel::initDataSocket() {
	flood_data_socket = createDataSocket();
	configureDataSocket();
	bindSocket(flood_data_socket, &flood_data_socket_config); 
}



/**
  *		Create and configure system socket with parameters from
  *		struct configure_struct system_data_config
  */ 
void UdpServerModel::initControlDataSocket() {
	control_data_socket = createControlDataSocket();
	configureControlDataSocket();
	bindSocket(control_data_socket, &control_data_socket_config); 
}



/**
  * 	Creates internet socket
  *
  */
int UdpServerModel::createDataSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("UDP_server: data socket creation error! Error code: %d\n", errno);
		exit(1);
	}
    fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	return socket_fd;
}



/**
  * 	Creates TCP socket for control data(system messages)
  */
int UdpServerModel::createControlDataSocket() {
	int socket_fd;	

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("UDP_server: system socket creation error! Error code: %d\n", errno);
		exit(1);
	}
	return socket_fd;
}



/**
  *		Fills the config structure
  */
void UdpServerModel::configureDataSocket() {
	memset(&flood_data_socket_config, 0, sizeof(flood_data_socket_config));
	flood_data_socket_config.sin_family = AF_INET;
	flood_data_socket_config.sin_port = htons(port);
	flood_data_socket_config.sin_addr.s_addr = htonl(INADDR_ANY);
}



/**
  *		Fills the system socket config structure(TCP)
  *
  */
void UdpServerModel::configureControlDataSocket() {
	memset(&control_data_socket_config, 0, sizeof(control_data_socket_config));
	control_data_socket_config.sin_family = AF_INET;
	control_data_socket_config.sin_port = htons(system_port);
	control_data_socket_config.sin_addr.s_addr = htonl(INADDR_ANY);
}


/**
  *		Binds socket(any type)
  */
void UdpServerModel::bindSocket(int socket, struct sockaddr_in *socket_config) {
	if (bind(socket, (struct sockaddr *)socket_config, sizeof(*socket_config)) < 0) {
		printf("UDP_server: socket bind error! Error code %d\n", errno);
		exit(2);
	}
}


/**
  *		Starts listening in another thread for system messages
  */
void UdpServerModel::prepareControlDataSocket() {
	printf("System data server on air..\n");
	initControlDataSocket();
	listen(control_data_socket, SYSTEM_SERVER_BACKLOG_SIZE);
}



/**
  *		Start packet processing, this method is static
  * 	just for C threads compatibility. UNSAFE
  *		@obj    is and pointer to "this"
  */
void *UdpServerModel::startDataReceiving(void *obj) {
    UdpServerModel *this_object = static_cast<UdpServerModel *>(obj);


    //---Configure timeout killing timer
    this_object->configureTimer();

	printf("UDP_server: udp serving in thread started..\n"); 
	this_object->receiveDataStream(); 

    return NULL;
}



/**
  *     Creates THREAD, that will listen UDP socket to
  *     receive data
  */
void UdpServerModel::startDataReceivingThread() {
    int thread_err_code = 0;

	//---Create data thread
    if (thread_err_code = pthread_create(&flood_data_thread, NULL, startDataReceiving, static_cast<void *>(this))) {
            printf("UDP_server: flood receiving thread: creation error!%d\n", errno);
            exit(1);
    }
    
}



/**
  *		Receive initialization packet with UDP protocol
  *						 *DERPRECATED*
  */
void UdpServerModel::receiveInitPacket() {
	printf("UDP_server: *unsafe* waiting for init packet..\n"); 

	memset(&init_data_packet, 0, sizeof(connection_init_data));
	if (recvfrom(flood_data_socket, (void *)&init_data_packet, sizeof(connection_init_data),
			0, NULL, NULL) < 0) {
		printf("UDP_server:: *unsafe* message receive error! Error code %d\n", errno);
		exit(3);
	}

	printf("Udp_server:: *unsafe* get init packet packet count: %d client name: %s\n", init_data_packet.packet_count, init_data_packet.client_name);

	//---Save expected count of stream
	packets_expected = init_data_packet.packet_count;
}



/**
  *		Receives all data stream
  *
  */
void UdpServerModel::receiveDataStream() {
	printf("UDP_server: start receiving data stream, expected %d packets\n", packets_expected); 

	while(true) { 
		//---if end-of-data-stream packet did't come yet
		if (!end_udp_data_flag) {
	        receiveDataPacket();
		} else {
			receiveRemainingData();
			pthread_exit(NULL);
		}

        //---Checks fulfilling of socket
        //select(1, &udp_socket_set, NULL, NULL, &udp_socket_sleep_interval);
        /*if (FD_ISSET(receive_socket, &udp_socket_set)) {
    		receiveDataPacket();
        }*/
		if (packets_received == packets_expected) {
			printf("UDP_server: finalize data processing due to: received all expected packets\n");
			pthread_exit(NULL);
		}
	}
	printf("UDP_server: end of data stream\n");
}



/**
  *		Receives all remaining packets from IP stack
  */
void UdpServerModel::receiveRemainingData() {
	while(receiveDataPacket()) {
		//printf("UDP_server: get dead flag!\n");
	}
}



/**
  *		Receive udp data packet
  */
int UdpServerModel::receiveDataPacket() {
	struct udp_data_packet		packet;	
	struct sockaddr_in			packet_info;
	socklen_t					packet_info_length = sizeof(struct sockaddr_in);
    int                         recv_result = 0;

    recv_result = recvfrom(flood_data_socket, (void *)&packet, sizeof(struct udp_data_packet),
			MSG_WAITALL, (struct sockaddr *)&packet_info, &packet_info_length);

	if (recv_result < 0) {
		//perror("UDP_server: message receive error! Error code ");
		return false;
	}

    if (recv_result > 0) {
        //printf("UDP_server: data received from: IP %s, data: %d\n", inet_ntoa(packet_info.sin_addr), packet.number);
        packets_received++;
		return true;
    }
}
		
		

/**
  *		Receives init packet with TCP protocol
  */
void UdpServerModel::safeReceiveInitPacket() {

	if ((receive_socket = accept(control_data_socket, NULL, NULL)) < 0) {
		printf("UDP_server: system socket: packet socket creation error!%d\n", errno);
		exit(2);
	}

	if (recv(receive_socket, (void *)&init_data_packet, sizeof(struct connection_init_data), 0) < 0) {
		perror("UDP_server: system socket: receive init data error!");
		exit(2);
	}

	//---Save expected count of stream
	packets_expected = init_data_packet.packet_count;
	
	printf("Udp_server: get init packet packet count: %d client name: %s\n", packets_expected, init_data_packet.client_name); 
	printf("UDP_server: started..\n"); 
}



/*
*	Receives termination packet
*/
void UdpServerModel::safeReceiveTerminationPacket() {
	struct connection_terminate_data	terminate_packet;

	printf("UDP_server: waiting for term packet\n");

	//---Receive terminate packet
	if (recv(receive_socket, (void *)&terminate_packet, sizeof(struct connection_terminate_data), 0) < 0) {
		perror("UDP_server: system socket: receive init data error!");
		exit(2);
	}
	
	printf("Udp_server: get termination packet with code %d\n", terminate_packet.termination_code);
}



/**
  *    Prints statistic info
  */
void UdpServerModel::printStatistic() {
	long receive_time_ms;
	double loss_percentage = 1 - packets_received / (double)packets_expected;

	receive_time_ms = getUdpDataProcessingTime();
	//printf("In MS receive time is %d %lli\n", receive_time_ms, receive_time_ms);
	receive_time_sec = receive_time_ms / 1000.0;

	average_speed = packets_received * sizeof(udp_data_packet) / receive_time_sec;

	printf("Data processing time: %.3f\n", receive_time_sec);
    printf("Packets expected: %d, receive: %d\n", packets_expected, packets_received);
	printf("Percentage of loss packets: %.3f\n", loss_percentage);
	printHumanReadableAverageSpeed();
}
    


/**
  *     Free all resources
  */
void UdpServerModel::freeResources() {
    close(receive_socket);
    close(flood_data_socket);
    close(control_data_socket);
}



/**
  *    Configure timer
  */
void UdpServerModel::configureTimer() {
    struct sigaction        sa;
    struct itimerval        timer;
	printf("UDP_server: settin timer!\n");

    //---Set signal handler
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = killingUdpThreadHandler; //--Prove it!
    sigaction(SIGVTALRM, &sa, NULL);

    //---Configure timer
	memset(&timer, 0, sizeof(struct itimerval));
    timer.it_value.tv_sec = UDP_PACKET_WAIT_INTERVAL * packets_expected;
    timer.it_value.tv_sec = 0;
    //timer.it_value.tv_usec = UDP_PACKET_WAIT_INTERVAL * packets_expected;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL)) {
        printf("UDP_server: timer setting error! %d\n");
        exit(2);
    }
} 



/**
  * 	Fills structure with current process on CPU uptime
  */
int UdpServerModel::getCurrentTime(struct timespec *time_struct) {
	memset(time_struct, 0, sizeof(struct timespec));

	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, time_struct)) {
		perror("UDP_server: error getting thread time!");
		return false;
	}
	return true;
}



/**
  * 	Getting time of data processing(in ms)
  */
long UdpServerModel::getUdpDataProcessingTime() {
	long start_ms = start_receive_data_time.tv_sec * 1000 + start_receive_data_time.tv_nsec / 1000000;
	long end_ms = end_receive_data_time.tv_sec * 1000 + end_receive_data_time.tv_nsec / 1000000;
/*	printf("start time: %d %d\n", start_receive_data_time.tv_sec, start_receive_data_time.tv_nsec);
	printf("end time: %d %d\n", end_receive_data_time.tv_sec, end_receive_data_time.tv_nsec);
	printf("res: %d\n", end_ms - start_ms);*/
	return end_ms - start_ms;
}



/**
  *
  */
void UdpServerModel::printHumanReadableAverageSpeed() {
	double kb_speed;
	double mb_speed;
	kb_speed = average_speed / 1024.0;
    mb_speed = kb_speed / 1024.0;

	if (kb_speed < 1024) {
		printf("UDP_server: average speed :%.3FKb\n", kb_speed);
	} else {
		printf("UDP_server: average speed :%.3FMb\n", mb_speed);
	}
}
