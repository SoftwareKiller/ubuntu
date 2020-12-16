.PHONY:all

all:cas mutex spin

cas:cas.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

mutex:mutex_.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

spin:spin.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f mutex cas spin
