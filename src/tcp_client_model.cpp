#define CLIENT_PORT 3409
#define N 100000
#include "tcp_client_model.h"
#include <netinet/in.h>
struct sending
{
//    int all;
    int that;
    int size;
    char self;
}me;


TcpClientModel::TcpClientModel() {
	printf("Tcp client created!\n");
}


void TcpClientModel::defaultConfigure(){
    this->conf.ip = "192.168.1.4";
    //TcpClientModel.conf.numberOfPackages = 16;    
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
  if((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
    flag = 1;
  //printf("Socket created \n");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(CLIENT_PORT);
//  printf("port and family fill\n");
  if(inet_aton(this->conf.ip, &addr.sin_addr) == 0)
    flag = 1;
  //printf("IP address converted\n");
  if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
    flag = 1;
  printf("Connection done");
  return flag;
}
int TcpClientModel::sendInformation(int sockfd)
{
//    printf("Send Information\n");
    int count = 0;
    int nn = N;
  //  me.all = N;
    if(send(sockfd,(void *)&nn, sizeof(int), 0)==-1){
      printf("Error with sending initializes package\n");
      exit(1);
    }
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
    defaultConfigure();
    int i;
    int count = 0;
    int sockfd;
    if(createConnection(sockfd))
    {
      printf("Create connection errror!\n");
      exit(1);
    }
    printStatistic(TcpClientModel::sendInformation(sockfd));
    close(sockfd);
}


/*
*	This function provides pre configuration
*	Do not touch now
*/
void TcpClientModel::configure(struct configure_struct *) {
}
