/*************************************************************************
> File Name: mydb.h
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: Sun 13 Apr 2014 01:06:18 AM CST
***********************************************************************/

#ifndef __MY_DB_H

#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
class CMyDB{
    public:
    CMyDB();
    bool initDB(string server_host , string user, string password, string db_name);
    bool executeSQL(string sql_str);
    bool create_table(string table_str_sql);
    ~CMyDB();
    private:
    MYSQL *connection;
    MYSQL_RES *res;
    MYSQL_ROW row;
};
#endif

