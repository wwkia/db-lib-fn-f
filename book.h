#include "menu.h"

class Book {
	string title;
	string author;
	int date;
	int type;
	unsigned long isbn[2];
	int pages;
	int searchmatch;
	string type_to_string(int n) const;
	friend int print_menu_file(string out_file, const vector<Book>& v);
	friend class Database;
	friend ostream& operator<<(ostream&, const Book&);
	friend istream& operator>>(istream&, Book&);
	//friend ofstream& operator<<(ofstream&, const Book&);
	//friend ifstream& operator>>(ifstream&, Book&);
	bool valid_year(int date);
	bool is_ten_digit(unsigned long entry);
	bool valid_isbn(unsigned long entry);
public: 
	Book();
	void print();
	void throwaway();
	void set_title();
	void set_author();
	void set_date();
	void set_type();
	void set_isbn();
	void set_pages();
};
//
