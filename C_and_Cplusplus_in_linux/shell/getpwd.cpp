/*************************************************************************
    > File Name: test.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Fri 07 Mar 2014 03:06:29 PM CST
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include <unistd.h>
using namespace std;
const int MAXPATH = 1000;
int main(int argc, char**argv, char**env){
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    printf("%s", buffer);
    printf("/");
    printf("%s\n",__FILE__);
}
