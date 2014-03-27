#define VIEW_H		1
/*
*	Abstract interface for view class
*	You should define (void *) to (struct yuor_info_type *)
*	for defined type of View.
*/
class View {
	public:
		void printError(void *);
		void printInfo(void *);
		void printWarning(void *);
		void printStatisticData(void *);
};
