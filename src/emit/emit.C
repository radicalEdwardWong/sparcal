/*
 * emit.C
 *
 */

#include <iostream>

#include "../p_tree/p_tree.h"
#include "../symtab/symtab.h"
#include "../ctrl/ctrl.h"

#include "emit.h"

using namespace std;

int VarAtt :: emit(PEmitter emtr) {
	//cout << "VarAtt::emit()" << endl;
	emtr->emit(this);
	return 0;
}

int Symtab :: emit(PEmitter emtr) {
	//cout << "Symtab::emit()" << endl;
	emtr->emit(this);

	// First (i=1) SymtabEntry object is for program name
	for (int i=2; i < next_location; i++) {
		symtab[i] -> emit(emtr);
	}
	return 0;
}

int NumFactor :: emit(PEmitter emtr) {
	//cout << "NumFactor::emit()" << endl;
	emtr->emit(this);
	return 0;
}

int VarAccessFactor :: emit(PEmitter emtr) {
	//cout << "VarAccessFactor::emit()" << endl;
	emtr->emit(this);
	return 0;
}

int Statement :: emit(PEmitter emtr) {
	emtr->emit(this);
	return 0;
}

int EmptyStmt :: emit(PEmitter emtr) {
	//cout << "EmptyStmt::emit()" << endl;
	return 0;
}

int AssignmentStmt :: emit(PEmitter emtr) {
	//cout << "AssignmentStmt::emit()" << endl;
	Statement::emit(emtr);
	expr->emit(emtr);

	emtr->emit(this);
	return 0;
}

int WriteStmt :: emit(PEmitter emtr) {
	//cout << "WriteStmt::emit()" << endl;
	Statement::emit(emtr);
	expr->emit(emtr);
	emtr->emit(this);
	return 0;
}

int StatementSeq :: emit(PEmitter emtr) {
	//cout << "StatementSeq::emit() " << endl;
	PPTreeNode p = this->seq_head;
	while (p) {
		p->emit(emtr);
		p = PStatement(PStatement(p)->get_next());
	}
	return 0;
}

int PTree :: emit(PEmitter emtr) {
	//cout << "PTree::emit() " << endl;
	if (!root) {
		cerr << "PTree::emit - LOGIC ERROR" << endl;
		return 0;
	} else {
		return root->emit(emtr);
	}
}

int Program :: emit(PEmitter emtr) {
	//cout << "Program::emit() " << endl;
	if (block && std_table) {
		emtr->emit(this);

		this->std_table->emit(emtr);

		return 0;
	} else {
		cerr << "Program::emit - LOGIC ERROR" << endl;
		return 0;
	}
}

int Block :: emit(PEmitter emtr) {
	//cout << "Block::emit() " << endl;
	return this->stmt_seq->emit(emtr);
}

#include "sparc_emit.C"
#include "arm_emit.C"
