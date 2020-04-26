#pragma once
#include <iostream>
using namespace std;

class Cards {
	string suit;
	string name;
	public:
	Cards() : name(""), suit("") {}
	Cards(string str1, string str2) {
		name = str1;
		suit = str2;
	}
	void set_name(string n) {name = n;} 
	string get_name() {return name;}
	void set_suit(string s) {suit = s;}
	string get_suit() {return suit;}
};
