.PHONY:all

all:server_sel client

server_sel:server_sel.c
	gcc -o $@ $^

client:client.c
	gcc -o $@ $^
	
.PHONY:clean
clean:
	rm -f server_sel client
