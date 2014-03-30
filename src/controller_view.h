#pragma once
#include <View.h>
#include <info_types.h>
#include <Controller_view_types.h>
class ControllerView: public View{
                void setView(View *view);
    	        void printError(void *error_struct);
		void printInfo(void *info_struct);
		void printWarning(void *warning_struct);
		void printStatisticData(void *statistic_data_struct);
};
