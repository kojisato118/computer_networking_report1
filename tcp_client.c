#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *args[])
{
  int sock;
  int s;
  int port = 3000;
  int n;
  char *host = "host";
  char buf[255];
  struct sockaddr_in6 server;

  sock  = socket(AF_INET6, SOCK_STREAM,  0);
  if (sock < 0) {
    perror("socket");
    return -1;
  }
  server.sin6_family = AF_INET6;
  server.sin6_port = htons(port);
  s = inet_pton(AF_INET6, host,  &server.sin6_addr);

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
