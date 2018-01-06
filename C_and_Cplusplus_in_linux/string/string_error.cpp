/*************************************************************************
> File Name: code.cpp
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: Sun 16 Mar 2014 06:39:06 PM CST
************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test(){
    string str="";
    
    printf("str length = %d \n",str.length());
    str[0] = '1';
    str[1] = '\0';
    printf("str length = %d \n",str.length());

    printf("-------------test end----------\n");
}

int main()
{

    test();

    

    string a;
    string e[10];
    int i, j;
    int k, l;
    freopen("test.txt","r",stdin);
    cin >> k;

    while(k--)
    {
        //init;
        for(i = 0; i < 10; i++)
        e[i] = "\0";

        cin >> a;
        l = a.length();
        j = 0;

        cout << "a:" << a<<endl;
        for(i = 0; i < l; i++)
        {
            if(i / 6 > j)
            {
                e[j][6] = '\0';
                j++;
                cout <<"j++"<<endl;
                cout <<"j :"<<j << endl;
            }
            e[j][i%6] = a[i];
            cout << "e[" << j << "]" << "[" << i%6 << "]:" << e[j][i%6] <<"    ";
            cout << "e[0][0]:" << e[0][0] << endl;
            cout << "e:" << e[0] << endl;
        }

        cout <<"devide group complete" << endl;

        for(i = 0; i< 5; i++)
        {
            cout << e[1][i];
        }
        cout << endl;
        for(i = 0; i< 5; i++)
        {
            cout << e[0][i];
        }
        cout << endl;
        for(i = 0; i <= j; i++)
        {
            cout << e[i] << endl;
        }
    }
    return 0;
}
