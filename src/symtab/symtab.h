/*
 * symtab.h
 */

class Controller;
class Emitter;
class SparcEmitter;
class ArmEmitter;
class RealNumber;

typedef class SymtabEntry *PSymtabEntry;
class SymtabEntry {
	public:
		SymtabEntry() {;}
		SymtabEntry(char *Name);
		friend class SparcEmitter;
		friend class ArmEmitter;
		friend class Symtab;
		virtual int emit(Emitter *emtr);
	protected:
		char *name;
};

typedef class Symtab *PSymtab;
class Symtab {
	public:
		Symtab();
		int	insert(PSymtabEntry);
		PSymtabEntry lookup(char *);
		int emit(Emitter *emtr);
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

typedef class IntVarAtt *PIntVarAtt;
class IntVarAtt : public SymtabEntry {
	public:
		IntVarAtt(char* Name, int Value);
		void set_value(int Value) {value = Value;}
		int get_value() {return value;}
		int emit(Emitter *emtr);
	private:
		int value;
};

typedef class RealVarAtt *PRealVarAtt;
class RealVarAtt : public SymtabEntry {
	public:
		RealVarAtt(char* Name, RealNumber *Value);
		void set_value(RealNumber *Value) {value = Value;}
		RealNumber *get_value() {return value;}
		int emit(Emitter *emtr);
	private:
		RealNumber *value;
};
