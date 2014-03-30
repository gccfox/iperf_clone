#pragma once
#include "view.h"

class ViewController: public View {
		View *view;

	public:
		ViewController();
		ViewController(View *_view);
		void setView(View *_view);
		void printError(void *error_struct);
		void printInfo(void *info_struct);
		void printWarning(void *warning_struct);
		void printStatisticData(void *statistic_data_struct);
};
