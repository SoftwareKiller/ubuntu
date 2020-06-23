.PHONY:all

all:redis_cli

FLAGS=-lpthread

redis_cli:main.cpp parser.cpp client.cpp
	g++ -g -o $@ $^ $(FLAGS)

.PHONY:clean
clean:
	rm -rf redis_cli
