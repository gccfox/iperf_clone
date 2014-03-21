/*
*	Just a constructor 
*/
#define CLIENT_PORT 3409
#define N 100000
#include "tcp_client_model.h"
#include <netinet/in.h>
struct sending
{
    int all;
    int that;
    int size;
    char self;
}me;


TcpClientModel::TcpClientModel() {
	printf("Tcp client created!\n");
}


void TcpClientModel::defaultConfigure(){
//    TcpClientModel.conf.ip = "192.168.1.4";
    //TcpClientModel.conf.numberOfPackages = 16;    
}

/*
*	Main function of tcp client
*	Place your code here
*/
int TcpClientModel::createConnection(int &sock) //conection creat function
{
  struct sockaddr_in addr;
  int flag = 0;
  if((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
    flag = 1;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(CLIENT_PORT);
  if(inet_aton(conf.ip, &addr.sin_addr) == 0)
    flag = 1;
  if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
    flag = 1;
  return flag;
}
int TcpClientModel::sendInformation(int sockfd)
{
    int count = 0;
    me.all = N;
    for(int i = 0; i <= N; i++)
    {
        me.that = i;
        me.self = 'S';
        me.size = sizeof(me.self);
        if(send(sockfd, (void *)&me, sizeof(me),0) == -1)
            printf("Send error with package number %d\n", i);
        else
            count++;
    }
    return count;
}
void  TcpClientModel::printStatistic(int sent)
{
  printf("Try to send packages  - %d\n", N);
  printf("Sent without any problems - %d\n", sent);
}
void TcpClientModel::run() {
    TcpClientModel::defaultConfigure();
    int i;
    int count = 0;
    int sockfd;
    if(TcpClientModel::createConnection(sockfd))
    {
      printf("Create connection errror!\n");
      exit(1);
    }
    TcpClientModel::printStatistic(TcpClientModel::sendInformation(sockfd));
    close(sockfd);
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpClientModel::configure(struct configure_struct *) {
}
