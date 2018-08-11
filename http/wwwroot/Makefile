WORK_DIR=$(shell pwd)
cc=gcc
bin=httpd
src=http.c threadpool.c condition.c
LDFLAGS=-lpthread

$(bin):$(src)
	$(cc) -g -o $@ $^ $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(bin)
