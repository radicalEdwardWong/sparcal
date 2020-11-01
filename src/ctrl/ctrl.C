/*
 * Controller Implementation
 *
 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "ctrl.h"

#include "../scanparse/scanparse.h"
#include "../p_tree/p_tree.h"
#include "../symtab/symtab.h"
#include "../emit/emit.h"

using namespace std;

class Symtab;
class Scope;

int Option::list;
int Option::emit;
int Option::arm;
int Option::check;

Option::Option() {
	//cout << "Option() " << endl;
	list = 0;
	emit = 0;
	arm = 0;
	check = 0;
}

int Option::option_info() {
	return (list | emit | arm | check);
}

int Controller::open_file(char* source_file) {
	//cout<< "Conroller::open_file(" << source_file << ") " << endl;
	int length = strlen(source_file);
	//Check for .p extension
	if ((length > 1) && ((source_file[length -2] == '.') &&
						 (source_file[length -1] == 'p') )) {
		if (!freopen(source_file, "r", stdin)) {
			cout << "	Cannot open file -- Sorry " << endl;
			return 0;
		} else {
			return 1;
		}
	} else if (length == 0) {
		cout << "	No fie specified" << endl;
		return 0;
	} else {
		cout << "	File must have a .p extension" << endl;
		return 0;
	}
}


Controller::Controller(int argc, char** argv) {
	//cout << "Controller " << endl;

	this->std_table = new Symtab;
	PScope scp = new Scope;
	scp->visible_symtab = this->std_table;

	char *source_file = new char[80];
	this->parse_tree = 0;
	if (argc <= 1) {
		cout << "	Usage: sparcal [-ela] <filename>.p" << endl;
		return;
	} else {
		for (int i = 1; i < argc; i++) {
			if (*argv[i] != '-') {
				source_file = argv[i];
			} else {
				while (*++argv[i]) {
					switch(*argv[i]) {
					case 'l':
						Option::list = 1;
						continue;

					case 'e':
						Option::emit = 2;
						continue;

					case 'a':
						Option::arm = 4;
						continue;

					case 'C':
						Option::check = 8;
						continue;

					default:
						cerr << "Unknown option " <<
										*argv[i] << endl;
					}
				}
			}
		}
	}

	if (open_file(source_file)) {
		ios::sync_with_stdio();
		PScanParse sp = new ScanParse;
		this->parse_tree = sp->parse_tree;

		if (Option::check) {
			cout << "Type checker not yet implemented!! b-(>_<)-d" << endl;
		}

		if (Option::emit) {
			if (Option::arm) {
				parse_tree->emit(new ArmEmitter);
			} else {
				parse_tree->emit(new SparcEmitter);
			}
		} else if (Option::list) {
			parse_tree->execute();
		}
	}
}

