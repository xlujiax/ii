CC = gcc 
CFLAGS = -Wall -W -Wshadow -std=gnu99
TARGETS = sockwrap icmp traceroute send_echo_request icmp_recieve
 
all: traceroute

traceroute: icmp sockwrap send_echo_request icmp_recieve traceroute.c
	$(CC) -o $@ $(CFLAGS) $^

send_echo_request: icmp sockwrap send_echo_request.c send_echo_request.h
	$(CC) -c send_echo_request.c $(CFLAGS) -o $@

icmp_recieve: icmp sockwrap icmp_recieve.c icmp_recieve.h
	$(CC) -c icmp_recieve.c $(CFLAGS) -o $@

icmp: icmp.h icmp.c
	$(CC) -c icmp.c $(CFLAGS) -o $@

sockwrap: sockwrap.h sockwrap.c
	$(CC) -c sockwrap.c $(CFLAGS) -o $@

distclean:
	rm -f traceroute
clean:
	rm -f $(TARGETS)
