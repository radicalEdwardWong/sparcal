/*
 * p_tree.h
 */

class LexTok;
class Symtab;

typedef class PTreeNode *PPTreeNode;
class PTreeNode {
	public:
		PTreeNode();
		virtual int emit();
		virtual int execute();
		virtual void print();
		virtual LexTok *get_let_tok() {return lt;}
	protected:
		LexTok *lt;
};

typedef class NumLiteral *PNumLiteral;
class NumLiteral : public PTreeNode {
	public:
		NumLiteral();
		int get_value() {return value;}
	private:
		int value;
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
		Expr();
		virtual int evaluate();
		virtual int emit();
	protected:
		int value;
};

typedef class Factor *PFactor;
class Factor : public Expr {
	public:
		Factor();
};

typedef class NumFactor *PNumFactor;
class NumFactor : public Factor {
	public:
		NumFactor(PPTreeNode NumLit);
		int evaluate();
		int emit();
};

typedef class VarAccessFactor *PVarAccessFactor;
class VarAccessFactor : public Factor {
	public:
		VarAccessFactor(PPTreeNode Ident);
		int evaluate();
		int emit();
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
		int emit();
	protected:
		char *stmt_text;
};

typedef class EmptyStmt *PEmptyStmt;
class EmptyStmt : public Statement {
	public:
		EmptyStmt() {;}
		int execute();
		int emit();
};

typedef class AssignmentStmt *PAssignmentStmt;
class AssignmentStmt : public Statement {
	public:
		AssignmentStmt() {;}
		AssignmentStmt(PPTreeNode ident,
						PPTreeNode Expr,
						char *stmtText);
		int execute();
		int emit();
	private:
		PPTreeNode ident; // left-hand side
		PPTreeNode expr; // right-hand side
};

typedef class WriteStmt *PWriteStmt;
class WriteStmt : public Statement {
	public:
		WriteStmt() {;}
		WriteStmt(PPTreeNode Expr, char* StmtText);
		int execute();
		int emit();
	private:
		PPTreeNode expr;
};

typedef class StatementSeq *PStatementSeq;
class StatementSeq : public PTreeNode {
	public:
		StatementSeq() {;}
		StatementSeq(PPTreeNode Stmt);
		int execute();
		int emit();
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
		int emit();
	private:
		PPTreeNode stmt_seq;
};

typedef class Program *PProgram;
class Program : public PTreeNode {
	public:
		Program() {;}
		Program(PPTreeNode Ident, PPTreeNode Block);
		int execute();
		int emit();
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
		int emit();
		void print();
	private:
		PPTreeNode root;
		PPTreeNode current;
};
