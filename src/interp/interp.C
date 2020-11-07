/*
 * interp.C
 *
 */

#include <iostream>

#include "../p_tree/p_tree.h"
#include "../symtab/symtab.h"

using namespace std;

int PTreeNode :: execute() {
	cout << "PTreeNode::execute() BASE CLASS!!!" << endl;
	return 0;
}

int Statement :: execute() {
	cout << "Statement::execute() BASE CLASS!!!" << endl;
	return 0;
}

int EmptyStmt :: execute() {
	//cout << "EmptyStmt::execute()" << endl;
	return 0;
}

int IntAssignmentStmt :: execute() {
	//cout << "IntAssignmentStmt::execute() " << endl;

	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found_it = scp->lookup(name);
	if (!found_it) {
		// TODO: delegate to Error class
		cout << "IntAssignmentStmt::execute() LOGIC ERROR" << endl;
	} else {
		int rval = PIntExpr(expr)->evaluate();
		PIntVarAtt(found_it)->set_value(rval);
	}
	return 0;
}

int RealAssignmentStmt :: execute() {
	//cout << "RealAssignmentStmt::execute() " << endl;

	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found_it = scp->lookup(name);
	if (!found_it) {
		// TODO: delegate to Error class
		cout << "RealAssignmentStmt::execute() LOGIC ERROR" << endl;
	} else {
		RealNumber *rval = PRealExpr(expr)->evaluate();
		PRealVarAtt(found_it)->set_value(rval);
	}
	return 0;
}

int WriteStmt :: execute() {
	cout << "WriteStmt::execute() BASE CLASS !!!" << endl;
	return 0;
}

int IntWriteStmt :: execute() {
	//cout << "IntWriteStmt::execute() " << expr << endl;
	cout << "   -> " << PIntExpr(expr) -> evaluate() << endl;
	return 0;
}

int RealWriteStmt :: execute() {
	//cout << "RealWriteStmt::execute() " << expr << endl;
	PRealNumber real = PRealExpr(expr) -> evaluate();
	cout << "   -> " << real->integer << "." << real->decimal << endl;
	return 0;
}

int StatementSeq :: execute() {
	//cout << "StatementSeq::execute() " << endl;
	PPTreeNode p = this->seq_head;
	while (p) {
		p->execute();
		p = PStatement(PStatement(p)->get_next());
	}
	return 0;
}

int Block :: execute() {
	//cout << "Block::execute() " endl;
	return this->stmt_seq->execute();
}

int Program :: execute() {
	//cout << "Block::execute() " << endl;
	return this->block->execute();
}

int PTree :: execute() {
	//cout << "PTree::execute() " << endl;
	if (!root) {
		cerr << "PTree::execute - LOGIC ERROR" << endl;
		return 0;
	} else {
		return root->execute();
	}
}
