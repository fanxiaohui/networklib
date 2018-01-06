/*************************************************************************
  > File Name: cgi.cpp
  > Author: tiankonguse
  > Mail: i@tiankonguse.com 
  > Created Time: Mon 21 Apr 2014 02:42:02 AM CST
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
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
int main(int argc, char** argv) {
    for(int i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    return 0;
}
