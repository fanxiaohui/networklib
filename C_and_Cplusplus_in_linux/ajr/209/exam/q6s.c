#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *ifp, *ofp;
    int c;

    if (argc != 3) {
	fprintf(stderr, "usage: %s fromfile tofile\n", argv[0]);
	return(1);
    }

    if ((ifp = fopen(argv[1], "r")) == NULL) {
	perror(argv[1]);
	return(1);
    }
    if ((ofp = fopen(argv[2], "w")) == NULL) {
	perror(argv[2]);
	return(1);
    }

    while ((c = getc(ifp)) != EOF)
	putc(c, ofp);

    return(0);
}
