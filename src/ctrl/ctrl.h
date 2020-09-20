/*
 * Option Definition
 */

typedef class Option *POption;
class Option {
	public:
		static int option_info();
		friend class Controller;
	private:
		Option();
		static int list;
		static int emit;
};


class Symtab;
class PTree;


typedef class Controller *PController;
class Controller {
	public:
		Controller(int argc, char** argv);
		void print();
	private:
		Symtab *std_table;
		PTree *parse_tree;
		int open_file(char*);
};
