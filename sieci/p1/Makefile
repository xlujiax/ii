CC = gcc 
CFLAGS = -Wall -W -Wshadow -std=gnu99
TARGETS = sockwrap icmp traceroute
 
all: traceroute

traceroute: sockwrap icmp traceroute.c
	$(CC) -o $@ $(CFLAGS) $^

icmp: icmp.h icmp.c
	$(CC) -c icmp.c $(CFLAGS) -o $@

sockwrap: sockwrap.h sockwrap.c
	$(CC) -c sockwrap.c $(CFLAGS) -o $@

distclean:
	rm -f traceroute
clean:
	rm -f $(TARGETS)
