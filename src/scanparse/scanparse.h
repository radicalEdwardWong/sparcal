/*
 * LexTok Definition
 */

typedef class LexTok *PLexTok;
class LexTok {
	public:
		LexTok(int LineNo, int Token, char *Lexeme);
		char* get_lexeme() {return lexeme;}
	public:
		int line_no;
		char *lexeme;
		int token;
};


class PTree;

typedef class ScanParse *PScanParse;
class ScanParse {
	public:
		ScanParse();
		void print();
		friend class Controller;
	private:
		PTree *parse_tree;
};
