CC=gcc
CFLAGS=-Wall -Wextra

all: lights_nif.so

lights_nif.so:
	gcc -o lights_nif.so -fpic -shared lights.c lights_nif.c -lpigpio -lrt -lpthread -I/usr/local/lib/erlang/usr/include/

clean:
	rm -f lights_nif.so
