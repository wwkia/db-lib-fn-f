#include "book.h"

using namespace std;

int db_fn_exit(bool fn_state, string fn_msg);

//database.h
class Database {
	vector<Book> lib;
	int print_to_file(string out_file);
public:
	friend class Main_menu;
	Database();
	int entry_confirm(Book& entry);
	void update_book(Book& entry);
	int add(vector<Book>& lib);
	int del(vector<Book>&lib);
	int update();
	int pure_search(vector<Book>& results);
	//int get_update_data_loc(Book choice);
	int edit_search(vector<Book>& results);
	int switch_search(int choice, bool search_type);
	int search(bool search_type);
	int save();
	int load();
};
