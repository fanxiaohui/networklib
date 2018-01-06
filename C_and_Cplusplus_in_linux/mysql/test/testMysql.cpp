/*************************************************************************
> File Name: test.cpp
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: Sun 23 Mar 2014 08:44:23 PM CST
************************************************************************/

#include <iostream>
#include <cstdlib>
#include <mysql/mysql.h>

using namespace std;

char const * const db_host = "127.0.0.1"; 
char const * const db_name = "tiankong_site"; 
char const * const db_user = "tiankong_site";
char const * const db_password = "4nMuNnZX";


void mysql_err_function(MYSQL *mysql);      //将错误处理打包成一个函数

int main()
{
    MYSQL *connection;                      //设置连接句柄并初始化
    connection = mysql_init(NULL);
    if (!connection)                        //初始化出错
    {
        cout << "mysql_init failed!" << endl;
        exit(-1);
    }

    if (connection == mysql_real_connect(connection, db_host, db_user, db_password, db_name,0,NULL,0))
    {
        cout << "Connection Success!" << endl;

        string str = "SELECT count(*) num FROM `record_record`";

        int res;
        int affected_count = 0;             //受影响的行数
        res = mysql_query(connection,str.c_str());

        if (!res)
        {
            cout << "select : " << affected_count << " rows" << endl;
        }
        else
        {
            mysql_err_function(connection);
        }

        mysql_close(connection);
        cout << "MySQL Server Closed!" << endl;
    }
    else
    {
        cout << "Connection failed!" << endl;
        mysql_err_function(connection);
    }
}

void mysql_err_function(MYSQL * mysql)
{
    if (mysql_errno(mysql))
    {
        cout << "Error " << mysql_errno(mysql) << ": ";
        cout << mysql_error(mysql) << endl;

        exit(-1);
    }
}
