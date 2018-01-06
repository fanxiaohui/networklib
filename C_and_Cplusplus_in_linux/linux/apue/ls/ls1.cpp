/*************************************************************************
  > File Name: ls1.cpp
  > Author: tiankonguse
  > Mail: i@tiankonguse.com 
  > Created Time: 2014年07月08日 星期二 11时23分27秒
***********************************************************************/

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include"apue.h"
#include <dirent.h>

#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
int main(int argc, char* argv[]) {
    
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2){
        err_quit("usage: ls directory_name");
    }

    if((dp = opendir(argv[1])) == NULL){
        err_sys("can't open %s", argv[1]);
    }

    while((dirp = readdir(dp)) != NULL){
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);

    return 0;
}
