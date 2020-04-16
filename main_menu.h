#include "database.h"

class Main_menu : public Menu {
	public:
		Main_menu(string f, int n);
		void switch_main(int choice, Database db);
};



