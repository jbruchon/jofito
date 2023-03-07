/*
 * Jody Bruchon's File Tool - tokenizer
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
#include "tokenizer.h"
#include "oom.h"
#include "version.h"


// Token definitions and name list

const char * const restrict token_names[] = {
	"NULL",      // 0x00
	"NUM",       // 0x01
	"VAR",       // 0x02
	"FUNC",      // 0x03
	"CONTROL",   // 0x04
	"ASSIGN",    // 0x05
	"MATH",      // 0x06
	"BITWISE",   // 0x07
	"LOGICAL",   // 0x08
	"COMPARE",   // 0x09
	"STRING",    // 0x0a
	"INDEX",     // 0x0b
	"TYPE",      // 0x0c
	"EOE",       // 0x0d
};


/* Add token to temporary token buffer but don't commit to final output yet */
static void buffer_token(int type, void *data)
{
	fprintf(stderr, "buffer_token: [%s] '%p'\n", token_names[type], data);
	return;
}


int tokenize(char * const line, const int len, const int lineno)
{
	fprintf(stderr, "tokenize: [%d] '%s'\n", len, line);

	for (int pos = 0; pos < len; pos++) {
		char * const cur = line;
		int substart, sublen;

		/* Skip leading spaces and tabs */
		if (cur[pos] == ' ' || cur[pos] == '\t') continue;
		if (cur[pos] == '\0') {
			fprintf(stderr, "internal error: %d,%d: NULL character found (report this as a bug)\n", lineno, pos + 1);
			exit(EXIT_FAILURE);
		}
		/* End of line or semicolon terminates statements */
		if (cur[pos] == '\n' || cur[pos] == '\r' || cur[pos] == ';' || cur[pos] == '\0') { buffer_token(TOK_EOE, NULL); continue; }
		if (cur[pos] == '(') {
			/* Handle subexpressions */
			pos++;
			/* Skip spaces and tabs again */
			while (cur[pos] == ' ' || cur[pos] == '\t') pos++;
			if (cur[pos] == '\0' || cur[pos] == '\r' || cur[pos] == ';' || cur[pos] == ')') {
				fprintf(stderr, "error: %d,%d: left parenthesis but no subexpression\n", lineno, pos + 1);
				exit(EXIT_FAILURE);
			}
			/* Subexpression start - seek until an unquoted right parenthesis appears */
			substart = pos; sublen = 1;
			while (1) {
				while (cur[pos] != '"' && cur[pos] != ')' && cur[pos] != '\0' && cur[pos] != '\r') { pos++; sublen++; }
				/* Skip quoted strings */
				if (cur[pos] == '"') {
					pos++; sublen++;
					while (cur[pos] != '"' && cur[pos] != '\0' && cur[pos] != '\r') { pos++; sublen++; }
				}
				/* End of parenthetical subexpression */
				if (cur[pos] == ')') {
					sublen--;
					tokenize(line + substart, sublen, lineno);
					break;
				}
				if (pos >= len) {
					fprintf(stderr, "error: %d,%d: premature end of subexpression\n", lineno, pos + 1);
					exit(EXIT_FAILURE);
				}
			}
			continue;
		}
		/* Is the symbol a function or variable? */
	}

	return 0;
}
