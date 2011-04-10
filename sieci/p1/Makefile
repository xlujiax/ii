CC = gcc 
CFLAGS = -Wall -W -Wshadow -std=gnu99
TARGETS = sockwrap imcp traceroute
 
all: traceroute

traceroute: sockwrap imcp traceroute.c
	$(CC) -o $@ $(CFLAGS) traceroute.c

imcp: imcp.h imcp.c
	$(CC) -o $@ $(CFLAGS) $^

sockwrap: sockwrap.h sockwrap.c
	$(CC) -o $@ $(CFLAGS) $^

distclean:
	rm -f traceroute
clean:
	rm -f $(TARGETS)
