/*************************************************************************
  > File Name: getpid.cpp
  > Author: tiankonguse
  > Mail: i@tiankonguse.com 
  > Created Time: 2014年07月08日 星期二 11时59分04秒
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<apue.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
int main(int argc, char* argv[]) {
    
    printf("hello word from process ID %d\n",getpid());
    

    return 0;
}
