#include <controller_view.h>

void ControllerView::printError(void *error_struct) {
      save_view->printError(error_struct); 
}

void ControllerView::printInfo(void *info_struct) {
       save_view->printInfo(info_struct);
}

void ControllerView::printWarning(void *warning_struct) {
       save_view->printWarning(warning_struct);
}

void ControllerView::printStatisticData(void *statistic_data_struct) {
      save_view->printStatisticData(statistic_data_struct);
}
void ControllerView::setView(View *view){
      this->save_view = view;
}





