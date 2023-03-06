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
	"ASSIGN",    // 0x03
	"MATH",      // 0x04
	"BITWISE",   // 0x05
	"LOGICAL",   // 0x06
	"COMPARE",   // 0x07
	"LPAREN",    // 0x08
	"RPAREN",    // 0x09
	"LQUOTE",    // 0x0a
	"RQUOTE",    // 0x0b
	"LBRACKET",  // 0x0c
	"RBRACKET",  // 0x0d
	"TYPE",      // 0x0e
	"EOE",       // 0x0f
	"EOF"        // 0x10
};


int tokenize(char * const line, const int len)
{
	char * const cur = line;

	fprintf(stderr, "interpret_line: [%d] '%s'\n", len, line);
	return 0;
}
