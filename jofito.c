/*
 * Jody Bruchon's File Tool
 * Copyright (C) 2023 by Jody Bruchon <jody@jodybruchon.com>
 * See LICENSE for licensing information
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include "jofito.h"
#include "oom.h"
#include "version.h"

/* Detect Windows and modify as needed */
#if defined _WIN32 || defined __CYGWIN__
 #define ON_WINDOWS 1
 #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
 #endif
 #include <windows.h>
 #include <io.h>
#endif

void show_version(void)
{
	fprintf(stderr, "Jody Bruchon's File Tool %s (%s)\n", VER, VERDATE);
	return;
}

int main(int argc, char **argv)
{
	printf("Nothing is here yet!\n");
	show_version();
	exit(EXIT_FAILURE);
}
