/*
 * interp.C
 *
 */

#include <iostream>

#include "../p_tree/p_tree.h"
#include "../symtab/symtab.h"

using namespace std;

class AssignmentStmt;

int EmptyStmt :: execute() {
	//cout << "EmptyStmt::execute()" << endl;
	return 0;
}

int AssignmentStmt :: execute() {
	//cout << "AssignmentStmt::execute() " << endl;
	int rval = PExpr(expr)->evaluate();

	char *name = PIdent(ident)->get_name();
	PSymtab scp = Scope::get_visible_symtab();
	PSymtabEntry found_it = scp->lookup(name);
	if (!found_it) {
		// TODO: delegate to Error class
		cout << "AssignmentStmt::execute() LOGIC ERROR" << endl;
	} else {
		PVarAtt(found_it)->set_value(rval);
	}
	return 0;
}

int WriteStmt :: execute() {
	//cout << "WriteStmt::execute() " << expr << endl;
	cout << "   -> " << PExpr(expr) -> evaluate() << endl;
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
