/*************************************************************************
  > File Name: cp1.cpp
  > Author: tiankonguse
  > Mail: i@tiankonguse.com 
  > Created Time: 2014年07月08日 星期二 11时39分54秒
***********************************************************************/

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<apue.h>

#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

#define BUFFSIZE 4096


int main(int argc, char* argv[]) {

    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
        if(write(STDOUT_FILENO, buf, n) != n){
            err_sys("write error");
        }
    }

    if(n < 0){
        err_sys("read error");
    }

    return 0;
}
