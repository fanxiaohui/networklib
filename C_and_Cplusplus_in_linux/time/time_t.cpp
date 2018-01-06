/*************************************************************************
    > File Name: time_t.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Fri 14 Mar 2014 11:17:27 PM CST
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

int main(){
    time_t biggest = 0x7fffffff;
    printf("biggest = %s \n", ctime(&biggest));
    printf("biggest = %s \n", asctime(gmtime(&biggest)));
    return 0;
}

