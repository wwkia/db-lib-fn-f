//database.cpp


//constructs an empty database
Database::Database()
: lib({}) {}

//displays error or success, returns user selection to repeat function or exit to main
int db_fn_exit(bool fn_state, string fn_msg) {
	//if state is false (error occured) print red error msg
	if (fn_state==false)
		cout << red << "\nError  " << fn_msg << def_txt;
	//if state is true (function successfully executed) print green success msg
	if (fn_state==true)
		cout << green << "\nSuccess! " << bold << fn_msg << def_txt;
	//ask user to repeat action or exit
	Menu db_fn_exit("db_fn_exit.txt", 2);
	db_fn_exit.display_menu();
	int choice=db_fn_exit.get_ui();
	return choice;
}
//asks user to confirm entry correctness (Yes/Update/Return to main)
int Database::entry_confirm(Book& entry) {
	//print the entry
	entry.print();
	//display a confirmation menu
	Menu entry_confirm_menu("entry_confirm_menu.txt", 3);
	entry_confirm_menu.display_menu();
	//return the users choice
	int choice=entry_confirm_menu.get_ui();
	return choice;
}
//update a book entry 
void Database::update_book(Book& entry) { //pass in the entry by reference so it is directly updated
	Menu update_menu("update_menu.txt",7);
	update_menu.display_menu();
	int choice=update_menu.get_ui();
	//while (choice!=update_menu.exit_code()) {
		switch (choice) {
			case 1:
				entry.throwaway();
				entry.set_title();
				break;
			case 2:
				entry.throwaway();
				entry.set_author();
				break;
			case 3:
				entry.throwaway();
				entry.set_date();
				break;
			case 4:
				entry.throwaway();
				entry.set_type();
				break;
			case 5:
				entry.throwaway();
				entry.set_isbn();
				break;
			case 6:
				entry.throwaway();
				entry.set_pages();
				break;
			case 7:
				break;
			default:
				break;
		}
	//}
}
int Database::add(vector<Book>& lib) {
	cout << clrscrn << "Adding a book entry...\n\n";
	Book temp;
	//collect values
	temp.throwaway();
	temp.set_title();
	temp.set_author();
	temp.set_date();
	temp.set_type(); 
	temp.set_isbn();
	temp.set_pages();
	int choice=0;
	do {
		//ask user to confirm the addition
    	choice=entry_confirm(temp);
		//adds the entry to the data base 
		if (choice==1) {
			lib.push_back(temp);
			//return function exit option (add again/exit to main)
			return db_fn_exit(true,"Book added to the database.");
			break;
		}	
		//update desired field 
		if (choice==2) 
			update_book(temp);
	} while (choice !=3); //choice 3 exits to main
	return 0;
}
//prints a vector of books to a file with numbere entries
int print_menu_file(string out_file, vector<Book>& v) {
	fstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_fn_exit(false,"opening file"); //returns ui from the error menu (Try again/Exit)
	//iterates through each entry of the vector, prints number beside each entry
	for (int i=0; i<v.size(); i++) {
		out << i+1 << " " << v.at(i);
	}
	return 0;
}
//deletes an entry
int Database::del(vector<Book>& lib) {
	cout << clrscrn << "Delete an entry from the database...\n";
	//open an edit menu which asks user to browse, search, or cancel
	Menu del_menu("edit_menu.txt", 3);
	//display delete menu (Browse/Search/Cancel)
	del_menu.display_menu();
	int choice=del_menu.get_ui();
	//browse all entries to delete
	if (choice==1) {
		//turns the database into a menu 
		int n=print_menu_file("database.txt",lib);
		//there was an error opening the print file, user chose to try again
		if (n==1)
			del(lib);
		//there was an error opening the print file, user chose to exit to main
		if (n==2)
			return 0;
		Menu database("database.txt", lib.size());
		database.display_menu();
		//asks user which entry to delete
		int del_entry=database.get_ui();
		//delete the entry from the library vector
		lib.erase(lib.begin()+(del_entry-1));
		return db_fn_exit(true,"Entry deleted.");
	}
	//search for entry to delete
	if (choice==2) {
		int i=search(1);
		if (i==0)//if user choice to return to main menu in the search function
			return 0;
		lib.erase(lib.begin()+(i-1));
		return db_fn_exit(true, "Entry deleted.");
	}
	//back to main menu
	if (choice==3)
		return 0;
}
//update an existing entry 
int Database::update() {
	cout << clrscrn << "Edit an entry in the database...\n";
	Menu update_menu("edit_menu.txt",3);
	//display update menu(Browse/Search/Cancel)
	update_menu.display_menu();
	int choice=update_menu.get_ui();
	if (choice==1) {
		//turn database into menu
		print_menu_file("database.txt",lib);
		Menu database("database.txt",lib.size());
		//ask user entry to update
		int update_entry=(database.get_ui()-1);
		update_book(lib.at(update_entry));
		return db_fn_exit(true, "Entry updated.");
	}
	//search for entry to edit
	if (choice==2) {
		int i=search(1);
		//if the user chose to return to main menu in the search function
		if (i==0)
			return 0;
		update_book(lib.at(i-1));
		return db_fn_exit(true, "Entry updated.");
	}
	//back to main menu
	return 0;
}

//print a vector of books to the console as a numbered list
void console_print(const vector<Book>& v) {
	int i=1;
	for (auto& entry : v) { //for each entry in v print index and entry
		cout << i << " " << entry; //works because << was overloaded 
		i++;
	}
}
//print search results for pure searching
int Database::pure_search(vector<Book>& results) {
	//options at top of search results (Search again/Exit to main)
	Menu search_result_menu("search_result_menu.txt",2);
	search_result_menu.display_menu();
	//print sorted results to the console
	console_print(results);
	//search again or exit to main
	int search_choice=search_result_menu.get_ui();
	//search again
	if (search_choice==1)
		return -1;
	//exit to main
	return 0;
}
//print search results for editing a result
int Database::edit_search(vector<Book>& results) {
	console_print(results);
	//options at bottom of search results (Choose/Search again/Exit to main)
	Menu edit_search_result_menu("edit_search_result_menu.txt",3);
	edit_search_result_menu.display_menu();
	int edit_search_choice=edit_search_result_menu.get_ui();
	//choose an entry
	if (edit_search_choice==1) {  
		//create menu from search results
		print_menu_file("search_results.txt",results);
		Menu search_results("search_results.txt",results.size());
		int edit_entry=search_results.get_ui();
		//locate book in the result vector
		Book edit_choice = results.at(edit_entry - 1);
		//get the location of the chosen book in the database library vector
		//int update_loc = update_loc(edit_choice,lib);
		//return it's location (+1 because 0= return to main, the 1 is removed when processing later) 
		//return update_loc + 1;
	}
	//search again
	if (edit_search_choice==2) 
		return -1;
	//exit to main
	return 0;
}
//processes the chosen search type (EX searches by author)
int Database::switch_search(int choice, bool search_type) {
	vector<Book> results;
	Book temp;
	switch (choice) {
			//searches database by title
			case 1: {
				temp.set_title();
				string search_title=temp.title;
				while (!(cin>>search_title))
					ui_error("title");
				//results=find(search_title, "*", "*", "*", "*", "*", "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by author
			case 2: {
				temp.set_author();
				string search_author=temp.author;
				while (!(cin>>search_author))
					ui_error("author");
				//results=find("*", search_author, "*", "*", "*", "*", "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by date
			case 3: {
				temp.set_date();
				string search_date=to_string(temp.date);
				while (!(cin>>search_date))
					ui_error("date");
				//results=find("*", "*", search_date, "*", "*", "*", "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by date
			case 4: {
				temp.set_type();
				string search_tp=temp.type_to_string(temp.type);
				while (!(cin>>search_type))
					ui_error("type");
				//results=find("*", "*", "*", search_tp, "*", "*", "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by ISBN 10 digit
			case 5: {
				string search_isbn10;
				cout << "\nISBN10: ";
				while (!(cin>>search_isbn10))
					ui_error("isbn10");
				//results=find("*", "*", "*", "*", search_isbn10, "*", "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by ISBN 13 digit
			case 6: {
				string search_isbn13;
				cout << "\nISBN 13: ";
				while (!(cin>>search_isbn13))
					ui_error("isbn13");
				//results=find("*", "*", "*", "*", "*", search_isbn13, "*", lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by # of pages
			case 7: {
				temp.set_pages();
				string search_pages=to_string(temp.pages);
				//results=find("*", "*", "*", "*", "*", "*", search_pages, lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by multiple parameters
			case 8: {
				cout << "\nSearch by multiple parameters.";
				cout << "Enter * for unknown fields";
				temp.throwaway();
				temp.set_title();
				string search_title=temp.title;
				temp.set_author();
				string search_author=temp.author;
				temp.set_date();
				string search_date=to_string(temp.date);
				temp.set_type();
				string search_tp=temp.type_to_string(temp.type);
				temp.set_isbn();
				string search_isbn10=to_string(temp.isbn[0]);
				string search_isbn13=to_string(temp.isbn[1]);
				temp.set_pages();
				string search_pages=to_string(temp.pages);
				//results=find(search_title,search_author,search_date,search_tp,search_isbn10,search_isbn13,search_pages,lib);
				//results=sort(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			case 9:
				return 0;
			default:
				return 0;
				break;
		}
}
//search for an entry
int Database::search(bool search_type) {
	//display the search menu
	Menu search_menu("search_menu.txt",9);
	search_menu.display_menu();
	int search_choice=search_menu.get_ui();
	//process chosen search type (EX by title)
	int switch_result=switch_search(search_choice,search_type);	
	//user chose to exit to main
	if (switch_result==0) 
		return 0;
	//user chose to search again
	if (switch_result==-1) 
		search(search_type);
	return switch_result;
}
//collects a file name from the user 
string ui_file_name() {
	string name;
	cout << "\nPlease enter a file name: ";
	while (!(cin>>name))
		ui_error("file name");
	return name;
}
//prints contents of database to a file 
int Database::print_to_file(string out_file) {
	ofstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_fn_exit(false,"Could not open file."); //returns ui from the error menu
	//iterates through each entry of the vector
	for (auto& entry: lib) 
		out << entry; //prints to file
	return 0;
}
//saves the database to a textfile named by user
int Database::save() {
	//ask user for a file name and open the file
	cout << clrscrn << "Save the database to a file...\n";
	string save_file_name=ui_file_name();
	int n=print_to_file(save_file_name);
	if (n==0)
		return db_fn_exit(true,"Database saved");
	//error opening file, user chose to try again
	if (n==1)
		save();
	//error opening file, user chose to exit to main
	return 0;		
}
//loads a database from a file
int Database::load() {
	cout << clrscrn << "Load the database from a text file...\n";
	//ask user for a file name and open the file
	string load_file_name=ui_file_name();
	fstream out;
	out.open(load_file_name);
	if (out.fail())
		return db_fn_exit(false,"opening file"); //returns ui from the error menu
	Book temp;
	while (out >> temp) //adds objects to database until extraction fails
		lib.push_back(temp);
	return db_fn_exit(true,"\nData base loaded.");
	return 0;
}