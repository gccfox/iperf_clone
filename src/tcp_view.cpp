#include "tcp_view.h"

void TcpDataView::printError(void *error_struct){
	struct tcp_error_struct*		_error_struct = (struct tcp_error_struct)error_struct; 
	printf("ERROR %i\n %s: %s", _error_struct -> error_code, _error_struct -> model_name, _error_struct -> error_msg);
}


void TcpDataView::printInfo(void *info_struct){
	struct tcp_info_data*  	_info_struct = (struct tcp_info_data)info_struct;
	printf("Information message: %s\n", _info_struct -> info_msg);
}

void TcpDataView::printWarning(void *warning_struct){
	struct tcp_warning_data* _warning_struct = (struct tcp_warning_data)warning_struct;
	printf("WARNING: %s\n", _warning_struct -> warning_msg);
}

void TcpDataView::printStatisticData(void *statistic_data_struct){
	struct tcp_statistic_data* _statistic_data_struct = (struct tcp_statistic_data)statistic_data_struct;
	printf("Statistic:\n
				packets expected: %d
				packets received: %d
				bandwidth(dytes per seccond): %f
				processing time(sec): %f
				",
				_statistic_data_struct -> packets_expected,
				_statistic_data_struct -> packets_received,
				_statistic_data_struct -> bandwidth_bytes_per_sec,
				_statistic_data_struct -> processing_time_sec);
}
