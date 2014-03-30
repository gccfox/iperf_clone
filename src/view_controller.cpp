#include "view_controller.h"

ViewController::ViewController(View *_view) {
	this->view = _view;
}


ViewController::ViewController() {
}



void ViewController::printError(void *error_struct) {
	this->view->printError(error_struct); 
}



void ViewController::printInfo(void *info_struct) {
    this->view->printInfo(info_struct);
}



void ViewController::printWarning(void *warning_struct) {
    this->view->printWarning(warning_struct);
}



void ViewController::printStatisticData(void *statistic_data_struct) {
    this->view->printStatisticData(statistic_data_struct);
}



void ViewController::setView(View *_view){
    this->view = _view;
}





