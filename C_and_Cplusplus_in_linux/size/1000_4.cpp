#include<cstdio>

int _nine_print(int,int,int);

int _print(int i,int base) {
    base /= 10;
    base^0 && _nine_print(i,base,0);
    base^0 || printf("%d\n",i);    
    return 1;
}

int _nine_print(int i,int base, int lev){
    lev^10 && _print(i+lev*base,base) && _nine_print(i,base,lev+1);
    return 1;
}

int main() {
    _print(1,1000);
    return 0;
}
