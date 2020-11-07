
void SparcEmitter :: emit(IntVarAtt *ptnode) {
	cout << "	.align 4" << endl;
	cout << "	.common _" << ptnode->name;
	cout << ",4" << endl;
}

void SparcEmitter :: emit(RealVarAtt *ptnode) {
	cout << "	.align 4" << endl;
	cout << "	.common _" << (string)ptnode->name + "0";
	cout << ",4" << endl;
	cout << "	.common _" << (string)ptnode->name + "1";
	cout << ",4" << endl;
}

void SparcEmitter :: emit(Symtab *ptnode) {
	cout << "	.bss" << endl;
}

void SparcEmitter :: emit(IntFactor *ptnode) {
	cout << "	mov	0x" << hex << ptnode->value << ",%o0" << endl;
}

void SparcEmitter :: emit(RealFactor *ptnode) {
	cout << "! real literal implemented simply as a pair of integer/decimal values" << endl;
	cout << "	mov	0x" << hex << ptnode->value->integer<< ",%o0" << endl;
	cout << "	mov	0x" << hex << ptnode->value->decimal<< ",%o1" << endl;
}

void SparcEmitter :: emit(IntVarAccessFactor *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << "),%o0" << endl;
	cout << "	ld	[%o0+%lo(_" ;
		cout << ident_str;
		cout << ")],%o0" << endl;
}

void SparcEmitter :: emit(RealVarAccessFactor *ptnode) {
	string ident_str = (string)PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str + "0";
		cout << "),%o0" << endl;
	cout << "	ld	[%o0+%lo(_" ;
		cout << ident_str + "0";
		cout << ")],%o0" << endl;
	cout << "	sethi	%hi(_" ;
		cout << ident_str + "1";
		cout << "),%o1" << endl;
	cout << "	ld	[%o1+%lo(_" ;
		cout << ident_str + "1";
		cout << ")],%o1" << endl;
}

void SparcEmitter :: emit(Statement *ptnode) {
	cout << "! " << ptnode->stmt_text << endl;
}

void SparcEmitter :: emit(IntAssignmentStmt *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << ">,%o1" << endl;
	cout << "	st	%o0,[%1o+%lo(_";
		cout << ident_str;
		cout << ")]" << endl;
}

void SparcEmitter :: emit(RealAssignmentStmt *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << ">,%o1" << endl;
	cout << "	st	%o0,[%1o+%lo(_";
		cout << ident_str;
		cout << ")]" << endl;
	cout << "	sethi	%hi(_" ;
		cout << ident_str;
		cout << ">,%o1" << endl;
	cout << "	st	%o1,[%1o+%lo(_";
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
