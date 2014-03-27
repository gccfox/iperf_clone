#include "udp_view.h"
/**
  *		How to print error message from UDP model
  */
void UdpView::printError(void *error_struct) {
	struct udp_error_struct		perror_struct = (struct udp_error_struct *)error_struct;
	printf("ERROR: %s: %s\n", perror_struct->model_name, perror_struct->error_msg); 
	perror(perror_struct->error_msg);
}



/**
  *	How to print info message from UDP model
  */
void UdpView::printInfo(void *info_struct) {
}



/**
  *		How to print warning message from UDP model
  */
void UdpView::printWarning(void *warning_struct) {
}



/**
  *		How to print data message from UDP model
  */
void UdpView::printStatisticData(void *statistic_data_struct) {
}



