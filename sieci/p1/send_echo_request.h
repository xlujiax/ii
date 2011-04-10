#ifndef __SEND_ECHO_REQUEST_H
#define __SEND_ECHO_REQUEST_H

#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sockwrap.h"
#include "icmp.h"

void send_echo_request(int sockfd, int ttl, const char* ip);

#endif
