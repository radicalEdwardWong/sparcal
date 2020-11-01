/*
 * Emitter Definition
 */

typedef class Emitter *PEmitter;
class Emitter {
	public:
		virtual void emit(VarAtt *ptnode) {;}
		virtual void emit(Symtab *ptnode) {;}
		virtual void emit(NumFactor *ptnode) {;}
		virtual void emit(VarAccessFactor *ptnode) {;}
		virtual void emit(Statement *ptnode) {;}
		virtual void emit(AssignmentStmt *ptnode) {;}
		virtual void emit(WriteStmt *ptnode) {;}
		virtual void emit(Program *ptnode) {;}
};
class SparcEmitter : public Emitter {
	public:
		SparcEmitter () {;}
		void emit(VarAtt *ptnode);
		void emit(Symtab *ptnode);
		void emit(NumFactor *ptnode);
		void emit(VarAccessFactor *ptnode);
		void emit(Statement *ptnode);
		void emit(AssignmentStmt *ptnode);
		void emit(WriteStmt *ptnode);
		void emit(Program *ptnode);
};
class ArmEmitter : public Emitter {
	public:
		ArmEmitter () {;}
		void emit(VarAtt *ptnode);
		void emit(Symtab *ptnode);
		void emit(NumFactor *ptnode);
		void emit(VarAccessFactor *ptnode);
		void emit(Statement *ptnode);
		void emit(AssignmentStmt *ptnode);
		void emit(WriteStmt *ptnode);
		void emit(Program *ptnode);
};
