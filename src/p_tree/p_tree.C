/*
 * PTreeNode implementation
 */

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "../scanparse/scanparse.h"
#include "../symtab/symtab.h"

#include "p_tree.h"

class Emitter;

using namespace std;

LstSeqBldr :: LstSeqBldr() {
	//cout << "LstSeqBldr()" << endl;
	next = 0;
}

PLstSeqBldr LstSeqBldr :: append(PLstSeqBldr ToBeAdded) {
	//cout << "LstSeqBldr::append()" << endl;
	return this->next = ToBeAdded;
}

PTreeNode :: PTreeNode() {
	//cout << "PTreeNode" << endl;
	extern LexTok *lex_tok;
	lt = lex_tok;
}

int PTreeNode :: emit(Emitter *emtr) {
	cout << "PTreeNode::emit() BASECLASS !!!!!" << endl;
	return 0;
}

void PTreeNode :: print() {
	cout << "PTreeNode::print() " << " lex_tok " << (lt->token) << endl;
}

IntLiteral :: IntLiteral() {
	//cout << "IntLiteral" << endl;
	value = atoi(this->PTreeNode::lt->get_lexeme());
}

RealLiteral :: RealLiteral() {
	//cout << "RealLiteral" << endl;
	string str = this->PTreeNode::lt->get_lexeme();
	string intDigits = "";
	string decimalDigits = "";
	bool decimalReached = false;
	for (int i = 0; i < str.length(); i++) {
		char c = str[i];
		if ('.' == c) {
			decimalReached = true;
			continue;
		}
		if (decimalReached) {
			decimalDigits += c;
		} else {
			intDigits += c;
		}
	}
	decimalDigits += '\0';
	intDigits += '\0';
	value = new RealNumber(stoi((string)intDigits), stoi((string)decimalDigits));
}

Ident :: Ident() {
	//cout << "Ident" << endl;
	char *name = this->PTreeNode::lt->get_lexeme();

	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	if (!found) {
		PIntVarAtt va = new IntVarAtt(name, 0);
		scp->insert(va);
	}
}

char *Ident :: get_name() {
	//cout << "Ident::get_name()" << endl;
	return this->PTreeNode::lt->get_lexeme();
}

int Expr :: emit(Emitter *emtr) {
	cout << "Expr:emit() BASE CLASS !!!" << endl;
	return 0;
}

IntExpr :: IntExpr() {
	//cout << "IntExpr" << endl;
}

int IntExpr :: evaluate() {
	cout << "IntExpr:evaluate() BASE CLASS !!!" << endl;
	return 0;
}

int IntExpr :: emit(Emitter *emtr) {
	cout << "IntExpr:emit() BASE CLASS !!!" << endl;
	return 0;
}

RealExpr :: RealExpr() {
	//cout << "RealExpr" << endl;
}

PRealNumber RealExpr :: evaluate() {
	cout << "RealExpr:evaluate() BASE CLASS !!!" << endl;
	return 0;
}

int RealExpr :: emit(Emitter *emtr) {
	cout << "RealExpr:emit() BASE CLASS !!!" << endl;
	return 0;
}

IntFactor :: IntFactor(PPTreeNode IntLit) {
	//cout << "IntFacor() " << endl;
	if (!IntLit) {
		cerr << "IntFactor - LOGIC ERROR" << endl;
	}
	IntExpr::value = PIntLiteral(IntLit)->get_value();
	//cout << " value " << Expr::value << endl;
}

int IntFactor :: evaluate() {
	//cout << "IntFactor::evaluate()" << endl;
	return value;
}

RealFactor :: RealFactor(PPTreeNode RealLit) {
	//cout << "RealFacor() " << endl;
	if (!RealLit) {
		cerr << "RealFactor - LOGIC ERROR" << endl;
	}
	RealExpr::value = PRealLiteral(RealLit)->get_value();
	//cout << " value " << Expr::value << endl;
}

PRealNumber RealFactor :: evaluate() {
	//cout << "RealFactor::evaluate()" << endl;
	return value;
}

IntVarAccessFactor :: IntVarAccessFactor(PPTreeNode Ident) {
	//cout << "IntVarAccessFactor() " << endl;
	if (!Ident) {
		cerr << "IntVarAccessFactor() - LOGIC ERROR" << endl;
	}
	ident = Ident;
	char *name = PIdent(ident) -> get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	if (!found) {
		cerr << "	" << *name << " name but not set" << endl;
		PIntVarAtt va = new IntVarAtt(name, 0);
		scp->insert(va);
		IntExpr::value = 0;
	} else {
		IntExpr::value = PIntVarAtt(found)->get_value();
	}
}

int IntVarAccessFactor :: evaluate() {
	//cout << "IntVarAccessFactor::evaluate()" << endl;
	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	return PIntVarAtt(found)->get_value();
}

RealVarAccessFactor :: RealVarAccessFactor(PPTreeNode Ident) {
	//cout << "RealVarAccessFactor() " << endl;
	if (!Ident) {
		cerr << "RealVarAccessFactor() - LOGIC ERROR" << endl;
	}
	ident = Ident;
	char *name = PIdent(ident) -> get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	if (!found) {
		cerr << "	" << *name << " name but not set" << endl;
		PRealNumber realNum = new RealNumber(0, 0);
		PRealVarAtt va = new RealVarAtt(name, realNum);
		scp->insert(va);
		RealExpr::value = realNum;
	} else {
		RealExpr::value = PRealVarAtt(found)->get_value();
	}
}

PRealNumber RealVarAccessFactor :: evaluate() {
	//cout << "RealVarAccessFactor::evaluate()" << endl;
	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	return PRealVarAtt(found)->get_value();
}

Statement :: Statement(char *StmtText) {
	//cout << "Statement()" << endl;
	stmt_text = new char[strlen(StmtText)+1];
	strcpy(stmt_text, StmtText);
}

AssignmentStmt :: AssignmentStmt(
					PPTreeNode Ident,
					PPTreeNode Expr,
					char* TextLine
				) : Statement(TextLine) {
	//cout << "AssignmentStm() " << endl;
	if (!Ident || !Expr) {
		cerr << "AssignmentStmt() - LOGIC ERROR " << endl;
	}
	ident = Ident;
	expr = Expr;
}

WriteStmt :: WriteStmt(PPTreeNode Expr, char *TextLine): Statement(TextLine) {
	//cout << "WriteStmt() " << endl;
	if (!Expr) {
		cerr << "WriteStmt() - LOGIC ERROR " << endl;
	}
	expr = Expr;
}

StatementSeq :: StatementSeq(PPTreeNode Stmt) {
	//cout << "StatementSeq() " << endl;
	seq_tail = seq_head = PStatement(Stmt);
}

PPTreeNode StatementSeq :: append(PPTreeNode Stmt) {
	//cout << "StatementSeq::append()" << endl;
	if (!seq_tail) {
		cerr << "StatementSeq::append() -- LOGIC ERROR" << endl;
	} else {
		seq_tail = PStatement(seq_tail->LstSeqBldr::append(PStatement(Stmt)));
	}
	return this;
}

Block :: Block(PPTreeNode StmtSeq) {
	//cout << "Block" << endl;
	stmt_seq = StmtSeq;
}

extern PPTreeNode prgm_node; //declared in scanparse.C
Program :: Program(PPTreeNode Ident, PPTreeNode Block) {
	//cout << "Program() " << endl;
	ident = PIdent(Ident);
	block = PBlock(Block);
	std_table = Scope::get_visible_symtab();
	prgm_node = this;
}

void Program :: print() {
	cout << "Program::print()" << endl;
}

PTree :: PTree(PPTreeNode Root) {
	//cout << "PTree()" << endl;
	root = current = Root;
}

void PTree :: print() {
	cout << "PTree " << endl;
	root->print();
}
