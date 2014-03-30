#include <controller_view.h>

void ControllerView::printError(void *error_struct) {
       view->printError((void *)&error_struct); 
}

void ControllerView::printInfo(void *info_struct) {
       view->printInfo((void *)&info_struct);
}

void ControllerView::printWarning(void *warning_struct) {
       view->printWarning((void *)&warning_struct);
}

void ControllerView::printStatisticData(void *statistic_data_struct) {
      view->printStatisticData((void *)&statistic_data_struct);
}
void ControllerView::setView(View *view){
      view = new View();
}





