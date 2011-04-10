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
#include "icmp.h"

int get_icmp_seq()
{
  static int gen = 1;
  return gen++;
}

void send_echo_request(int sockfd, int ttl, const char* ip)
{
  struct sockaddr_in remote_address;
  bzero (&remote_address, sizeof(remote_address));
  remote_address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &remote_address.sin_addr);

  struct icmp icmp_packet;
  icmp_packet.icmp_type = ICMP_ECHO;
  icmp_packet.icmp_code = 0;
  icmp_packet.icmp_id = getpid();
  icmp_packet.icmp_seq = get_icmp_seq();
  icmp_packet.icmp_cksum = 0;
  icmp_packet.icmp_cksum = in_cksum((u_short*)&icmp_packet, 8, 0);

  Setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

  Sendto(sockfd, &icmp_packet, ICMP_HEADER_LEN, 0, &remote_address, sizeof(remote_address));
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

  send_echo_request(sockfd, 10, ip);

  return 0;
}
