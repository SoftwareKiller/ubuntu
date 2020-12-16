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
            strcpy(arg,getenv("QUERY_STRING"));
        }else{
            char c;
            int i = 0;
            int len = atoi(getenv("CONTENT_LENGTH"));
            for(; i < len; ++i)
            {
                read(0, &c, 1);
                arg[i] = c;
            }
            arg[i] = 0;
        }
    }

    strtok(arg,"=&");
    string name = strtok(NULL, "=&");
    strtok(NULL,"=&");
    string std_id = strtok(NULL, "=&");
    MYSQL *myfd = connectMysql();
    selectMysql(myfd, name, std_id);
    closeMysql(myfd);
    return 0;
}
