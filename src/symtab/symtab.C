/*
 * symtab.C
 */
#include <iostream>
#include <string.h>

#include "symtab.h"
/* end of header */

Symtab :: Symtab() {
	//cout << "Symtab::()"<< endl;
	tablesize = 17; // Must be a prime for good performance
	hashtable = new int[tablesize];
	next_location = 1; // sacrifice 0th spot - hashtable empty:NIL
	symtab = new PSymtabEntry[tablesize]; // global!!
	PSymtabEntry tmp = new SymtabEntry((char *)"    ");
	for (int i = 0; i < tablesize; i++) {
		hashtable[i] = 0;
		symtab[i] = tmp;
	}
}

int Symtab :: hash(char *s) {
	//cout << "Symtab :: hashing fo " << s;
	char* ss = s;
	unsigned int h = 0, g;
	for (; *ss != '\0'; ss++) {
		h = (h << 4) + *ss;
		if (g = h & 0xf0000000) {
			h ^= g >> 24; // fold top 4 bits onto ------X-
			h ^= g; // clear top 4 bits
		}
	}
	//cout << "hashing to " << h % tablesize << endl;
	return h % tablesize;
}

int Symtab :: insert (PSymtabEntry info) {
	//cout << "Symtab :: insert()" << endl;
	// Return 0 if insert successful; else location in symtab.

	// Look for open slot in the hashtable
	int Try, hash_try; // 'tr' can be a reserved word
	char *Name = info->name;
	//cout << "preparing to enter" << Name << endl;
	Try = hash(Name);
	//cout << "preparing to go into hash table at " < Try << endl;

	while (hash_try = hashtable[Try]) { // have something
		// Check to see if it's he same thing we wan to insert
		if (!strcmp((symtab[hash_try]->name), Name)) {
			return hash_try; // it's already there!
		} else if (++Try >= tablesize) {
			// resolve collision by looking for open spot
			Try = 0; // Wrap around
		}

	}

	hashtable[Try] = next_location;
	//cout << "entered current location in table " << Try << endl;
	symtab[next_location++] = info;
	return 0; // success!
}

PSymtabEntry Symtab :: lookup(char *Name) {
	//cout << "Symtab :: lookup for " << Name ;
	int cur_table_size = tablesize;
	int Try, orig_try, hash_try;

	orig_try = Try = hash(Name);
//cout << "orig_try " << orig_try << "\n";
	hash_try = hashtable[Try];
//cout << "hash_try " << hash_try << endl;
	while (hash_try) {
		if (!strcmp(symtab[hash_try]->name, Name)) {
			return symtab[hash_try];
		}
		if (++Try >= cur_table_size)
			Try = 0; // wrap around
		if (Try == orig_try)
			return symtab[0];
		else
			hash_try = hashtable[Try];

//cout << "hash_try " << hash_try  endl;
	}
	return 0; // Failure!
}
