#include<cstdio>
#include<cstring>
#include<cstdlib>

struct A{
    char a;
    char aa;
    char aaa;
    char aaaa;
    char aaaaa;
    int b;
    char c;
};

struct B{
    char a;
    char b;
    int c;
};

struct C{
    char a;
    int b;
    double c;
    char d;
};

struct D{
    int a;
}d;

int main(){
    printf("%d\n",sizeof(A));
    printf("%d\n",sizeof(B));
    printf("%d\n",sizeof(C));
   d.a = 0x12345678;//小端
   char* pd = (char*)(&d);
   printf("%X %X %X %X\n",*pd, *(pd+1), *(pd+2), *(pd+3));
  

    A a;
    memset(&a,0,sizeof(a));
    
    a.a = 1;
    char * pa =(char*)(&a);
    
    printf("%X %X %X %X\n",*pa, *(pa+1), *(pa+2), *(pa+3));

   return 0;
}
