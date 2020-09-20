
/*
 * ScanParse and LexTok implementation
 */

// header
#include <iostream>
#include "../p_tree/p_tree.h"
#include "scanparse.h"
// end header

#include <string.h>
LexTok :: LexTok(int LineNo, int Token, char *Lexeme) {
	//cout << "LexTok(LineNo, Token, Lexeme)" << endl;
	line_no = LineNo;
	token = Token;
	lexeme = new char[80];
	if (Lexeme) {
		strcpy(lexeme, Lexeme);
	}
}
// end LexTok implementation

PPTreeNode prgm_node; // Gloabl! Set by top of tree Program

#include "scanparse.fct"

ScanParse :: ScanParse() {
	//cout << "SanParse()" << endl;
	yyparse();
	parse_tree = new PTree(prgm_node);
}
// end ScanParse implementation
