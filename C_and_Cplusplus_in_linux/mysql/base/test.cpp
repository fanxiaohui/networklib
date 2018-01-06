/*************************************************************************
> File Name: main.cpp
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: Sun 13 Apr 2014 01:07:57 AM CST
***********************************************************************/
#include "mydb.h"
int main(int argc,char **argv)
{
    CMyDB my;
    my.initDB("localhost" , "tiankong_site", "4nMuNnZX" , "tiankong_site" );
    return 0;
}


