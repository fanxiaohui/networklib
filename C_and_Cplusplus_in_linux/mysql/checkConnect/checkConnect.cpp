/*************************************************************************
> File Name:  dbMonitor.cpp 
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: Sun 13 Apr 2014 01:11:05 AM CST
> g++ dbMonitor.cpp -lpthread -lz -o dbMonitor
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<time.h>
#include <mysql/mysql.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const char* host = "127.0.0.1";
const char* user = "tiankong_site";
const char* password = "4nMuNnZX";
const char* db = "tiankong_site";

void reboot(){
    time_t t = time(NULL); 
    int ret = system("sudo reboot");
    if(ret != 0){
        printf("system run error. %s\n",ctime(&t));
    }
}


int main() {
    time_t t = time(NULL); 
    MYSQL *connection;
    connection = mysql_init(NULL);
    if(connection == NULL) {
        printf("mysql init error %s\n", ctime(&t));
        sleep(5);
        if(mysql_init(NULL) == NULL){
            reboot();
        }
    }else{
        connection = mysql_real_connect(connection , host , user , password , db , 0 , NULL , 0);
        if(connection == NULL){
            printf("mysql connect error %s\n",ctime(&t));
            reboot();
        }else{
            printf("mysql connect success %s\n",ctime(&t));
        }
    }

    if(connection != NULL){
        mysql_close(connection);
    }

    return 0;
}
