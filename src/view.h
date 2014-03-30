#pragma once
/*
*	Abstract interface for view class
*	You should define (void *) to (struct yuor_info_type *)
*	for defined type of View.
*/
class View {
	public:
		View() {};
		virtual void printError(void *) {};
		virtual void printInfo(void *) {};
		virtual void printWarning(void *) {};
		virtual void printStatisticData(void *) {};
};
