/*
 * p_tree.h
 */

class LexTok;
class Symtab;
class Emitter;
class SparcEmitter;
class ArmEmitter;

typedef class PTreeNode *PPTreeNode;
class PTreeNode {
	public:
		PTreeNode();
		virtual int emit(Emitter *emtr);
		virtual int execute();
		virtual void print();
		virtual LexTok *get_let_tok() {return lt;}
	protected:
		LexTok *lt;
};

typedef class NumLiteral *PNumLiteral;
class NumLiteral : public PTreeNode {
	public:
		NumLiteral(){;}
};

typedef class IntLiteral *PIntLiteral;
class IntLiteral : public NumLiteral {
	public:
		IntLiteral();
		int get_value() {return value;}
	private:
		int value;
};

typedef class RealNumber *PRealNumber;
class RealNumber {
	public:
		RealNumber() {;}
		RealNumber(int Int, int Decimal) {
			integer = Int;
			decimal = Decimal;
		}
		int integer;
		int decimal;
};

typedef class RealLiteral *PRealLiteral;
class RealLiteral : public NumLiteral {
	public:
		RealLiteral();
		PRealNumber get_value() { return value; }
	private:
		PRealNumber value;
};

typedef class Ident *PIdent;
class Ident : public PTreeNode {
	public:
		Ident();
		char *get_name();
};

typedef class Expr *PExpr;
class Expr : public PTreeNode {
	public:
		Expr() {;}
		virtual int emit(Emitter *emtr);
};

typedef class IntExpr *PIntExpr;
class IntExpr : public PTreeNode {
	public:
		IntExpr();
		friend class SparcEmitter;
		friend class ArmEmitter;
		virtual int emit(Emitter *emtr);
		virtual int evaluate();
	protected:
		int value;
};

typedef class RealExpr *PRealExpr;
class RealExpr : public PTreeNode {
	public:
		RealExpr();
		friend class SparcEmitter;
		friend class ArmEmitter;
		virtual int emit(Emitter *emtr);
		virtual PRealNumber evaluate();
	protected:
		PRealNumber value;
};

typedef class IntFactor *PIntFactor;
class IntFactor : public IntExpr {
	public:
		IntFactor() {;}
		IntFactor(PPTreeNode IntLit);
		friend class SparcEmitter;
		friend class ArmEmitter;
		int evaluate();
		int emit(Emitter *emtr);
};

typedef class RealFactor *PRealFactor;
class RealFactor : public RealExpr {
	public:
		RealFactor() {;}
		RealFactor(PPTreeNode RealLit);
		friend class SparcEmitter;
		friend class ArmEmitter;
		PRealNumber evaluate();
		int emit(Emitter *emtr);
};

typedef class IntVarAccessFactor *PIntVarAccessFactor;
class IntVarAccessFactor : public IntFactor {
	public:
		IntVarAccessFactor() {;}
		IntVarAccessFactor(PPTreeNode Ident);
		friend class SparcEmitter;
		friend class ArmEmitter;
		int evaluate();
		int emit(Emitter *emtr);
	private:
		PPTreeNode ident;
};

typedef class RealVarAccessFactor *PRealVarAccessFactor;
class RealVarAccessFactor : public RealFactor {
	public:
		RealVarAccessFactor() {;}
		RealVarAccessFactor(PPTreeNode Ident);
		friend class SparcEmitter;
		friend class ArmEmitter;
		PRealNumber evaluate();
		int emit(Emitter *emtr);
	private:
		PPTreeNode ident;
};

typedef class LstSeqBldr *PLstSeqBldr;
class LstSeqBldr {
	public:
		LstSeqBldr();
		virtual PLstSeqBldr append(PLstSeqBldr);
		virtual PLstSeqBldr get_next() {return next;}
	private:
		PLstSeqBldr next;
};

typedef class Statement *PStatement;
class Statement : public PTreeNode, public LstSeqBldr {
	public:
		Statement() {;}
		Statement(char *StmtText);
		friend class SparcEmitter;
		friend class ArmEmitter;
		int emit(Emitter *emtr);
		int execute();
	protected:
		char *stmt_text;
};

typedef class EmptyStmt *PEmptyStmt;
class EmptyStmt : public Statement {
	public:
		EmptyStmt() {;}
		int emit(Emitter *emtr);
		int execute();
};

typedef class AssignmentStmt *PAssignmentStmt;
class AssignmentStmt : public Statement {
	public:
		AssignmentStmt() {;}
		AssignmentStmt(PPTreeNode ident,
						PPTreeNode Expr,
						char *stmtText
					);
		PPTreeNode ident; // left-hand side
		PPTreeNode expr; // right-hand side
};

typedef class IntAssignmentStmt *PIntAssignmentStmt;
class IntAssignmentStmt : public AssignmentStmt {
	public:
		IntAssignmentStmt() {;}
		IntAssignmentStmt(PPTreeNode ident,
						PPTreeNode Expr,
						char *stmtText
					) : AssignmentStmt(ident,
						Expr,
						stmtText) {}
		friend class SparcEmitter;
		friend class ArmEmitter;
		int emit(Emitter *emtr);
		int execute();
};

typedef class RealAssignmentStmt *PRealAssignmentStmt;
class RealAssignmentStmt : public AssignmentStmt {
	public:
		RealAssignmentStmt() {;}
		RealAssignmentStmt(PPTreeNode ident,
						PPTreeNode Expr,
						char *stmtText
					) : AssignmentStmt(ident,
						Expr,
						stmtText) {}
		friend class SparcEmitter;
		friend class ArmEmitter;
		int emit(Emitter *emtr);
		int execute();
};

typedef class WriteStmt *PWriteStmt;
class WriteStmt : public Statement {
	public:
		WriteStmt() {;}
		WriteStmt(PPTreeNode Expr, char* StmtText);
		int emit(Emitter *emtr);
		virtual int execute();
	protected:
		PPTreeNode expr;
};

typedef class IntWriteStmt *PIntWriteStmt;
class IntWriteStmt : public WriteStmt {
	public:
		IntWriteStmt() {;}
		IntWriteStmt(PPTreeNode Expr, char* StmtText) : WriteStmt(Expr, StmtText) {}
		int execute();
};

typedef class RealWriteStmt *PRealWriteStmt;
class RealWriteStmt : public WriteStmt {
	public:
		RealWriteStmt() {;}
		RealWriteStmt(PPTreeNode Expr, char* StmtText) : WriteStmt(Expr, StmtText) {}
		int execute();
};

typedef class StatementSeq *PStatementSeq;
class StatementSeq : public PTreeNode {
	public:
		StatementSeq() {;}
		StatementSeq(PPTreeNode Stmt);
		int execute();
		int emit(Emitter *emtr);
		PPTreeNode append(PPTreeNode);
	private:
		Statement *seq_head;
		Statement *seq_tail;
};

typedef class Block *PBlock;
class Block : public PTreeNode {
	public:
		Block() {;}
		Block(PPTreeNode StmtSeq);
		int execute();
		int emit(Emitter *emtr);
	private:
		PPTreeNode stmt_seq;
};

typedef class Program *PProgram;
class Program : public PTreeNode {
	public:
		Program() {;}
		Program(PPTreeNode Ident, PPTreeNode Block);
		friend class SparcEmitter;
		friend class ArmEmitter;
		int execute();
		int emit(Emitter *emtr);
		void print();
	private:
		Symtab *std_table;
		PIdent ident;
		PPTreeNode block;
};

typedef class PTree *PPTree;
class PTree {
	public:
		PTree(PPTreeNode Root);
		int execute();
		int emit(Emitter *emtr);
		void print();
	private:
		PPTreeNode root;
		PPTreeNode current;
};
