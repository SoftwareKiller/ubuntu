#include"comm.h"

MYSQL* connectMysql()
{
    MYSQL* myfd = mysql_init(NULL);
    if(mysql_real_connect(myfd, "localhost","zym","","test", 3306, NULL, 0) == NULL)
    {
        cerr<<"connect error"<<endl;
    }else
    {
        cout<<"connect success"<<endl;
    }
    return myfd;
}

int insertMysql(MYSQL* myfd, const string& name, const string& gender, const string& hobby)
{
    string sql = "INSERT INTO stdtab (name, gender, hobby) VALUES (\"";
    sql += name;
    sql += "\",\"";
    sql += gender;
    sql += "\",\"";
    sql += hobby;
    sql += "\")";

    cout << sql << endl;
    return mysql_query(myfd, sql.c_str());
}

void selectMysql(MYSQL* myfd)
{
    string sql = "SELECT * FROM stdtab";
    mysql_query(myfd, sql.c_str());
    MYSQL_RES* result = mysql_store_result(myfd);
    int lines = mysql_num_rows(result);
    int cols = mysql_num_fields(result);
    cout << "<table border=\"1\">" << endl;
    MYSQL_FIELD *field = mysql_fetch_fields(result);
    int i = 0;
    cout << "<tr>" << endl;
    for(; i < cols; ++i)
    {
        cout << "<th>" << field[i].name << "</th>";
    }
    cout<< "</tr>" << endl;

    for(i=0; i < lines; ++i)
    {
        cout << "<tr>" << endl;
        MYSQL_ROW line = mysql_fetch_row(result);
        int j = 0;
        for(; j < cols; ++j)
        {
            cout << "<td>" << line[j] << "</td>";
        }
        cout << "</tr" << endl;
    }
    cout << "</table>" << endl;
    free(result);
}

void closeMysql(MYSQL* myfd)
{
    mysql_close(myfd);
}

