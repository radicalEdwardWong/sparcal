/define YYERROR/a\
void yyerror(string s);\n#include "parser.fcts"
/define YYERRCODE/a\
#include "parser.h"
/yynewerror:/d
/++yynerrs;/d
/extern YYSTYPE yylval;/d
