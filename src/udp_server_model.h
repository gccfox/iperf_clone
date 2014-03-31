#pragma once
#include "model.h"
#include "udp_data_types.h"
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

#define SYSTEM_SERVER_BACKLOG_SIZE	            0
#define UDP_PACKET_WAIT_INTERVAL				1 

/**
  *		This model characterize Udp Server behaviour
  */
class UdpServerModel : public Model {

	int 						flood_data_socket;
	int							control_data_socket;
	long 						packet_count, packets_expected, packets_received;
    double		                receive_time_sec;
	int							receive_socket;
    //clock_t                     start_receive_time, end_receive_time;
	double						average_speed;
	struct timespec				start_receive_data_time, end_receive_data_time;
	struct sockaddr_in			flood_data_socket_config;
	struct sockaddr_in			control_data_socket_config;
	struct configure_struct 	*server_model_config;
	struct connection_init_data	init_data_packet;

	int							end_udp_data_flag;

	//---Inner options
	int							port;
	int							system_port;
	bool						loss_measurement_flag;

    //---data receiver thread 
    pthread_t                   flood_data_thread;
	
	public:
		UdpServerModel();
		virtual void run();
		virtual void configure(struct model_configuration_struct *);
	
	private:
		void bindSocket(int socket, struct sockaddr_in *socket_config);

		//---Data stream(UDP) receiving method for C compatibility this method made static
		static void *startDataReceiving(void *argv);

		//---Data socket(UDP) configuration methods
		void initDataSocket();
		int createDataSocket();
		void configureDataSocket();
        void startDataReceivingThread();

		//---Data socket(UDP) receiving methods
		void receiveInitPacket();
		int receiveDataPacket();
		void receiveDataStream();
		void receiveRemainingData();
		
		//---System socket(TCP) configuraion methods
		void initControlDataSocket();
		int createControlDataSocket();
		void configureControlDataSocket();
		void prepareControlDataSocket();

		//---System socket(TCP) receiving methods
		void safeReceiveInitPacket();
		void safeReceiveTerminationPacket();

        //---Other
        void printStatistic(); 
        void freeResources();
        void configureTimer();
		int getCurrentTime(struct timespec *time_struct);
		long getUdpDataProcessingTime(); //---in ms
		void printHumanReadableAverageSpeed();
};
