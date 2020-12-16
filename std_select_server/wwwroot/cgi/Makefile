.PHONY:all

all:select_cgi

select_cgi:select_cgi.cpp comm.cpp
	g++ -o $@ $^ -I/usr/include/mysql -L /usr/lib64/mysql -lmysqlclient

.PHONY:clean
clean:
	rm -f select_cgi
