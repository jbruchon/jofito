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
#define TOK_ASSIGN   0x03  // equal sign '=' for value assignment
#define TOK_MATH     0x04  // math ops, + - * / % ** (add/sub/mul/div/mod/exp)
#define TOK_BITWISE  0x05  // bitwise ops, AND OR XOR NAND NOR XNOR ROL ROR SHL SHR
#define TOK_LOGICAL  0x06  // logical ops, & | ^ ~ (and/or/xor/not)
#define TOK_COMPARE  0x07  // comparison ops, > < = >= <= =< => == != etc.
#define TOK_LPAREN   0x08  // left parenthesis '('
#define TOK_RPAREN   0x09  // right parenthesis ')'
#define TOK_LQUOTE   0x0a  // opening quote for string: "like this"
#define TOK_RQUOTE   0x0b  // closing quote for string
#define TOK_LBRACKET 0x0c  // left square bracket '['
#define TOK_RBRACKET 0x0d  // right square bracket ']'
#define TOK_TYPE     0x0e  // type specs: string, float, [u]int[size], boolean
#define TOK_EOE      0x0f  // end of expression (unquoted newline or semicolon)
#define TOK_EOF      0x10  // end of program (unconditional exit)

extern const char * const restrict token_names[];
extern int tokenize(char * const line, const int len);

#ifdef __cplusplus
}
#endif

#endif /* JOFITO_TOKENS_H */
