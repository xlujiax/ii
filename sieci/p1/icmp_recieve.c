#include "icmp_recieve.h"

unsigned char   buffer[IP_MAXPACKET+1];
unsigned char*  buffer_ptr;
int             remaining_packet_data;

void skip_bytes (int count)
{
  for (int i=0; i<count; i++) {
    buffer_ptr++;
    remaining_packet_data--;
  }
}

int icmp_recieve(
  int sockfd,
  char* readable_ip,
  struct ip** packet, struct icmp** icmp_packet,
  struct ip** original_packet, struct icmp** original_icmp_packet)
{
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(sender);
  buffer_ptr = buffer;
  remaining_packet_data = Recvfrom(sockfd, buffer_ptr, IP_MAXPACKET,
    0, &sender, &sender_len);

  inet_ntop(AF_INET, &(sender.sin_addr), readable_ip, INET_ADDRSTRLEN);

  // Received IP packet with ICMP content
  packet = (struct ip**)&buffer_ptr;
  skip_bytes ((*packet)->ip_hl * 4);

  // IP header
  icmp_packet = (struct icmp**)&buffer_ptr;

  if ((*icmp_packet)->icmp_type == ICMP_TIME_EXCEEDED &&
    (*icmp_packet)->icmp_code == ICMP_EXC_TTL) {
    original_packet = (struct ip**)&buffer_ptr;
    skip_bytes((*original_packet)->ip_hl * 4);

    if ((*original_packet)->ip_p == IPPROTO_ICMP) {
      original_icmp_packet = (struct icmp**)&buffer_ptr;
      return REC_PACKET_AND_ORIGINAL_PACKET;
    } else {
      return REC_NONE;
    }
  }

  if ((*icmp_packet)->icmp_type == ICMP_ECHOREPLY) {
    return REC_PACKET;
  }

  return REC_NONE;
}
