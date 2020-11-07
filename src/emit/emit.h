/*
 * Emitter Definition
 */

typedef class Emitter *PEmitter;
class Emitter {
	public:
		virtual void emit(IntVarAtt *ptnode) {;}
		virtual void emit(RealVarAtt *ptnode) {;}
		virtual void emit(Symtab *ptnode) {;}
		virtual void emit(IntFactor *ptnode) {;}
		virtual void emit(RealFactor *ptnode) {;}
		virtual void emit(IntVarAccessFactor *ptnode) {;}
		virtual void emit(RealVarAccessFactor *ptnode) {;}
		virtual void emit(Statement *ptnode) {;}
		virtual void emit(IntAssignmentStmt *ptnode) {;}
		virtual void emit(RealAssignmentStmt *ptnode) {;}
		virtual void emit(WriteStmt *ptnode) {;}
		virtual void emit(Program *ptnode) {;}
};
class SparcEmitter : public Emitter {
	public:
		SparcEmitter () {;}
		void emit(IntVarAtt *ptnode);
		void emit(RealVarAtt *ptnode);
		void emit(Symtab *ptnode);
		void emit(IntFactor *ptnode);
		void emit(RealFactor *ptnode);
		void emit(IntVarAccessFactor *ptnode);
		void emit(RealVarAccessFactor *ptnode);
		void emit(Statement *ptnode);
		void emit(IntAssignmentStmt *ptnode);
		void emit(RealAssignmentStmt *ptnode);
		void emit(WriteStmt *ptnode);
		void emit(Program *ptnode);
};
class ArmEmitter : public Emitter {
	public:
		ArmEmitter () {;}
		void emit(IntVarAtt *ptnode);
		void emit(RealVarAtt *ptnode);
		void emit(Symtab *ptnode);
		void emit(IntFactor *ptnode);
		void emit(RealFactor *ptnode);
		void emit(IntVarAccessFactor *ptnode);
		void emit(RealVarAccessFactor *ptnode);
		void emit(Statement *ptnode);
		void emit(IntAssignmentStmt *ptnode);
		void emit(RealAssignmentStmt *ptnode);
		void emit(WriteStmt *ptnode);
		void emit(Program *ptnode);
};
