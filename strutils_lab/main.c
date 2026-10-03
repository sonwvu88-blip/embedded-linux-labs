#include <stdio.h>
#include <string.h>
#include "strutils.h"

static void test_reverse(const char *input)
{
    char buf[64];
    strncpy(buf, input, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    str_reverse(buf);
    printf("  reverse(\"%s\") -> \"%s\"\n", input, buf);
}

static void test_trim(const char *input)
{
    char buf[64];
    strncpy(buf, input, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    str_trim(buf);
    printf("  trim(\"%s\") -> \"%s\"\n", input, buf);
}

static void test_to_int(const char *input)
{
    int val = 0;
    int rc = str_to_int(input, &val);
    if (rc == 0)
        printf("  to_int(\"%s\") -> OK, %d\n", input, val);
    else
        printf("  to_int(\"%s\") -> ERROR (invalid input)\n", input);
}

int main(void)
{
    printf("== str_reverse ==\n");
    test_reverse("hello");        /* normal */
    test_reverse("abcd");         /* even length */
    test_reverse("a");            /* 1 char */
    test_reverse("");             /* empty */

    printf("== str_trim ==\n");
    test_trim("   hello world  ");  /* normal */
    test_trim("hello");             /* no space */
    test_trim("     ");             /* space */
    test_trim("");                  /* empty */

    printf("== str_to_int ==\n");
    test_to_int("123");            /* normal */
    test_to_int("-45");            /* negative number */
    test_to_int("  7  ");          /* there space */
    test_to_int("2147483647");     /* INT_MAX */
    test_to_int("-2147483648");    /*  INT_MIN */
    test_to_int("2147483648");     /* overflow */
    test_to_int("abc");            /* error: no number */
    test_to_int("12abc");          /* error: trash char */
    test_to_int("");               /* error: empty */

    int dummy;
    printf("  to_int(NULL) -> %s\n",
           str_to_int(NULL, &dummy) == -1 ? "ERROR (Correct)" : "False");

    return 0;
}
