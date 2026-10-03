#include "strutils.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void str_reverse(char *s)
{
    

    if (s == NULL) return;

    size_t len = strlen(s);
    if (len < 2) return;

    size_t i = 0, j = len - 1;
    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

void str_trim(char *s)
{
    if (s == NULL) return;

    char *start = s;
    while (*start != '\0' && isspace((unsigned char)*start))
        start++;

    if (*start == '\0') {          /* empty string or space */
        s[0] = '\0';
        return;
    }

    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';

    if (start != s)                /* move context to beginning */
        memmove(s, start, (size_t)(end - start) + 2);  /* +2: gồm cả '\0' */
}

int str_to_int(const char *s, int *out)
{
    if (s == NULL || out == NULL) return -1;

    char *endptr;
    errno = 0;
    long v = strtol(s, &endptr, 10);

    if (endptr == s) return -1;                 /* no numbers */

    while (isspace((unsigned char)*endptr))     /* allow space */
        endptr++;
    if (*endptr != '\0') return -1;             /* trash char, ex "12abc" */

    if (errno == ERANGE || v > INT_MAX || v < INT_MIN)
        return -1;                              /* overflow number */

    *out = (int)v;
    return 0;
}
