#include <stdio.h>
#include "sockwrap.h"
#include "send_echo_request.h"
#include "icmp_recieve.h"

int data_in_socket(int sockfd)
{
  fd_set fds;
  struct timeval timeout;
  int rc;

  timeout.tv_sec = 1;
  timeout.tv_usec = 0;

  FD_ZERO(&fds);
  FD_SET(sockfd, &fds);
  rc = select(sizeof(fds)*8, &fds, NULL, NULL, &timeout);

  if (rc > 0 && FD_ISSET(sockfd, &fds))
    return 1;

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    printf("Usage: traceroute ip_address\n");
    exit(1);
  }

  const char* ip = argv[1];
  int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  int i = 10;
  //for(int i = 1; i <= 30; ++i)
  {
    send_echo_request(sockfd, i, ip);

    sleep(1);

    while(data_in_socket(sockfd))
    {
      struct ip* packet;
      struct icmp* icmp_packet;
      struct ip* original_packet;
      struct icmp* original_icmp_packet;
      int rec = icmp_recieve(sockfd, &packet, &icmp_packet,
        &original_packet, &original_icmp_packet);

      switch(rec)
      {
        case REC_PACKET:
          printf("a\n");
          break;
        case REC_PACKET_AND_ORIGINAL_PACKET:
          printf("b\n");
          break;
        default:
          printf("c\n");
          // REC_NONE, ignore
          break;
      }
    }
  }

  return 0;
}
