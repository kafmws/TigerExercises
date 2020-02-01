#include"pch.h"
#include"tokens.h"
#include"errormsg.h"

YYSTYPE yylval;

int yylex(); /* prototype for the lexing function */

string toknames[] = {
"ID", "STRING", "INT", "COMMA", "COLON", "SEMICOLON", "LPAREN",
"RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
"MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
"AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR",
"TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
"VAR", "TYPE"
};

#define tokname(tok) (tok < 257 || tok > 299 ? "BAD_TOKEN" : toknames[tok - 257])

int main(int argc, char **argv) {
    int tok;
    string fname;
    if (argc != 2) { fprintf(stderr, "usage: a.out filename\n"); exit(1); }
    fname = argv[1];
    EM_reset(fname);
    for (;;) {
        tok = yylex();
        if (tok == 0) break;
        switch (tok) {
        case ID: case STRING:
            printf("%10s %4d %s\n", tokname(tok), EM_tokPos, yylval.sval);
            break;
        case INT:
            printf("%10s %4d %d\n", tokname(tok), EM_tokPos, yylval.ival);
            break;
        default:
            printf("%10s %4d\n", tokname(tok), EM_tokPos);
        }
    }
    return 0;
}