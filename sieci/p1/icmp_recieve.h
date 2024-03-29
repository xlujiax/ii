#ifndef __ICMP_RECIEVE
#define __ICMP_RECIEVE

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

#define REC_NONE 0
#define REC_PACKET 1
#define REC_PACKET_AND_ORIGINAL_PACKET 2

int icmp_recieve(
  int sockfd,
  char* readable_ip,
  struct ip** packet, struct icmp** icmp_packet,
  struct ip** original_packet, struct icmp** original_icmp_package);
  
#endif
