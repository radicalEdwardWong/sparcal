
void SparcEmitter :: emit(VarAtt *ptnode) {
	cout << "	.align 4" << endl;
	cout << "	.common _" << ptnode->name;
	cout << ",4" << endl;
}

void SparcEmitter :: emit(Symtab *ptnode) {
	cout << "	.bss" << endl;
}

void SparcEmitter :: emit(NumFactor *ptnode) {
	cout << "	mov	0x" << hex << ptnode->value << ",%o0" << endl;
}

void SparcEmitter :: emit(VarAccessFactor *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << "),%o0" << endl;
	cout << "	ld	[%o0+%lo(_" ;
		cout << ident_str;
		cout << ")],%o0" << endl;
}

void SparcEmitter :: emit(Statement *ptnode) {
	cout << "! " << ptnode->stmt_text << endl;
}

void SparcEmitter :: emit(AssignmentStmt *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << ">,%o1" << endl;
	cout << "	st	%o0,[%1o+%lo(_";
		cout << ident_str;
		cout << ")]" << endl;
}

void SparcEmitter :: emit(WriteStmt *ptnode) {
	cout << "	call	_Writeln,1" << endl;
	cout << "	nop" << endl;
}

void SparcEmitter :: emit(Program *ptnode) {
	cout << "	.text" << endl;
	cout << "	.global _main" << endl << endl;

	cout << "_main:" << endl;
	cout << "	save	%sp,-MINWINDOW,%sp" << endl;

	ptnode->block->emit(this);

	cout << "	ret" << endl;
	cout << endl;
	cout << "	.data" << endl;
	cout <<	"#define DW(x)	(((x)+7&(~0x07))" << endl;
	cout << "#define MINFRAME ((16+1+6)*4)" << endl;
	cout << "	MINWINDOW = 96 /* DW(MINFRAME) */" << endl;
}
