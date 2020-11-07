
void ArmEmitter :: emit(IntVarAtt *ptnode) {
	cout << "	.align 2" << endl;
	cout << "	_" << ptnode->name << ":" << endl;
	cout << "	.space 4" << endl << endl;
}

void ArmEmitter :: emit(RealVarAtt *ptnode) {
	cout << "	.align 2" << endl;
	cout << "	_" << (string)ptnode->name + "_int" << ":" << endl;
	cout << "	.space 4" << endl << endl;
	cout << "	_" << (string)ptnode->name + "_dec" << ":" << endl;
	cout << "	.space 4" << endl << endl;
}

void ArmEmitter :: emit(Symtab *ptnode) {
	cout << endl << ".bss" << endl << endl;
}

void ArmEmitter :: emit(IntFactor *ptnode) {
	cout << "	mov r0, #" << ptnode->value << endl;
}

void ArmEmitter :: emit(RealFactor *ptnode) {
	cout << "/* real literal implemented simply as a pair of integer/decimal values */" << endl;
	cout << "	mov r0, #" << ptnode->value->integer << endl;
	cout << "	mov r1, #" << ptnode->value->decimal << endl;
}

void ArmEmitter :: emit(IntVarAccessFactor *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	ldr r0,=" << ident_str << endl;
}

void ArmEmitter :: emit(RealVarAccessFactor *ptnode) {
	string ident_str = (string)PIdent(ptnode->ident)->get_name();
	cout << "	ldr r0,=" << ident_str + "_int" << endl;
	cout << "	ldr r1,=" << ident_str + "_dec" << endl;
}

void ArmEmitter :: emit(Statement *ptnode) {
	cout << endl << "/* " << ptnode->stmt_text << " */" << endl;
}

void ArmEmitter :: emit(IntAssignmentStmt *ptnode) {
	char *ident_str = PIdent(ptnode->ident)->get_name();
	cout << "	str r0,=" << ident_str << endl;
}

void ArmEmitter :: emit(RealAssignmentStmt *ptnode) {
	string ident_str = (string)PIdent(ptnode->ident)->get_name();
	cout << "	str r0,=" << ident_str + "_int" << endl;
	cout << "	str r1,=" << ident_str + "_dec" << endl;
}

void ArmEmitter :: emit(WriteStmt *ptnode) {
	cout << "	bl _Writeln" << endl;
}

void ArmEmitter :: emit(Program *ptnode) {
	cout << ".text" << endl << endl;
	cout << "	.globl main" << endl;
	cout << "	.arch arm" << endl;
	cout << "	.type	main, %function" << endl;
	cout << "main:" << endl;
	cout << "	push {lr}" << endl;

	ptnode->block->emit(this);

	cout << "	pop {pc}" << endl;
}
