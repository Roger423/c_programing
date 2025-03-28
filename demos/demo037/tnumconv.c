/* Tests C89 numeric conversion functions */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define CHK_VALID printf("    %s        %s\n", errno != ERANGE ? "Yes" : "No", *ptr == '\0' ? "Yes" : "No")

int main(int argc, char *argv[])
{
    char *ptr;

    if (argc != 2) {
        printf("Usage: tnumconv <number string>\n");
        exit(EXIT_FAILURE);
    }

    printf("Function    Return Value\n");
    printf("--------    ------------\n");
    printf("atof        %g\n", atof(argv[1]));
    printf("atoi        %d\n", atoi(argv[1]));
    printf("atol        %ld\n\n", atol(argv[1]));

    printf("Function    Return Value    Valid?    String Consumed?\n"
           "--------    ------------    ------    ---------------\n");

    errno = 0;
    printf("strtod      %-12g", strtod(argv[1], &ptr));
    CHK_VALID;

    errno = 0;
    printf("strtol      %-12ld", strtol(argv[1], &ptr, 10));
    CHK_VALID;

    errno = 0;
    printf("strtoul      %-12lu", strtoul(argv[1], &ptr, 10));
    CHK_VALID;

    return 0;

}
