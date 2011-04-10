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

int icmp_recieve(int sockfd)
{
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(sender);
  buffer_ptr = buffer;
  remaining_packet_data = Recvfrom(sockfd, buffer_ptr, IP_MAXPACKET,
    0, &sender, &sender_len);

  char str[20];
  inet_ntop(AF_INET, &(sender.sin_addr), str, sizeof(str));

  // Received IP packet with ICMP content
  struct ip* packet = (struct ip*) buffer_ptr;
  skip_bytes (packet->ip_hl * 4);

  // IP header
  struct icmp* icmp_packet = (struct icmp*) buffer_ptr;
  skip_bytes (ICMP_HEADER_LEN);

  // ICMP type and code
  if (icmp_packet->icmp_type == ICMP_TIME_EXCEEDED &&
    icmp_packet->icmp_code == ICMP_EXC_TTL) {

    // Original IP header
    struct ip* packet_orig = (struct ip*) buffer_ptr;
    skip_bytes (packet_orig->ip_hl * 4);

    if (packet_orig->ip_p == IPPROTO_ICMP) {
      // ICMP packet
      skip_bytes (ICMP_HEADER_LEN);
      assert(remaining_packet_data == 0);
    } else {
      // Original IP payload
      skip_bytes (remaining_packet_data);
    }
  }

  if (icmp_packet->icmp_type == ICMP_ECHOREPLY) {
    // ICMP payload
    skip_bytes (remaining_packet_data);
  }
  return 0;
}
