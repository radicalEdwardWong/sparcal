/*
 * PTreeNode implementation
 */

#include <iostream>
#include <string.h>

#include "../scanparse/scanparse.h"
#include "../symtab/symtab.h"

#include "p_tree.h"

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

int PTreeNode :: emit() {
	cout << "PTreeNode::emit() BASECLASS !!!!!" << endl;
	return 0;
}

int PTreeNode :: execute() {
	cout << "PTreeNode::execute() BASECLASS !!!!!" << endl;
	return 0;
}

void PTreeNode :: print() {
	cout << "PTreeNode::print() " << " lex_tok " << (lt->token) << endl;
}

NumLiteral :: NumLiteral() {
	//cout << "NumLiteral" << endl;
	value = atoi(this->PTreeNode::lt->get_lexeme());
}

Ident :: Ident() {
	//cout << "Ident" << endl;
	char *name = this->PTreeNode::lt->get_lexeme();

	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	if (!found) {
		PVarAtt va = new VarAtt(name, 0);
		scp->insert(va);
	}
}

char *Ident :: get_name() {
	//cout << "Ident::get_name()" << endl;
	return this->PTreeNode::lt->get_lexeme();
}

Expr :: Expr() {
	//cout << "Expr" << endl;
}

int Expr :: evaluate() {
	cout << "Expr:evaluate() BASE CLASS !!!" << endl;
	return 0;
}

int Expr :: emit() {
	cout << "Expr:emit() BASE CLASS !!!" << endl;
	return 0;
}

Factor :: Factor() {
	//cout << "Factor() " << endl;
}

NumFactor :: NumFactor(PPTreeNode NumLit) {
	//cout << "NumFacor() " << endl;
	if (!NumLit) {
		cerr << "NumFactor - LOGIC ERROR" << endl;
	}
	Expr::value = PNumLiteral(NumLit)->get_value();
	//cout << " value " << Expr::value << endl;
}

int NumFactor :: evaluate() {
	//cout << "NumFactor::evaluate()" << endl;
	return Expr::value;
}

int NumFactor :: emit() {
	cout << "NumFactor::emit() BASE CLASS !!!" << endl;
	return 0;
}

VarAccessFactor :: VarAccessFactor(PPTreeNode Ident) {
	//cout << "VarAccessFactor() " << endl;
	if (!Ident) {
		cerr << "VarAccessFactor() - LOGIC ERROR" << endl;
	}
	ident = Ident;
	char *name = PIdent(ident) -> get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	if (!found) {
		cerr << "	" << *name << " name but not set" << endl;
		PVarAtt va = new VarAtt(name, 0);
		scp->insert(va);
		Expr::value = 0;
	} else {
		Expr::value = PVarAtt(found)->get_value();
	}
}

int VarAccessFactor :: evaluate() {
	//cout << "VarAccessFactor::evaluate()" << endl;
	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found = scp->lookup(name);
	return PVarAtt(found)->get_value();
}

int VarAccessFactor :: emit() {
	cout << "VarAccessFactor::emit() BASE CLASS !!!" << endl;
	return 0;
}

Statement :: Statement(char *StmtText) {
	//cout << "Statement()" << endl;
	stmt_text = new char[strlen(StmtText)+1];
	strcpy(stmt_text, StmtText);
}

int Statement :: emit() {
	cout << "Statement:emit() BASE CLASS !!!" << endl;
	return 0;
}

int EmptyStmt :: execute() {
	cout << "EmptyStmt::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int EmptyStmt :: emit() {
	cout << "EmptyStmt:emit() BASE CLASS !!!" << endl;
	return 0;
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

int AssignmentStmt :: execute() {
	cout << "AssignmentStmt::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int AssignmentStmt :: emit() {
	cout << "AssignmentStmt::emit() BASE CLASS !!!" << endl;
	return 0;
}

WriteStmt :: WriteStmt(PPTreeNode Expr, char *TextLine): Statement(TextLine) {
	//cout << "WriteStmt() " << endl;
	if (!Expr) {
		cerr << "WriteStmt() - LOGIC ERROR " << endl;
	}
	expr = Expr;
}

int WriteStmt :: execute() {
	cout << "WriteStmt::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int WriteStmt :: emit() {
	cout << "WriteStmt::emit() BASE CLASS !!!" << endl;
	return 0;
}

StatementSeq :: StatementSeq(PPTreeNode Stmt) {
	//cout << "StatementSeq() " << endl;
	seq_tail = seq_head = PStatement(Stmt);
}

int StatementSeq :: execute() {
	cout << "StatementSeq::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int StatementSeq :: emit() {
	cout << "StatementSeq::emit() BASE CLASS !!!" << endl;
	return 0;
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

int Block :: execute() {
	cout << "Block::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int Block :: emit() {
	cout << "Block::emit() BASE CLASS !!!" << endl;
	return 0;
}

extern PPTreeNode prgm_node; //declared in scanparse.C
Program :: Program(PPTreeNode Ident, PPTreeNode Block) {
	//cout << "Program() " << endl;
	ident = PIdent(Ident);
	block = PBlock(Block);
	std_table = Scope::get_visible_symtab();
	prgm_node = this;
}

int Program :: execute() {
	cout << "Program::execute() BASECLASS !!!!!" << endl;
	return 0;
}

int Program :: emit() {
	cout << "Program::emit() BASE CLASS !!!" << endl;
	return 0;
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

int PTree :: emit() {
	cout << "PTree::emit() BASE CLASS !!!" << endl;
	return 0;
}

int PTree :: execute() {
	cout << "PTree::execute() BASECLASS !!!!!" << endl;
	return 0;
}
