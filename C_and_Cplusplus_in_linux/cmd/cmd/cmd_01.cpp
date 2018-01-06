#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int play( char *filename ) {
    char command[256];
    int status;  /* create command to execute */
    sprintf( command, "%s", filename );  /* play sound */
    status = system(command );
    printf("status=%d\n",status);
    return status;
}
int main( int argc, char *argv[] ) {
    char command[256];
    while(gets(command)){
        play( command);
    }

    return 0;
}

