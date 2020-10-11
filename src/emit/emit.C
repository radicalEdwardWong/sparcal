/*
 * emit.C
 *
 */

#include <iostream>

#include "../p_tree/p_tree.h"
#include "../symtab/symtab.h"

using namespace std;

int VarAtt :: emit() {
	//cout << "VarAtt::emit()" << endl;
	cout << "	.align 2" << endl;
	cout << "	_" << SymtabEntry::name << ":" << endl;
	cout << "	.space 4" << endl << endl;
	return 0;
}

int Symtab :: emit() {
	//cout << "Symtab::emit()" << endl;

	cout << endl << ".section .bss" << endl << endl;
	// First (i=1) SymtabEntry object is for program name
	for (int i=2; i < next_location; i++) {
		symtab[i] -> emit();
	}
	return 0;
}

int NumFactor :: emit() {
	//cout << "NumFactor::emit()" << endl;
	cout << "	mov r0, #" << Expr::value << endl;
	return 0;
}

int VarAccessFactor :: emit() {
	//cout << "VarAccessFactor::emit()" << endl;
	char *ident_str = PIdent(ident)->get_name();
	cout << "	ldr r0,=" << ident_str << endl;
	return 0;
}

int Statement :: emit() {
	cout << endl << "/* " << stmt_text << " */" << endl;
	return 0;
}

int EmptyStmt :: emit() {
	//cout << "EmptyStmt::emit()" << endl;
	return 0;
}

int AssignmentStmt :: emit() {
	//cout << "AssignmentStmt::emit()" << endl;
	Statement::emit();
	expr->emit();

	char *ident_str = PIdent(ident)->get_name();
	cout << "	str r0,=" << ident_str << endl;
	return 0;
}

int WriteStmt :: emit() {
	//cout << "WriteStmt::emit()" << endl;
	Statement::emit();
	expr->emit();
	cout << "	bl _Writeln" << endl;
	return 0;
}

int StatementSeq :: emit() {
	//cout << "StatementSeq::emit() " << endl;
	PPTreeNode p = this->seq_head;
	while (p) {
		p->emit();
		p = PStatement(PStatement(p)->get_next());
	}
	return 0;
}

int PTree :: emit() {
	//cout << "PTree::emit() " << endl;
	if (!root) {
		cerr << "PTree::emit - LOGIC ERROR" << endl;
		return 0;
	} else {
		return root->emit();
	}
}

int Program :: emit() {
	//cout << "Program::emit() " << endl;
	if (block && std_table) {
		cout << ".section .text" << endl << endl;
		cout << "	.globl main" << endl;
		cout << "	.arch arm" << endl;
		cout << "	.type	main, %function" << endl;
		cout << "main:" << endl;
		cout << "	push {lr}" << endl;

		this->block->emit();

		cout << "	pop {pc}" << endl;

		this->std_table->emit();

		return 0;
	} else {
		cerr << "Program::emit - LOGIC ERROR" << endl;
		return 0;
	}
}

int Block :: emit() {
	//cout << "Block::emit() " << endl;
	return this->stmt_seq->emit();
}
