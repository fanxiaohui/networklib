/*
 * WARNING: Do not run this while cd'd to the directory containing the
 * executable itself!
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    DIR *dp = opendir(".");
    struct dirent *r;

    if (dp == NULL) {
	perror(".");
	return(1);
    }
    while ((r = readdir(dp))) {
	if (strcmp(r->d_name, ".") && strcmp(r->d_name, "..")) {
	    switch (fork()) {
	    case -1:
		perror("fork");
		return(1);
	    case 0:  /* I am the child */
		execl(r->d_name, r->d_name, (char *)NULL);
		perror(r->d_name);
		return(127);
	    /* else I am the parent, so loop */
	    }
	}
    }
    return(0);
}
