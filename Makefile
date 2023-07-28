CC=clang
CFLAGS=-Werror -Wall -Wextra \
       -std=c17 -pedantic -g

please: please.o fileinfo.o
	$(CC) $(CFLAGS) -o please please.o fileinfo.o

please.o: please.c fileinfo.h
	$(CC) $(CFLAGS) -c please.c

fileinfo.o: fileinfo.c fileinfo.h
	$(CC) $(CFLAGS) -c fileinfo.c

.PHONY: clean
clean:
	-rm please *.o
