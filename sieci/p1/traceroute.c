#include <stdio.h>
#include "sockwrap.h"
#include "send_echo_request.h"
#include "icmp_recieve.h"

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

  icmp_recieve(sockfd);

  return 0;
}
