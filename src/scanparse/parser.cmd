/define YYERROR/a\
#include "parser.fcts"\nvoid yyerror(char* s);
/define YYERRCODE/a\
#include "parser.h"
/yynewerror:/d
/++yynerrs;/d
/extern YYSTYPE yylval;/d
