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

#define MAX_LINE 512

/* This holds the tokenized version of the code */
char *tok_prog = NULL;


void show_version(void)
{
	printf("Jody Bruchon's File Tool %s (%s)\n", VER, VERDATE);
	printf("This program is pre-alpha and not currently useful.\n");
	printf("Latest code available at https://github.com/jbruchon/jofito\n");
	return;
}


void do_help(void)
{
	printf("There is no help text available yet.\n");
	return;
}


int interpret_line(char *line, int len)
{
	return 0;
}

#ifdef UNICODE
int wmain(int argc, wchar_t **wargv)
#else
int main(int argc, char **argv)
#endif
{
	int len = 0;
	char line[MAX_LINE];

	line[MAX_LINE - 1] = '\0';

	show_version();

	while (1) {
		if (!fgets(line, MAX_LINE, stdin)) {
			fprintf(stderr, "Error reading stdin\n");
			exit(EXIT_FAILURE);
		}
		len = strlen(line);
		/* Process line */
		if (line[len-1] == '\n') {
			len--;
			line[len] = '\0';
		}
		if (len == 0) continue;
		if (!strncmp(line, "quit", MAX_LINE) || !strncmp(line, "exit", MAX_LINE)) break;
		else if (!strncmp(line, "help", MAX_LINE)) do_help();
		else interpret_line(line, len);
	}
	exit(EXIT_SUCCESS);
}
