/* jofito token definitions and names
 * See LICENSE for license information */

#ifndef JOFITO_TOKENS_H
#define JOFITO_TOKENS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Token type to number definitions */
#define TOK_NULL     0x00  // not a real token
#define TOK_NUM      0x01  // numeric value (incl. hexadecimal with 0x prefix)
#define TOK_VAR      0x02  // variable
#define TOK_FUNC     0x03  // function call
#define TOK_CONTROL  0x04  // reserved control words (if then fi while do done goto return switch case continue break)
#define TOK_ASSIGN   0x05  // equal sign '=' for value assignment
#define TOK_MATH     0x06  // math ops, + - * / % ** (add/sub/mul/div/mod/exp)
#define TOK_BITWISE  0x07  // bitwise ops, AND OR XOR NAND NOR XNOR ROL ROR SHL SHR
#define TOK_LOGICAL  0x08  // logical ops, & | ^ ~ (and/or/xor/not)
#define TOK_COMPARE  0x09  // comparison ops, > < = >= <= =< => == != etc.
#define TOK_STRING   0x0a  // opening quote for string: "like this"
#define TOK_INDEX    0x0b  // right parenthesis ')'
#define TOK_TYPE     0x0c  // type specs: string, float, [u]int[size], boolean
#define TOK_EOE      0x0d  // end of expression (unquoted newline or semicolon)

extern const char * const restrict token_names[];
extern int tokenize(char * const line, const int len, const int lineno);

#ifdef __cplusplus
}
#endif

#endif /* JOFITO_TOKENS_H */
