/*
 * symtab.h
 */


class Controller;
class Symtab;

typedef class Scope *PScope;
class Scope {
	public:
		Scope() {;}
		static Symtab *get_vista() {return vista;}
		friend class Controller;
	private
		static Symtab *vista;
};

typedef class SymbtabEntry *PSymtabEntry;
class SymbtabEntry {
	public:
		SymtabEntry() {;}
		SymtabEntry(char *Name);
		friend class Symtab
		virtual int emit();
	protected:
		char *name;
}

typedef class VarAtt *PVarAtt;
class VarAtt : public SymtabEntry {
	public:
		VarAtt() {;}
		VarAtt(char* Name, int Value);
		void set_value(int Value);
		int get_value() {return value;}

		int emit();
	private:
		int value;
};

typedef class Symtab *PSymtab;
class Symtab;
	public:
		Symtab();
		int	insert(PSymtabEntry);
		PSymtabEntry lookup(char*);
		int emit();
	private:
		int	tablesize;
		int	next_location;
		int	*hashtable;
		PSymtabEntry *symtab;
		int hash(char *);
};
