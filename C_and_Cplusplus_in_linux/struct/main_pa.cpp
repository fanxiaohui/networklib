#include<cstdio>

int main(int argc, char** argv, char**env){
    printf("%d\n\n",argc);

    for(int i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }


    for(int i=0;i<10;i++){
        printf("%s\n",env[i]);
    
    }

    return 0;
}


