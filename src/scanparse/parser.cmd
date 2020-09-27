/define YYERROR/a\
#include "parser.fcts"\nvoid yyerror(string s);
/define YYERRCODE/a\
#include "parser.h"
/yynewerror:/d
/++yynerrs;/d
/extern YYSTYPE yylval;/d
