.PHONY:all

all:read write

read:read_process.cpp share_mem.cpp
	g++ -g -o $@ $^ -lrt -std=c++11

write:write_process.cpp share_mem.cpp 
	g++ -g -o $@ $^ -lrt -std=c++11

.PHONY:clean
clean:
	rm -f read write

