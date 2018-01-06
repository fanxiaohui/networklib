#include<cstdio>
#include<cstdlib>
int main(int argc, char**argv) {
    printf("%d\n", argc);
    argc ^100 && main(argc+1,NULL);
    return 0;
}
