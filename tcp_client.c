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

struct server_info get_info(int argc, char *argv[]);
socklen_t sockaddr(char *host, int port, struct sockaddr_storage *ss);

int main(int argc, char *argv[])
{
  int sock;
  int s;
  int n;
  char buf[255];
  struct sockaddr_storage ss;
  struct sockaddr *sa;
  struct server_info info = get_info(argc, argv);
  socklen_t size;
 
  printf("b: %s\n", info.host);
  printf("p: %d\n", info.port);
  
  size = sockaddr(info.host, info.port, &ss);
  
  sa = (struct sockaddr *)&ss;
  sock  = socket(sa->sa_family, SOCK_STREAM,  0);
  if (sock < 0) {
    perror("socket");
    return -1;
  }
  
  if (connect(sock, sa, size) < 0){
    perror("connect");
    return -1;
  }

  memset(buf, 0,  sizeof(buf));
  n = read(sock,  buf,  sizeof(buf));
  printf("response: %s\n",  buf);
  return 0;
}

struct server_info get_info(int argc, char *argv[]){
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

// connectの際にsizeが必要なため返り値でそのサイズを返すことにした。
socklen_t sockaddr(char *host, int port, struct sockaddr_storage *ss){
  if (inet_pton(AF_INET, host, &((struct sockaddr_in *)ss)->sin_addr)){
    ((struct sockaddr_in *)ss)->sin_family = AF_INET;
    ((struct sockaddr_in *)ss)->sin_port = htons(port);
    return sizeof(*((struct sockaddr_in *)ss));
  }else if(inet_pton(AF_INET6, host, &((struct sockaddr_in6 *)ss)->sin6_addr)){
    ((struct sockaddr_in6 *)ss)->sin6_family = AF_INET6;
    ((struct sockaddr_in6 *)ss)->sin6_port = htons(port);
    return sizeof(*((struct sockaddr_in6 *)ss));
  }else{
    printf("invalid host. please confirm the value of -b\n");
    perror("sockaddr");
    exit(1);
  }
}
