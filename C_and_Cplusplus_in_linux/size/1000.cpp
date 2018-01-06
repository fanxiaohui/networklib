#include <cstdio>
#include <cstdlib>

int onetoth(int n){
    printf("%d ",n);
    (1000-n) && onetoth(n+1);
    return 0;
}

void yesprint(int i);
void noprint(int i);

typedef void(*fnPtr) (int);
fnPtr dispatch[] = { yesprint, noprint };

void yesprint(int i) {
    printf("%d\n", i);
    dispatch[i / 1000](i + 1);
}

void noprint(int i) {  }


int main(){
//    onetoth(1);

yesprint(1);

    return 0;
}
