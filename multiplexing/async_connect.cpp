#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <iostream>

using namespace std;

int main() {
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0) {
        cerr << "socket error" << endl;
        return -1;
    }
    int oldFlag = fcntl(clientfd, F_GETFD, 0);
    oldFlag |= O_NONBLOCK;
    fcntl(clientfd, F_SETFL, oldFlag);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5555);
    socklen_t len = sizeof(server);
    while(true){
        int ret = connect(clientfd, (struct sockaddr*)&server, len);
        if(ret == 0) {
            cout << "connect success" << endl;
            break;
        }
        else if(ret == -1){
            if(errno == EINTR) {
                cout << "signal interput, try again" << endl;
                continue;
            }
            else if(errno == EINPROGRESS){
                cout << "connecting ..." << endl;
                sleep(1);
            }
            else{
                cerr << "connect error" << endl;
                close(clientfd);
                return -1;
            }
        }
    }

    /*fd_set writeset;
    FD_ZERO(&writeset);
    FD_SET(clientfd, &writeset);
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if(select(clientfd + 1, nullptr, &writeset, nullptr, &tv) == 1)
        cout << "connect success" << endl;
    else
        cout << "connect fail" << endl;*/

    close(clientfd);
    return 0;
}

