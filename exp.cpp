/*
 * exp.cpp: Program to record expense
 *
 * St: 2016-11-10 Thu 07:01 PM
 * Up: 2016-11-19 Sat 04:41 PM
 *
 * Author: SPS
 */

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>

using namespace std;

/*
 * Expense book class
 */

class ExpBook
{
	private:
	fstream exp_file;
	vector<string> data;
	map<string, vector<string> > data_list;

	public:
	void open_book();
	void read_book();
	void disp_data();
	void add_data();
	void write_book();
	void close_book();
};

/*
 * Expense book class methods
 */

/* Open record book */
void ExpBook::open_book()
{
	exp_file.open("exp.exp");
}

/* Read book, and store the data in memory along the way */
void ExpBook::read_book()
{
	string line;
	string day_date;

	/* TODO: fix this */
	day_date = "dummy";

	while (getline(exp_file, line)) {
		if (line.compare(0, 6, "Date: ") == 0) {
			if (data_list.find(line) == data_list.end()) {
				day_date = line;
				data_list[day_date];
			}
		}
		data_list[day_date].push_back(line);
	}
}

/* Add new data to memory */
void ExpBook::add_data()
{
	string date;
	string line;

	cout << endl;
	cout << "Adding new data" << endl;
	cout << "===============" << endl;

	/* Get date */
	date = "Date: ";
	cout << endl;
	cout << "Date: ";
	getline(cin, line);
	date.append(line);
	if (data_list.find(date) == data_list.end()) {
		data_list[date];
		data_list[date].push_back(date);
	}

	/* Add items to this date */
	cout << endl;
	cout << "Enter items: " << endl;
	cout << endl;
	while (getline(cin, line) && line.compare("stop") != 0) {
		data_list[date].push_back(line);
	}
}

/* Diplay data stored in memory */
void ExpBook::disp_data()
{
	map<string, vector<string> >::iterator itr;

	cout << "Displaying data" << endl;
	cout << "===============" << endl;
	cout << endl;
	for (itr = data_list.begin(); itr != data_list.end(); itr++) {
		vector<string>& day_data = itr->second; 
		for (string each_data : day_data) {
			cout << each_data << endl;
		}
	}
}

/* Write record book */
void ExpBook::write_book()
{
	map<string, vector<string> >::iterator itr;

	cout << "Writing to file" << endl;
	cout << "===============" << endl;
	cout << endl;
	for (itr = data_list.begin(); itr != data_list.end(); itr++) {
		vector<string>& day_data = itr->second; 
		for (string each_data : day_data) {
			exp_file << each_data << endl;
		}
	}

}

/* Close record book */
void ExpBook::close_book()
{
	exp_file.close();
}

/* main: start __ */
int main(void)
{
	ExpBook book;
	string line;

	book.open_book();
	book.read_book();
	cout << "== Displaying orig data ==\n" << endl;
	book.disp_data();
	book.add_data();
	cout << "== Displaying after adding data ==\n" << endl;
	book.disp_data();
	cout << "Write to file ? [y/n]: ";
	getline(cin, line);
	if (line.compare("y") == 0) {
		book.close_book();
		book.open_book();
		book.write_book();
	}
	book.close_book();

	return 0;
}

