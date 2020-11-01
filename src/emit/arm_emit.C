
void ArmEmitter :: emit(VarAtt *ptnode) {
	cout << "	.align 2" << endl;
	cout << "	_" << ptnode->name << ":" << endl;
	cout << "	.space 4" << endl << endl;
}

void ArmEmitter :: emit(Symtab *ptnode) {
	cout << endl << ".bss" << endl << endl;
}

void ArmEmitter :: emit(NumFactor *ptnode) {
	cout << "	mov r0, #" << ptnode->value << endl;
}

void ArmEmitter :: emit(VarAccessFactor *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	ldr r0,=" << ident_str << endl;
}

void ArmEmitter :: emit(Statement *ptnode) {
	cout << endl << "/* " << ptnode->stmt_text << " */" << endl;
}

void ArmEmitter :: emit(AssignmentStmt *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	str r0,=" << ident_str << endl;
}

void ArmEmitter :: emit(WriteStmt *ptnode) {
	cout << "	bl _Writeln" << endl;
}

void ArmEmitter :: emit(Program *ptnode) {
	cout << "	bl _Writeln" << endl;
	cout << ".text" << endl << endl;
	cout << "	.globl main" << endl;
	cout << "	.arch arm" << endl;
	cout << "	.type	main, %function" << endl;
	cout << "main:" << endl;
	cout << "	push {lr}" << endl;

	ptnode->block->emit(this);

	cout << "	pop {pc}" << endl;
}
