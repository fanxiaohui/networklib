/*************************************************************************
  > File Name: cp2.cpp
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

    int c;
    while((c = getc(stdin)) != EOF){
        if(putc(c, stdout) == EOF){
            err_sys("output error");
        }
    }

    if(ferror(stdin)){
        err_sys("input error");
    }

    return 0;
}
