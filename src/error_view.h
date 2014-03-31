#ifndef VIEW_H
	#include "view.h"
#endif
#define ERROR_VIEW_H	1


/*
*	This view provides show of error messages
*/
class ErrorView : public View {
	public:
		ErrorView();
		void print(void *data);
};
