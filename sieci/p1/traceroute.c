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

  const char* ip = argv[1];
  int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  for(int i = 1; i <= 30; ++i)
  {
    printf("%d. ", i);

    struct timeval send_time;
    gettimeofday(&send_time, NULL);
    
    int id1 = send_echo_request(sockfd, i, ip);
    int id2 = send_echo_request(sockfd, i, ip);
    int id3 = send_echo_request(sockfd, i, ip);

    int sum_miliseconds = 0;
    int rec_packets = 0;

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

      if(rec == REC_PACKET)
      {
	struct timeval rec_time;
	gettimeofday(&rec_time, NULL);

	int seconds  = rec_time.tv_sec  - send_time.tv_sec;
	int useconds = rec_time.tv_usec - send_time.tv_usec;
	int mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

	printf("%s ", readable_ip);
	rec_packets++;
	sum_miliseconds += mtime;

	// wyjście z zewnętrznej pętli
	i = 30;
	break;
      }
      else if(rec == REC_PACKET_AND_ORIGINAL_PACKET)
      {
	if(original_icmp_packet->icmp_id == getpid())
	{
	  if(original_icmp_packet->icmp_seq == id1 ||
	     original_icmp_packet->icmp_seq == id2 ||
	     original_icmp_packet->icmp_seq == id3)
	  {
	    struct timeval rec_time;
	    gettimeofday(&rec_time, NULL);
	    
	    int seconds  = rec_time.tv_sec  - send_time.tv_sec;
	    int useconds = rec_time.tv_usec - send_time.tv_usec;
	    int mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

	    // spełnienie tego warunku implikuje, że pakiet ma ttl == i
	    printf("%s ", readable_ip);
	    rec_packets++;
	    sum_miliseconds += mtime;
	  }
	}
      }
    }

    if(rec_packets == 0)
      printf("*\n");
    else
      printf("%dms\n", sum_miliseconds / rec_packets);
  }

  return 0;
}
