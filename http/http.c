#include<stdio.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#include<pthread.h>
#include"threadpool.h"

#define MAX 1024
#define HOME_PAGE "index.html"
#define PAGE_404 "wwwroot/404.html"

static void Usage(const char* proc)
{
    printf("Usage %s [port]\n", proc);
}

static int startup(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket");
        exit(2);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        perror("bind");
        exit(3);
    }

    if(listen(sock, 5) < 0){
        perror("listen");
        exit(4);
    }

    return sock;
}

static int getLine(int sock, char line[], int size)
{
    char c = 'x';
    int i = 0;
    while(c != '\n' && i < size - 1){
        ssize_t s = recv(sock, &c, 1, 0);
        if(c == '\r'){
            recv(sock, &c, 1, MSG_PEEK);
            if( c == '\n'){
                recv(sock, &c, 1, 0);
            }else{
                c = '\n';
            }
        }
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

static void clearHead(int sock)
{
    char line[MAX];
    do{
        getLine(sock, line, sizeof(line));
    }while(strcmp("\n", line));
}

void show_404(int sock)
{
    char line[MAX];
    struct stat st;
    sprintf(line, "HTTP/1.0 404 NOT FOUND\r\n");
    send(sock, line, strlen(line), 0);
    sprintf(line, "Content-Type:text/html;charset=utf-8\r\n");
    send(sock, line, strlen(line), 0);
    sprintf(line, "\r\n");
    send(sock, line, strlen(line), 0);
    int fd = open(PAGE_404, O_RDONLY);
    stat(PAGE_404, &st);
    sendfile(sock, fd, NULL, st.st_size);
    close(fd);
}

static void echoErrMsg(int sock, int status_code)
{
    switch(status_code){
    case 404:
        show_404(sock);
        break;
    default:
        break;
    }
}

int exe_cgi(int sock, char* method, char* path, char* query_string)
{
    char line[MAX];
    int content_length = -1;
    char method_env[MAX/32];
    char query_string_env[MAX];
    char content_length_env[MAX/8];

    if(strcasecmp(method, "GET") == 0){
        clearHead(sock);
    }else{//POST方法
        do{
            getLine(sock, line, sizeof(line));
            //从首部中拿出POST实体的长度
            if(strncasecmp(line,"Content-Length:", 16) == 0){
                content_length = atoi(line + 16);
            }
        }while(strcmp(line, "\n"));
        if(content_length == -1){
            return 404;
        }
    }
    int input[2];
    int output[2];

    pipe(input);
    pipe(output);

    pid_t id = fork();
    if(id < 0){
        return 404;
    }
    else if(id == 0){//child
        close(input[1]);
        close(output[0]);

        dup2(input[0], 0);
        dup2(output[1], 1);

        sprintf(method_env, "METHOD=%s", method);
        putenv(method_env);
        if(strcasecmp(method, "GET") == 0){
            sprintf(query_string_env, "QUERY_STRING=%s", query_string);
            putenv(query_string_env);
        }
        else{
            sprintf(content_length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(content_length_env);
        }
        //exec
        execl(path, path, NULL);
        exit(1);
    }else{
        close(input[0]);
        close(output[1]);


        sprintf(line, "HTTP/1.0 200 OK\r\n");
        send(sock, line, strlen(line), 0);
        sprintf(line, "Content-Type:text/html;charset=ISO-8859-1\r\n");
        send(sock, line, strlen(line), 0);
        sprintf(line, "\r\n");
        send(sock, line, strlen(line), 0);

        int i = 0;
        char c;
        if(strcasecmp(method, "POST") == 0){
            for(; i < content_length; ++i){
                recv(sock, &c, 1, 0);
                write(input[1], &c, 1);
            }
        }

        while(read(output[0], &c, 1) > 0){
            send(sock, &c, 1, 0);
        }
        waitpid(id, NULL, 0);
        close(input[1]);
        close(output[0]);
    }
    return 200;
}

int echo_www(int sock, char* path, int size)
{
    char line[MAX];
    clearHead(sock);

    int fd = open(path, O_RDONLY);
    if(fd < 0){
        return 404;
    }

    sprintf(line, "HTTP/1.0 200 OK\r\n");
    send(sock, line, strlen(line), 0);
    sprintf(line, "Content-Type:text/html;charset=utf-8\r\n");
    send(sock, line, strlen(line), 0);
    sprintf(line, "\r\n");
    send(sock, line, strlen(line), 0);

    sendfile(sock, fd, NULL, size);

    close(fd);

    return 200;
}

void *handerRequest(void* arg)
{
    int sock = *(int*)arg;
    int status_code = 200;
    char line[MAX];
    char method[MAX/16];
    char url[MAX];
    char path[MAX/8];
    int cgi = 0;
    char *query_string = NULL;

    getLine(sock, line, sizeof(line));
    printf("%s",line);
    int i = 0;
    int j = 0;
    //取出方法
    while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j])){
        method[i] = line[j];
        i++,j++;
    }
    method[i] = '\0';

    //取出中间的空格
    while(j < sizeof(line) && isspace(line[j])){
        j++;
    }

    i = 0;
    while(i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j])){
        url[i] = line[j];
        i++,j++;
    }
    url[i] = '\0';

    printf("method is %s, url is %s\n", method, url);

    if(strcasecmp(method, "GET") == 0){
        query_string = url;
        while(*query_string){
            if(*query_string == '?'){
                cgi = 1;
                *query_string = '\0';
                query_string++;
                break;
            }
            ++query_string;
        }
    }else if(strcasecmp(method, "POST") == 0){
        cgi = 1;
    }else{
        status_code = 400;
        clearHead(sock);
        goto end;
    }

    //取出url,写入path
    sprintf(path, "wwwroot%s", url);
    if(path[strlen(path)-1] == '/'){    //仅仅只有根目录，则返回首页
        strcat(path, HOME_PAGE);
    }

    struct stat st;
    if(stat(path, &st) < 0){
        status_code = 404;
        clearHead(sock);
        goto end;
    }
    else{
        if(S_ISDIR(st.st_mode)){
            strcat(path, "/");
            strcat(path, HOME_PAGE);
        }else if((st.st_mode & S_IXUSR) || \
                 (st.st_mode & S_IXGRP) || \
                 (st.st_mode & S_IXOTH)){
            cgi = 1;
        }else{

        }

        //已经拿到了方法，路径url，参数query_string
        if(cgi){
            status_code = exe_cgi(sock, method, path, query_string);
        }else{
            status_code = echo_www(sock, path, st.st_size);
        }
    }
    
    /*else if(strcasecmp(method, "POST") == 0){

    }else{
        //method error
        status_code = 404;
        clearHead(sock);
        goto end;
    }*/

end:
    if(status_code != 200){
        echoErrMsg(sock, status_code);
    }
    close(sock);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        Usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(atoi(argv[1]));
    threadpool_t pool;
    threadpool_init(&pool, 5);
    for( ; ; ){
        struct sockaddr_in client;
        socklen_t len = sizeof(&client);
        int sock = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(sock < 0){
            perror("accept");
            continue;
        }

        int *arg = (int*)malloc(sizeof(sock));
        *arg = sock;
        thread_add_task(&pool, handerRequest, arg);
    }
    threadpool_destroy(&pool);
    return 0;
}
