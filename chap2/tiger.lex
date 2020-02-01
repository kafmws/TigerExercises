%{
	#include "util.h"
	#include "tokens.h"
	#include "errormsg.h"

	int charPos=1;

	int yywrap(void) {
	 charPos=1;
	 return 1;
	}

	void adjust(void) {
	 EM_tokPos=charPos;
	 charPos+=yyleng;
	}
	
    void passCmt(char *begin);

    char *makeId(char *tok);

    char *escape(char *tok);

%}

escape				n|t|\^([A-Z]|\[|\\|\]|\^|_|\x7F)|(00[0-9])|(0[1-9][0-9])|(1[01][0-9])|(12[0-7])|\"|\\
continue			\\(\n|\t|\f|\x20)+\\

%%

" "						{adjust(); continue;}
\t						{adjust(); continue;}
\n						{adjust(); EM_newline(); continue;}

","						{adjust(); return COMMA;}
":"						{adjust(); return COLON;}
";"						{adjust(); return SEMICOLON;}
"("					{adjust(); return LPAREN;}
")"					{adjust(); return RPAREN;}
"["					{adjust(); return LBRACK;}
"]"					{adjust(); return RBRACK;}
"{"					{adjust(); return LBRACE;}
"}"					{adjust(); return RBRACE;}
"."						{adjust(); return DOT;}
"+"					{adjust(); return PLUS;}
"-"					{adjust(); return MINUS;}
"*"					{adjust(); return TIMES;}
"/"					{adjust(); return DIVIDE;}
"="					{adjust(); return EQ;}
"<>"					{adjust(); return NEQ;}
"<"					{adjust(); return LT;}
"<="					{adjust(); return LE;}
">"					{adjust(); return GT;}
">="					{adjust(); return GE;}
"&"					{adjust(); return AND;}
"|"					{adjust(); return OR;}
":="					{adjust(); return ASSIGN;}

while					{adjust(); return WHILE;}
for					{adjust(); return FOR;}
to						{adjust(); return TO;}
break				{adjust(); return BREAK;}
let					{adjust(); return LET;}
in						{adjust(); return IN;}
end					{adjust(); return END;}
function			{adjust(); return FUNCTION;}
var					{adjust(); return VAR;}
type					{adjust(); return TYPE;}
array				{adjust(); return ARRAY;}
if						{adjust(); return IF;}
then					{adjust(); return THEN;}
else					{adjust(); return ELSE;}
do						{adjust(); return DO;}
of						{adjust(); return OF;}
nil						{adjust(); return NIL;}

\/\*([^\*]|((\*)*[^\*/]))*\*\/			{adjust(); passCmt(yytext); continue; }

[a-zA-Z]([a-zA-Z0-9_])*								{adjust(); yylval.sval = yytext; return ID;}
[0-9]+															{adjust(); yylval.ival=atoi(yytext); return INT;}
\"([^\"\\]|(\\{escape})|{continue})*\"			{adjust(); yylval.sval = escape(yytext); return STRING;}
.																	{adjust(); EM_error(EM_tokPos,"illegal token");}

%%

void passCmt(char *begin) {
	char *end = begin + yyleng;
	while(begin != end){
		if(*begin == '\n') EM_newline();
		begin++;
	}
}

char *makeId(char *tok) {
	return strncpy(malloc(sizeof(char) * (yyleng + 1)), tok, yyleng);
}

char *escape(char *tok) {
	char *str = malloc(sizeof(char) * (yyleng + 1));
	char *re = str;
	char *tokend = tok + yyleng;
	while(tok != tokend){
		if(*tok == '\\'){
			tok++;
			switch(*tok){
				case 'n': *str++ = '\n'; break;
				case 't': *str++ = '\t'; break;
				case '^': 
					tok++;
					*str++ = *tok == 127 ? 127 : (*tok) - 64;
					break;
				case '0':
				case '1':
				{
					int val = (*tok++) - '0';
					val = val * 10 + (*tok++) - '0';
					val = val * 10 + (*tok) - '0';
					*str++ = val;
				} 
					break;
				case '\"':
				case '\\':
					*str++ = *tok;
					break;
				case '\t':
				case '\n':
				case '\f':
				case ' ':
					do { 
						tok++;
					}while(*tok == '\t' || *tok == '\n' || *tok == '\f' || *tok == ' ');
					if(*tok != '\\') fprintf(stderr, "incorrect regular expression at \\f___f\\\n");
					break;
				default: fprintf(stderr, "unexpect escape\n");
			}
			tok++;
		}
		else *str++ = *tok++;
	}
    *str = 0;
	return re;
}