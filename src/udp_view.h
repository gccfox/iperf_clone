#pragma once
#include "view.h"
#include "udp_view_types.h"

class UdpDataView : public View {
	public:
		void printError(void *error_struct);
		void printInfo(void *info_struct);
		void printWarning(void *warning_struct);
		void printStatisticData(void *statistic_data_struct);
};
