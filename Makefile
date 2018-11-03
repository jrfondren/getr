CC=gcc
CFLAGS=-Wall -O3

getr: getr.c
	$(CC) $(CFLAGS) -o $@ $<

clean::
	rm -fv getr
