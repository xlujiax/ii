#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
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

  printf("My pid is %d\n", getpid());

  const char* ip = argv[1];
  int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  for(int i = 1; i <= 30; ++i)
  {
    printf("%d. \n", i);
    send_echo_request(sockfd, i, ip);
    send_echo_request(sockfd, i, ip);
    send_echo_request(sockfd, i, ip);

    while(data_in_socket(sockfd))
    {
      struct ip* packet;
      struct icmp* icmp_packet;
      struct ip* original_packet;
      struct icmp* original_icmp_packet;
      char readable_ip[INET_ADDRSTRLEN];
      int rec = icmp_recieve(sockfd, readable_ip,
	&packet, &icmp_packet,
        &original_packet, &original_icmp_packet);

      switch(rec)
      {
        case REC_PACKET:
	  {
	    printf("a: (%d %d) from %s\n",
	      icmp_packet->icmp_id,
	      icmp_packet->icmp_seq, readable_ip);
	  }
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
