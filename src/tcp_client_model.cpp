#define CLIENT_PORT 3409
#include "tcp_client_model.h"
#include <netinet/in.h>
/*struct sending
{
//    int all;
    int that;
    int size;
    char self;
}me;*/


TcpClientModel::TcpClientModel() {
	//printf("Tcp client created!\n");
}


/**
 *    Some shit
 */
void TcpClientModel::defaultConfigure(){
}

/*
*	Main function of tcp client
*	Place your code here
*/
int TcpClientModel::createConnection(int &sock) //conection creat function
{
  //printf("Create Connection \n");
  struct sockaddr_in addr;
  //printf("struct created \n");
  int flag = 0;
  if((sock = socket(AF_INET, SOCK_STREAM, 0))<0) {
	  perror("TCP_client: socket creation error!\n");
	  exit(0);
  }
  //printf("Socket created \n");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

//  printf("port and family fill\n");
  if(inet_aton(host_ip_address, &addr.sin_addr) == 0) {
	  perror("TCP_client: error invalid ip");
  }
//  printf("IP address converted\n");
  if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0) {
	  perror("TCP_client: connection problems\n");
  }
//  printf("Connection done\n");
  return flag;
}



int TcpClientModel::sendInformation(int sockfd)
{
	struct tcp_data_packet 	data_packet;
	printf("[TCP_client]: sending data\n");
    int count = 0;
    int nn = packets_count;
  //  me.all = N;
    if(send(sockfd,(void *)&nn, sizeof(int), 0)==-1){
      printf("TCP_client: Error with sending initializes package\n");
      exit(1);
    }
    for(int i = 0; i < packets_count; i++)
    {
        /*me.that = htons(i);
        me.self = 'S';
        me.size = sizeof(me);*/
		data_packet.number = i;
        if(send(sockfd, (void *)&data_packet, sizeof(struct tcp_data_packet),0) == -1)
            printf("TCP_client: send error with package number %d\n", i);
        else {
            count++;
//            printf("Send data packet with id %i %i\n", me.that, i);
        }
        //usleep(1);
    }
    return count;
}



void  TcpClientModel::printStatistic(int sent)
{
  printf("[TCP_client]: sendings packages  - %d\n", packets_count);
  printf("[TCP_client]: sent without any problems packages- %d\n", sent);
}



void TcpClientModel::run() {
    defaultConfigure();
    int i;
    int count = 0;
    int sockfd;
    if(createConnection(sockfd))
    {
      printf("TCP_client: Create connection errror!\n");
      exit(1);
    }
    printStatistic(sendInformation(sockfd));
    close(sockfd);
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpClientModel::configure(struct model_configuration_struct *conf_struct) {
	port = conf_struct->port;
	host_ip_address = conf_struct->ip;
	packets_count = conf_struct->packets_count;
}
