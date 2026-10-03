CC     := gcc
CFLAGS := -Wall -Wextra

.PHONY: all static shared clean

# ---- Target User  ----
all: main_static main_shared

static: main_static

shared: main_shared

clean:
	rm -f *.o libstrutils.a libstrutils.so main_static main_shared

# ---- Static ----
strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -c strutils.c -o $@

libstrutils.a: strutils.o
	ar rcs $@ $^

main_static: main.c strutils.h libstrutils.a
	$(CC) $(CFLAGS) main.c libstrutils.a -o $@

# ---- Shared ----
strutils_pic.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -fPIC -c strutils.c -o $@

libstrutils.so: strutils_pic.o
	$(CC) -shared -o $@ $^

main_shared: main.c strutils.h libstrutils.so
	$(CC) $(CFLAGS) main.c -L. -lstrutils -o $@