#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <deque>
#include "player.h"
#include "cards.h"

using namespace std;

class table {
	public:
		//what the table holds and keeps track of goes here

		static const int MAX_PLAYERS = 10;

		//All 'holds:' comments list the vector layers in order from outter to inner

		//holds: player numbers
		vector<int> players;

		//holds: position of play
		vector<int> play;

		//holds: blind position
		vector<vector<int>> bigy_smalls;

		//holds: the value of the Calls bet
		vector<int> Calls_bet;

		//holds: player bet in number of chips and chip type for each player
		vector<vector<vector<int>>> player_bet;

		//holds: the pot value in number of chips and chip types
		vector<vector<int>> pot;

		//holds: player num, number of each chip type for each player
		vector<vector<vector<int>>> player_chips;

		//holds: chip types
		vector<int> chip_values;

		//holds: player num, player cards
		vector<vector<int>> player_hand;

		//holds: the deck
		deque<int> deck;

		//holds: the river cards
		vector<int> river;

		vector<string> name = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

		vector<string> suit = {"hearts","diamonds","clubs","spades"};

		void init_deck() {
			for (int i = 1; i < 53; ++i) {
				deck.push_back(i);
			}	
		}

		void display_hands(int player) {
			int num = 0, s = 0, j = player;
			cout << "Player " << j << " cards:" << endl << endl;
			for (int i = 0; i < player_hand.at(j).size(); i++) {
				if (player_hand.at(j).at(i) <= 13) {
					s = 0;
					num = (player_hand.at(j).at(i) % 14);
				}
				else if (player_hand.at(j).at(i) > 13 and player_hand.at(j).at(i) <= 26) {
					s = 1;
					num = ((player_hand.at(j).at(i) + 1) % 14);
				}
				else if (player_hand.at(j).at(i) > 26 and player_hand.at(j).at(i) <= 39) {
					s = 2;
					num = ((player_hand.at(j).at(i) + 2) % 14);
				}
				else if (player_hand.at(j).at(i) > 39 and player_hand.at(j).at(i) <= 52) {
					s = 3;
					num = ((player_hand.at(j).at(i) + 3) % 14);
				}
				string Hearts = {
					"|            |\\\n"
						"|   / \\/ \\   |\\\n"
						"|   \\    /   |\\\n"
						"|    \\  /    |\\\n"
						"|     \\/     |\\\n"
						"|            |\\"
				};
				string Spades = {
					"|            |\\\n"
						"|     /\\     |\\\n"
						"|    /  \\    |\\\n"
						"|   /    \\   |\\\n"
						"|   \\_/\\_/   |\\\n"
						"|     /\\     |\\"
				};
				string Diamonds = {
					"|            |\\\n"
						"|     /\\     |\\\n"
						"|    /  \\    |\\\n"
						"|    \\  /    |\\\n"
						"|     \\/     |\\\n"
						"|            |\\"
				};
				string Clubs = {
					"|            |\\\n"
						"|     __     |\\\n"
						"|   _(  )_   |\\\n"
						"|  (__)(__)  |\\\n"
						"|     ||     |\\\n"
						"|            |\\"
				};
				const string ImageIndex[] = {Hearts, Diamonds, Clubs, Spades};
				const string CardChar[] = { "A ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "J ", "Q ", "K " };
				//cout << "Player " << j << " cards:" << endl << endl;
				cout << "The " << name.at(num - 1) << " of " << suit.at(s) << endl;
				cout << " ____________ " << endl;
				cout << "|" << CardChar[num - 1] << "          |\\" << endl;
				cout << ImageIndex[s] << endl;
				cout << "|          " << CardChar[num - 1] << "|\\" << endl;
				cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl << endl;
			}
		}
		//not used| the function above is used instead
		//converts deck numbers to name and suit
		void name_suit() {
			int num = 0;
			int s = 0;
			for (int i = 0; i < deck.size(); i++) {
				if (deck.at(i) <= 13) {
					s = 0;
					num = (deck.at(i) % 14);
				}
				else if (deck.at(i) > 13 and deck.at(i) <= 26) {
					s = 1;
					num = ((deck.at(i) + 1) % 14);
				}
				else if (deck.at(i) > 26 and deck.at(i) <= 39) {
					s = 2;
					num = ((deck.at(i) + 2) % 14);
				}
				else if (deck.at(i) > 39 and deck.at(i) <= 52) {
					s = 3;
					num = ((deck.at(i) + 3) % 14);
				}

				//cout << deck.at(i) << " " << name.at(num - 1) << " " << suit.at(s) << endl;
			}
		}

		void Shuffle() {
			random_device rd;
			mt19937 eng(rd());
			shuffle(deck.begin(), deck.end(), eng);
			/*  cout << "The deck: ";
			  for (auto it = deck.begin(); it != deck.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';
			  */
		}

		//initializes all players aspects and the num of play positions 
		void init_players(int &p, int &k) {

			while (cin) {
				cout << "Enter the number of players\n";
				cin >> p;
				if (p > MAX_PLAYERS) {
					cout << "Too many players!\n";
					continue;
				}
				if (p < 0) {
					cout << "Too few players!\n";
					continue;
				}
				if (!cin){
					cout << "INVALID INPUT!!\n";
					continue;
				}
				if (p <= MAX_PLAYERS and p > 0) break;
			}
			//players hands and position of play are initialized here
			for (int k = 0; k < p; k++) {
				vector<int> temp;
				for (int c = 0; c < 2; c++) {
					int card = deck.front();
					temp.push_back(card);
					deck.erase(deck.begin());
				}
				players.push_back(k);
				player_hand.push_back(temp);
			}
			cout << "Players hand: ";
			  for (auto it = player_hand.at(k).begin(); it != player_hand.at(k).end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';
			
			  cout << "The deck: ";
			  for (auto it = deck.begin(); it != deck.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';
			/*
			for (int k = 0; k < p; k++) {
			  vector<vector<int>> temp2;
			  for (int j = 0; j < 6; j++) {	
			//chip types are initialized here
			for (int i = 0; i < 6; i++) {
			chip_values.push_back(i);

			if (i == 0) chip_values.push_back(1);
			if (i == 1) chip_values.push_back(5);
			if (i == 2) chip_values.push_back(10);
			if (i == 3) chip_values.push_back(25);
			if (i == 4) chip_values.push_back(100);
			if (i == 5) chip_values.push_back(500);	
			}*/	
			/*cout << "Chip type values: ";
			  for (auto it = chip_values.begin(); it != chip_values.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';*/

			/*	if (j == 0) temp2.at(j) = 50;
				if (j == 1) temp2.at(j) = 50;
				if (j == 2) temp2.at(j) = 25;
				if (j == 3) temp2.at(j) = 10;
				if (j == 4) temp2.at(j) = 5;
				if (j == 5) temp2.at(j) = 2;
				}

				player_chips.push_back(temp2);
				}*/
			/*cout << "num of chip types: ";
			  for (auto it = player_chips.at(k).begin(); it != player_chips.at(k).end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';*/

			for (int k = 0; k < p; k++) {
				vector<int> temp3;
				for (int i = 0; i < 3; i++) {
					temp3.push_back(i);
				}
				bigy_smalls.push_back(temp3);
			}
		}

		//keeps track of who is a blind
		void blinds(int round, int player, int no, int big, int small) {
			int blind_type = 0;
			for (int i = 0; i < players.size(); i++) {
				if (i == round - 1) {
					bigy_smalls.at(i).at(small);
					play.push_back(0);
				}
				else if (i == round) {
					bigy_smalls.at(i).at(big);
					play.push_back(players.size()-1);
				}
				else {
					bigy_smalls.at(i).at(no);
					for (int j = 1; j < players.size()-1; j++) {
						play.push_back(j);
					}
				}
			}
			cout << "blind " << bigy_smalls.at(play.at(player)).at(blind_type) << endl;
		}
		//trashes a card and deals three cars to the river
		void the_flop() {
			deck.erase(deck.begin());
			for (int i = 0; i < 3; i++) { 
				int card = deck.front();
				river.push_back(card);
			}
			/*cout << "The deck: ";
			  for (auto it = deck.begin(); it != deck.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';

			  cout << "The river: ";
			  for (auto it = river.begin(); it != river.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';*/
		}
		//trashes a card and deals a card to the river
		void burn_N_turn() {
			//burn
			deck.erase(deck.begin());
			for (int i = 0; i < 1; i++) {
				//turn
				int card = deck.front();
				river.push_back(card);
			}
			/*cout << "The deck: ";
			  for (auto it = deck.begin(); it != deck.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';

			  cout << "The river: ";
			  for (auto it = river.begin(); it != river.end(); ++it) {
			  cout << ' ' << *it;
			  }
			  cout << '\n';*/
		}
};
