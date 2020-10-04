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
	cout << "	.align 4" << endl;
	cout << "	.common _" << SymtabEntry::name;
	cout << ",4" << endl;
	return 0;
}

int Symtab :: emit() {
	//cout << "Symtab::emit()" << endl;

	cout << "	.bss" << endl;
	// First (i=1) SymtabEntry object is for program name
	for (int i=2; i < next_location; i++) {
		symtab[i] -> emit();
	}
	return 0;
}

int NumFactor :: emit() {
	//cout << "NumFactor::emit()" << endl;
	cout << "	mov	0x" << hex << Expr::value << ",%o0" << endl;
	return 0;
}

int VarAccessFactor :: emit() {
	//cout << "VarAccessFactor::emit()" << endl;
	char *ident_str = PIdent(ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << "),%o0" << endl;
	cout << "	ld	[%o0+%lo(_" ;
		cout << ident_str;
		cout << ")],%o0" << endl;
	return 0;
}

int Statement :: emit() {
	cout << "! " << stmt_text << endl;
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
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << ">,%o1" << endl;
	cout << "	st	%o0,[%1o+%lo(_";
		cout << ident_str;
		cout << ")]" << endl;
	return 0;
}

int WriteStmt :: emit() {
	//cout << "WriteStmt::emit()" << endl;
	Statement::emit();
	expr->emit();
	cout << "	call	_Writeln,1" << endl;
	cout << "	nop" << endl;
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
		cout << "	.text" << endl;
		cout << "	.global _main" << endl << endl;

		cout << "_main:" << endl;
		cout << "	save	%sp,-MINWINDOW,%sp" << endl;

		this->block->emit();

		cout << "	ret" << endl;
		cout << endl;
		cout << "	.data" << endl;
		cout <<	"#define DW(x)	(((x)+7&(~0x07))" << endl;
		cout << "#define MINFRAME ((16+1+6)*4)" << endl;
		cout << "	MINWINDOW = 96 /* DW(MINFRAME) */" << endl;

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
