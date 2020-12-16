#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"comm.h"

int main()
{
    char arg[1024];
    if(getenv("METHOD"))
    {
        if(strcasecmp(getenv("METHOD"), "GET") == 0)
        {
            strcpy(arg, getenv("QUERY_STRING"));
        }
        else
        {
            char c;
            int i = 0;
            int len = atoi(getenv("CONTENT_LENGTH"));
            for(; i < len; ++i)
            {
                read(0, &c, 1);
                arg[i] = 0;
            }
            arg[i] = 0;
        }
    }

    strtok(arg, "=&");
    string name = strtok(NULL, "=&");
    strtok(NULL, "=&");
    string gender = strtok(NULL, "=&");
    strtok(NULL, "=&");
    string hobby = strtok(NULL, "=&");

    MYSQL *myfd = connectMysql();
    insertMysql(myfd, name, gender, hobby);
    closeMysql(myfd);
    return 0;
}

