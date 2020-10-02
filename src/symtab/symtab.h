/*
 * symtab.h
 */

class Controller;

typedef class SymtabEntry *PSymtabEntry;
class SymtabEntry {
	public:
		SymtabEntry() {;}
		SymtabEntry(char *Name);
		friend class Symtab;
		virtual int emit();
	protected:
		char *name;
};

typedef class Symtab *PSymtab;
class Symtab {
	public:
		Symtab();
		int	insert(PSymtabEntry);
		PSymtabEntry lookup(char *);
		int emit();
	private:
		int	tablesize;
		int	next_location;
		int	*hashtable;
		PSymtabEntry *symtab;
		int hash(char *);
};

typedef class Scope *PScope;
class Scope {
	friend class Controller;
	public:
		Scope() {;}
		static Symtab *get_visible_symtab() {return visible_symtab;}
	private:
		static Symtab *visible_symtab;
};

typedef class VarAtt *PVarAtt;
class VarAtt : public SymtabEntry {
	public:
		VarAtt() {;}
		VarAtt(char* Name, int Value);
		void set_value(int Value) {value = Value;}
		int get_value() {return value;}
		int emit();
	private:
		int value;
};
