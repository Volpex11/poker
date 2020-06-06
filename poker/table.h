#pragma once
#include <iostream>
#include "cards.h"
#include "player.h"

using namespace std;

class Table {
	int rank;
	double power;
	public:
	//card hierarchy
		//rank
			// lowest: 2 highest: A
	//set hierarchy
		//Low to high
			//Highest card
				//look at player hands
			//pair
			//2 pair
			//3 of a kind
			//straight
			//flush
			//full house
			//4 of a kind
			//straight flush
			//royal flush
				//all the rest look at river and player hands

};
