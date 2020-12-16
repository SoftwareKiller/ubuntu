.PHONY:all

all:server client

server:server_tcp.c
	gcc -o $@ $^

client:client.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f server client
