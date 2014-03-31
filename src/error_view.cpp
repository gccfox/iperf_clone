#ifndef ERROR_VIEW_H
	#include "error_view.h"
#endif
#include <stdlib.h>
#include <stdio.h>

/*
*	Construcotr
*/
ErrorView::ErrorView() {
	printf("Error view constructed!\n");
}


/*
*	This function provides viewing data on console
*/
void ErrorView::print(void *data) {
	printf("Error! %s\n", (char *)data);
}
