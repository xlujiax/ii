#include "send_echo_request.h"

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
  int convert = inet_pton(AF_INET, ip, &remote_address.sin_addr);

  if(convert == 0) { printf("IP address not parsable\n"); exit(1); }
  if(convert == -1) { printf("IP address conversion failed\n"); exit(1); }

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
