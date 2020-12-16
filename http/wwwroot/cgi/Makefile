.PHONY:all

all:insert_cgi select_cgi

insert_cgi:insert_cgi.cpp comm.cpp
	g++ -o $@ $^ -I/usr/include/mysql -L /usr/lib64/mysql -lmysqlclient

select_cgi:select_cgi.cpp comm.cpp
	g++ -o $@ $^ -I/usr/include/mysql -L /usr/lib64/mysql -lmysqlclient

.PHONY:clean
clean:
	rm -f insert_cgi select_cgi
