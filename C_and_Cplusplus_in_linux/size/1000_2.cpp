#include<cstdio>

class Printer{
public:
    Printer() { static unsigned i=1; printf("%d\n",i++);}
};

int main(){
    Printer p[1000];
    return 0;
}
