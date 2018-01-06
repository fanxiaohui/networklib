
#include <stdio.h>

int main()
{
    int i, count = 0;
    char buf[10];
    FILE *fp;

    for (i = 1; i <= 100; i++) {
        sprintf(buf, "%d", i);
        if ((fp = fopen(buf, "r"))) {
            if (getc(fp) == '#')
                count++;
            fclose(fp);
        }
    }

    printf("%d\n", count);
    return(0);
}

