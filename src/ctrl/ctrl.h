/*
 * Option Definition
 */

typedef class Option *POption;
class Option {
	public:
		friend class Controller;
		static int option_info();
		static bool isArmMode() { return arm != 0; }
	private:
		Option();
		static int list;
		static int emit;
		static int arm;
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
