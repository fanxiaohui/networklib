#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int x = fork();
    if (x == 0) {
        /* child */
        int fd = open("file", O_WRONLY|O_CREAT|O_TRUNC, 0666);
        close(1);
        dup(fd);
        close(fd);
        execl("/bin/ls", "ls", (char *)NULL);
        perror("/bin/ls");
        return(1);
    } else {
        /* parent */
        int status;
        wait(&status);
        printf("Still here, although not for long\n");
        return(0);
    }
}
