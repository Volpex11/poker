#pragma once
#include <iostream>
#include <utility>
#include "cards.h"
using namespace std;

class Player {
	bool small_blind;		
	bool big_blind;
	string name;
	string password;
	string pos_phrase;
	string neg_phrase;
	size_t money;
	pair<Card, Card> hand;
	size_t bet;

	public:
	Player() : small_blind(0), big_blind(0), name(""), password(""), pos_phrase(""), neg_phrase(""), money(0),hand(make_pair(Card(), Card())) , bet(0) {}
	Player(bool s = 0, bool b = 0, string str, string pass, string f1, string f2, size_t m, size_t n, Card first, Card second) {
		small_blind = s;
		big_blind = b;
		name = str;
		password = pass;
		pos_phrase = f1;
		neg_phrase = f2;
		money = m;
		bet = n;
		hand = make_pair(first, second);
	}
	
	void set_small(bool b) { small_blind = b; }
	bool get_small() { return small_blind; }
	
	void set_big(bool b) { big_blind = b; }
	bool get_big() { return big_blind; }
	
	void set_name(string s) { name = s; }
	string get_name() { return name; }
	
	void set_password(string s) { password = s; }
	string get_password() { return password; }
	
	void set_pos_phrase(string s) { pos_phrase = s; }
	string get_pos_phrase() { return pos_phrase; }
	
	void set_neg_phrase(string s) { neg_phrase = s; }
	string get_neg_phrase() { return neg_phrase; }
	
	void set_first_card(Card c) { hand.first = c; }
	void set_second(Card d) { hand.second = d; }
	void set_hand(Card c, Card d) { hand = make_pair(c, d); }
	pair<Card, Card> get_hand() { return hand; }
	
};
