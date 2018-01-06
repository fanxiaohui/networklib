#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
using namespace std;
typedef long long LL;
#include<stdarg.h>

int sum(int n,...) {
    int i , sum = 0;
    va_list vap;
    va_start(vap , n);    //指向可变参数表中的第一个参数
    for(i = 0 ; i < n ; ++i)
        sum += va_arg(vap , int);    //取出可变参数表中的参数，并修改参数指针vap使其增加以指向表中下一个参数
    va_end(vap);    //把指针vap赋值为0
    return sum;
}
int main(int argc, char* argv[]) {
    int m = sum(3,2,3,4);
    printf("%d\n",m);
    return 0;
}






