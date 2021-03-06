// lab0.cpp : 定义控制台应用程序的入口点。
// aaa

#include "stdafx.h"
#include"lab0header.h"
#include<iostream>
#include<vector>
#include <string>
#include <sstream>
#include <fstream>
#include<ctype.h>

using namespace std;

int readFile(vector<string> &str, char * r) {
	string buffer;
	ifstream ifs(r);
	if (ifs.is_open()) {
		while ( ifs>>buffer) {
			str.push_back(buffer);

		}

		

		ifs.close();
		return funReturn::success;
	}
	else {
		cout << "can't open the file." << endl;
		return funReturn::file_open_failed;

	}



}

int usage(char *r) {
	cout << "usage: " << r << " " << "<input_file_name>" <<endl;
	return funReturn::no_file_name_given;


}
int main(int argc, char* argv[])
{
	if (argc != 2) {

		return usage(argv[0]);


	}

	vector<string> str;
	int message;
	bool isDigit = false;
	message=readFile(str, argv[1]);

	if (message != 0) {

		return message;
	}
	vector<int> num;
	
	for (size_t i = 0; i < str.size(); ++i) {

		const char *c = 0;
		c = str[i].c_str();

		for (size_t j = 0; j < str[i].size(); ++j) {
			if (isdigit(c[j]) != 0) {
				isDigit = true;
			}

			else {
				isDigit = false;
				break;
			}

		}
		if (isDigit) {
			istringstream temp(str[i]);
			int n;
			temp >> n;
			num.push_back(n);

		}
		else {
			cout << str[i] << " " << flush;
		}
	}
	cout << endl;

	for (size_t i = 0; i < num.size(); ++i) {

		cout << num[i] << " " << flush;

	}
    return funReturn::success;
}

