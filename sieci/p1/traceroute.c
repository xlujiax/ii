#include <stdio.h>
#include "sockwrap.h"
#include "send_echo_request.h"
#include "icmp_recieve.h"
#include "data_in_sock.h"

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
    send_echo_request(sockfd, i, ip);
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
