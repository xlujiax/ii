#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include "sockwrap.h"
#include "send_echo_request.h"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    printf("Usage: traceroute ip_address\n");
    exit(1);
  }

  const char* ip = argv[1];

  int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  send_echo_request(sockfd, 10, ip);
  sleep(1);

  return 0;
}
