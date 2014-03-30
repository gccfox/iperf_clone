#pragma once
/*
 *     This file contains all structures wanted for Udp view
 *     Those structures used to transmit information from Model
 */
#include <string.h>

#define TCP_INFO_MSG_SIZE           256
#define TCP_ERROR_MSG_SIZE          256
#define TCP_WARNING_MSG_SIZE        256
#define TCP_MODEL_NAME_SIZE         256
#define TCP_SERVER_MODEL            0
#define TCP_CLIENT_MODEL            1

/*
 *     Contains info data for UDP view
 */
struct tcp_info_data {
	    char info_msg[TCP_INFO_MSG_SIZE];
};



/*
 *     Contains error data for TCP view
 */
struct tcp_error_data {
	    char error_msg[TCP_ERROR_MSG_SIZE];
		char model_name[TCP_MODEL_NAME_SIZE];
		int error_code;

		tcp_error_data() {
			memset(error_msg, 0, TCP_ERROR_MSG_SIZE);
			memset(model_name, 0, TCP_MODEL_NAME_SIZE);
			error_code = 0;
		}
};


/*
 *     Contains warnin data for TCP view
 */
struct tcp_warning_data {
	    char warning_msg[TCP_WARNING_MSG_SIZE];
};




/*
 *     Contains statistic data for TCP view
 */
struct tcp_statistic_data {
	    long packets_expected;
	    long packets_received;
		double bandwidth_bytes_per_sec;
		double processing_time_sec;

		tcp_statistic_data() {
			packets_expected = packets_received = 0;
			bandwidth_bytes_per_sec = 0.0;
			processing_time_sec = 0.0;
		}
};

