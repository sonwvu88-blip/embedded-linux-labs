#include <stdio.h>
#include <stdlib.h>

/* One table row: region | name | address | note */
#define ROW(region, name, ptr, note) \
    printf("| %-6s | %-30s | %-14p | %-32s |\n", \
           (region), (name), (void *)(ptr), (note))

static void print_sep(void)
{
    printf("+--------+--------------------------------+"
           "----------------+----------------------------------+\n");
}

static void print_header(void)
{
    print_sep();
    printf("| %-6s | %-30s | %-14s | %-32s |\n",
           "Region", "Name", "Address", "Note");
    print_sep();
}

/* ---- File-scope variables ---- */
int g_init = 100;                /* global, initialized            */
int g_uninit;                    /* global, uninitialized          */
int g_zero = 0;                  /* global, initialized to zero    */
static int s_init = 200;         /* file-static, initialized       */
static int s_uninit;             /* file-static, uninitialized     */
const int g_const = 300;         /* global const                   */
const char *g_str = "hello";     /* global pointer + string literal */
char g_buf[4096];                /* large global array, uninitialized */

static void func_a(void)
{
    static int call_count = 7;   /* local static, initialized      */
    static int call_zero;        /* local static, uninitialized    */
    int local_a = 0;             /* ordinary local variable        */
    char note[48];

    call_count++;
    snprintf(note, sizeof(note), "call #%d (value %d)",
             call_count - 7, call_count);

    ROW("DATA",  "&call_count (local static)", &call_count, note);
    ROW("BSS",   "&call_zero (local static)",  &call_zero,  "local static, zero");
    ROW("STACK", "&local_a (plain local)",     &local_a,    "plain local variable");
}

static void recurse(int depth)
{
    int x = depth;
    char name[48];

    snprintf(name, sizeof(name), "&x (recursion depth %d)", depth);
    ROW("STACK", name, &x, "one stack frame per call");

    if (depth < 3)
        recurse(depth + 1);
}


int main(void)
{
    int local_init = 1;
    int local_uninit;            /* only its address is used, never its value */
    char local_arr[16] = "stack";
    int *p1 = malloc(16);
    int *p2 = malloc(16);

    if (p1 == NULL || p2 == NULL) {
        free(p1);
        free(p2);
        return 1;
    }

    print_header();

    /* TEXT / RODATA */
    ROW("TEXT",   "main",                 main,     "machine code");
    ROW("TEXT",   "func_a",               func_a,   "machine code");
    ROW("RODATA", "&g_const",             &g_const, "global const");
    ROW("RODATA", "g_str (\"hello\")",    g_str,    "string literal");
    print_sep();

    /* DATA */
    ROW("DATA",   "&g_init",              &g_init,  "global, initialized");
    ROW("DATA",   "&s_init",              &s_init,  "file-static, initialized");
    ROW("DATA",   "&g_str",               &g_str,   "pointer variable itself");
    print_sep();

    /* BSS */
    ROW("BSS",    "&g_uninit",            &g_uninit, "global, uninitialized");
    ROW("BSS",    "&g_zero",              &g_zero,   "global, initialized to 0");
    ROW("BSS",    "&s_uninit",            &s_uninit, "file-static, uninitialized");
    ROW("BSS",    "g_buf",                g_buf,     "global array, 4096 bytes");
    print_sep();

    /* HEAP */
    ROW("HEAP",   "p1",                   p1,        "malloc(16)");
    ROW("HEAP",   "p2",                   p2,        "malloc(16)");
    print_sep();

    /* STACK */
    ROW("STACK",  "&local_init",          &local_init,   "local, initialized");
    ROW("STACK",  "&local_uninit",        &local_uninit, "local, uninitialized");
    ROW("STACK",  "local_arr",            local_arr,     "local array, 16 bytes");
    ROW("STACK",  "&p1",                  &p1,           "pointer variable p1");
    ROW("STACK",  "&p2",                  &p2,           "pointer variable p2");
    print_sep();

    /* Local statics: called twice to show the value persists */
    func_a();
    func_a();
    print_sep();

    /* Stack growth */
    recurse(1);
    print_sep();

    free(p1);
    free(p2);
    return 0;
}
