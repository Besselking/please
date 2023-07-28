CC=clang
CFLAGS=-Werror -Wall -Wextra \
       -Weverything -Wno-padded \
       -Wno-declaration-after-statement \
       -Wno-unsafe-buffer-usage \
       -std=c2x -pedantic -g

please: please.o fileinfo.o
	$(CC) $(CFLAGS) -o please please.o fileinfo.o

please.o: please.c fileinfo.h
	$(CC) $(CFLAGS) -c please.c

fileinfo.o: fileinfo.c fileinfo.h
	$(CC) $(CFLAGS) -c fileinfo.c

.PHONY: clean
clean:
	-rm please *.o
