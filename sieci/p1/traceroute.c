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

  for(int i = 1; i <= 30; ++i)
  {
    send_echo_request(sockfd, i, ip);
    
    sleep(1);

    struct ip* packet;
    struct icmp* icmp_packet;
    struct ip* original_packet;
    struct icmp* original_icmp_packet;
    int rec = icmp_recieve(sockfd, &packet, &icmp_packet, &original_packet, &original_icmp_packet);

    switch(rec)
    {
      case REC_PACKET:
	break;
      case REC_PACKET_AND_ORIGINAL_PACKET:
	break;
      default:
	// REC_NONE, ignore
	break;
    }
  }

  return 0;
}
