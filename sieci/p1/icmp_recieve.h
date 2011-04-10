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
#include "sockwrap.h"
#include "icmp.h"

int icmp_recieve(int sockfd);
  
#endif
