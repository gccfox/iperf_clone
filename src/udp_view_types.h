#pragma once
/**
  * 	This file contains all structures wanted for Udp view
  * 	Those structures used to transmit information from Model
  */
#define UDP_INFO_MSG_SIZE 			256
#define UDP_ERROR_MSG_SIZE 			256
#define UDP_WARNING_MSG_SIZE 		256
#define	UDP_MODEL_NAME_SIZE			256
#define UDP_SERVER_MODEL			0
#define UDP_CLIENT_MODEL			1


/**
  * 	Contains info data for UDP view
  */
struct udp_info_data {
	char info_msg[UDP_INFO_MSG_SIZE];
};



/**
  * 	Contains error data for UDP view
  */
struct udp_error_data {
	char error_msg[UDP_ERROR_MSG_SIZE];
	char model_name[UDP_MODEL_NAME_SIZE];
	int error_code;

	udp_error_data() {
		memset(error_msg, 0, UDP_ERROR_MSG_SIZE);
		memset(model_name, 0, UDP_MODEL_NAME_SIZE);
		error_code = 0;
	}
};



/**
  * 	Contains warnin data for UDP view
  */
struct udp_warning_data {
	char warning_msg[UDP_WARNING_MSG_SIZE];
};



/**
  * 	Contains statistic data for UDP view
  */
struct udp_statistic_data {
	long packets_expected;
	long packets_received;
	double bandwidth_bytes_per_sec;
	double processing_time_sec;

	udp_statistic_data() {
		packets_expected = packets_received = 0;
		bandwidth_bytes_per_sec = 0.0;
		processing_time_sec = 0.0;
	}
};
