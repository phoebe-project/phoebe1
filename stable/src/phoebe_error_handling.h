#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int phoebe_notice (const char *fmt, ...);
int phoebe_warning (const char *fmt, ...);
int phoebe_debug (const char *fmt, ...);
int phoebe_fatal (const char *fmt, ...);

void *phoebe_malloc (size_t size);
void *phoebe_realloc (void *ptr, size_t size);
void script_warning (char *message);
