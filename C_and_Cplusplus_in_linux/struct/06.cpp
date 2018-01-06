#include<cstdio>
 
//sizeof的研究
 
struct MyClass_One{
    char a;
    int b;
};
 
 
struct MyClass_Two{
    int a;
    int b;
};
 
 
struct MyClass_Three{
    char a;
    char b;
};
 
struct MyClass_Four{
    char a;
    char b;
    char c;
};
struct MyClass_Five{
    char a;
    char b;
    char c,d;
};
struct MyClass_Six{
    char a;
    char b;
	short f;
    char c,d,e;
};
 
int main() {
    printf("MyClass_One = %d\n",sizeof(MyClass_One));// 输出的是8
    printf("MyClass_Two = %d\n",sizeof(MyClass_Two));// 输出的是8
    printf("MyClass_Three = %d\n",sizeof(MyClass_Three));// 输出的是8
    printf("MyClass_Four = %d\n",sizeof(MyClass_Four));// 输出的是8
    printf("MyClass_Five = %d\n",sizeof(MyClass_Five));// 输出的是8
    printf("MyClass_Six = %d\n",sizeof(MyClass_Six));// 输出的是8
 
    //想说的是结构体里存在字节对齐，一般情况下是按4字节对齐
 
 
    //对于字符串数组，sizeof 求出的是数组的全部内存大小
    char str1[100] = "abcd";
    printf("str1=%d\n",sizeof(str1));//输出的是 100
 
    //猜想： 对于数组,sizeof 测得是数组的全部内存大小
    int str2[100];
    printf("str2=%d\n",sizeof(str2));//400
 
    //验证猜想：上面猜想正确
    MyClass_One str3[100];
    printf("str3=%d\n",sizeof(str3));//800
 
 
    return 0;
}
