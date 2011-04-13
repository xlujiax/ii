/* Marcin Kolarczyk
 * nr indeksu: 221041
 *
 * Skorzystałem z pomocniczych funkcji z wykładu (sockwrap.h, icmp.h)
 */
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
#define MAX_REQ 3
#define MAX_HOPS 30

unsigned char 	buffer[IP_MAXPACKET+1];
unsigned char* 	buffer_ptr;
int	        remaining_packet_data;

int main (int argc, char** argv)
{
	if (argc != 2) 
	{ 
		printf ("Usage: ./troute ip\n"); 
		exit(1); 
	}
	int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);	
	char* req_addr = argv[1]; // Adres do ktorego bedziemy wysylac komunikat ICMP 
	int ident = getpid() & 0xFFFF; // id procesu
	
	struct sockaddr_in remote_address;
	bzero (&remote_address, sizeof(remote_address));
	remote_address.sin_family	= AF_INET;
	if( inet_pton(AF_INET, req_addr, &remote_address.sin_addr) < 1 )
	{
		printf("Incorrect ip\n");
		exit(1);
	}

	struct icmp icmp_packet;
	icmp_packet.icmp_type = ICMP_ECHO;
	icmp_packet.icmp_code = 0;
	icmp_packet.icmp_id = ident;		
	icmp_packet.icmp_seq = 1;		
	icmp_packet.icmp_cksum = 0;
	icmp_packet.icmp_cksum = in_cksum((u_short*)&icmp_packet, 8, 0);
		
	int ttl=1, req=0; // TTL oraz nr proby
	while (ttl <= MAX_HOPS)
	{
		// Ustawiamy pole TTL
		Setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
		Sendto(sockfd, &icmp_packet, ICMP_HEADER_LEN, 0, &remote_address, sizeof(remote_address));
		
		fd_set readfds, masterfds; // zbiory do selecta
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 500000; //500 ms
		FD_ZERO(&masterfds); //zerowanie 
		FD_SET(sockfd, &masterfds); //dodawanie
		readfds = masterfds;
		
		if (select(sockfd+1, &readfds, NULL, NULL, &timeout) < 0)
		{ // jesli cos sie zepsuje
			perror("on select");
			exit(1);
		}
		
		if (FD_ISSET(sockfd, &readfds))
		{ //jesli jest co odbierac
			struct sockaddr_in sender;	
			socklen_t sender_len = sizeof(sender);
			buffer_ptr = buffer;
			remaining_packet_data = Recvfrom (sockfd, buffer_ptr, IP_MAXPACKET, 0, &sender, &sender_len);
	
			char str[20]; 
			inet_ntop(AF_INET, &(sender.sin_addr), str, sizeof(str));
			printf ("%d. %s\n", ttl, str);
	
			// naglowek IP
			struct ip* packet = (struct ip*) buffer_ptr;
			buffer_ptr += packet->ip_hl*4;
			remaining_packet_data -= packet->ip_hl*4;
	
			// ICMP enkapsulowany w pakiecie IP
			struct icmp* icmp_packet = (struct icmp*) buffer_ptr;
			buffer_ptr += ICMP_HEADER_LEN;
			remaining_packet_data -= ICMP_HEADER_LEN;
			
			// TIME_EXCEEDED
			if (icmp_packet->icmp_type == ICMP_TIME_EXCEEDED && 
				icmp_packet->icmp_code == ICMP_EXC_TTL) {	
				struct ip* packet_orig = (struct ip*) buffer_ptr;
				buffer_ptr += packet_orig->ip_hl * 4;
				remaining_packet_data -= packet_orig->ip_hl * 4;
				
				if (packet_orig->ip_p == IPPROTO_ICMP  ) {
					
					//Sprawdzanie czy to 'nasz' pakiet
					struct icmp* icmp_echo_packet = (struct icmp*) buffer_ptr;
					if( icmp_echo_packet->icmp_id != ident ) break; 
					
					//buffer_ptr += ICMP_HEADER_LEN;
					//remaining_packet_data -= ICMP_HEADER_LEN;
	
				}else break;
			}
			
			if (icmp_packet->icmp_type == ICMP_ECHOREPLY) {
				break;
			}
			
			ttl++;
        		req = 0;
		}
		else
		{ // jesli przekroczony czas
			if( req > MAX_REQ )
			{ //jesli przekroczony limit zapytan bez odpowiedzi
				printf("%d. *\n", ttl);
				ttl++;
				req = 0;
			}else
			{
				req++;
			}
		}
	}
        return 0;
}
















