#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

struct server_info {
  char *host;
  int port;
};

struct server_info get_option(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  int sock;
  int s;
  int n;
  char buf[255];
  struct sockaddr_in6 server;
  struct server_info info = get_option(argc, argv);
 
  printf("b: %s\n", info.host);
  printf("p: %d\n", info.port);
 
  sock  = socket(AF_INET6, SOCK_STREAM,  0);
  if (sock < 0) {
    perror("socket");
    return -1;
  }
  server.sin6_family = AF_INET6;
  server.sin6_port = htons(info.port);
  s = inet_pton(AF_INET6, info.host,  &server.sin6_addr);

  if (s < 1){
    perror("inet_pton");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0){
    perror("connect");
    return -1;
  }

  memset(buf, 0,  sizeof(buf));
  n = read(sock,  buf,  sizeof(buf));
  printf("%s¥n",  buf);
  return 0;
}

struct server_info get_option(int argc, char *argv[]){
  int result;
  char *host;
  int port;

  while((result=getopt(argc,argv,"b:p:"))!=-1){
    switch(result){

    case 'b':
      host = optarg;
      break;
    case 'p':
      port = atoi(optarg);
      break;
    }
  }

  struct server_info info = {host, port};
  return info;
}
