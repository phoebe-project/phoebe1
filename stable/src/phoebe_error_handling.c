#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

int phoebe_notice (const char *fmt, ...)
	{
	va_list ap;
	int r;

	printf ("PHOEBE notice: ");
	va_start (ap, fmt);
	r = vprintf (fmt, ap);
	va_end (ap);

	return r;
	}

int phoebe_warning (const char *fmt, ...)
	{
	va_list ap;
	int r;

	printf ("PHOEBE warning: ");
	va_start (ap, fmt);
	r = vprintf (fmt, ap);
	va_end (ap);

	return r;
	}

int phoebe_debug (const char *fmt, ...)
	{
	/* This function writes the message to stdout in case PHOEBE was compiled   */
	/* with --enable-debug switch, otherwise it just returns control to the ma- */
	/* in program.                                                              */

	va_list ap;
	int r = -1;

	#ifdef PHOEBE_DEBUG_SUPPORT
		printf ("PHOEBE debug: ");
		va_start (ap, fmt);
		r = vprintf (fmt, ap);
		va_end (ap);
	#endif

	return r;
	}

int phoebe_fatal (const char *fmt, ...)
	{
	va_list ap;

	printf ("PHOEBE fatal: ");
	va_start (ap, fmt);
	vprintf (fmt, ap);
	va_end (ap);

	exit (EXIT_FAILURE);
	}

void *phoebe_malloc (size_t size)
	{
	register void *value = malloc (size);
	if (value == 0) phoebe_fatal ("Virtual memory exhauseted.\n");
	return value;
	}

void *phoebe_realloc (void *ptr, size_t size)
	{
	register void *value = realloc (ptr, size);
	if (value == 0) phoebe_fatal ("Virtual memory exhauseted.\n");
	return value;
	}

void script_warning (char *message)
	{
	printf ("\nPHOEBE script warning: %s\n", message);
	}
