#ifndef TCP_VIEW_H
       #include "tcp_View.h"
#endif
	  
#include <stdlib.h>
#include <stdio.h>
		   
/*
 *   Construcotr
 */

tcpView::tcpView() 
	{
	
	}

/*
 *   This function provides viewing data on console
 */
void tcpView::printError(void *data) 
	{
		printf("Error! %s\n", (char *)data);
	}


/*
 *	 Function print data of tcp_struct on concole
 */
void tcpView::print_data_struct(void *data)
	{	
		struct tcp_data_struct *tcpData = (tcp_data_struct)data;
		printf("Print data of tcp_data_struct"); //printf("Speed: %d; ...; ...", tcpData -> speed, ...., ....);
	}
