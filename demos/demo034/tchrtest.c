/* Tests the character-classification functions */

#include <stdio.h>
#include <ctype.h>

#define TEST(f) printf("   %c ", f(*p) ? 'x' : ' ')

int main(void)
{
    char *p;

    printf("        alnum  cntrl  graph  print  space  xdigit  alpha  digit  lower  punct  upper\n");
    printf("------------------------------------------------------------------------------------\n");
    for (p = "azAZ0 !\t"; *p != '\0'; p++) {
        if (iscntrl(*p))
            printf("\\x%02x :", *p);
        else
            printf("   %c :", *p);
        TEST(isalnum);
        TEST(isalpha);
        TEST(isdigit);
        TEST(isgraph);
        TEST(islower);
        TEST(isprint);
        TEST(ispunct);
        TEST(isspace);
        TEST(isupper);
        TEST(isxdigit);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------\n");

    return 0;
}

