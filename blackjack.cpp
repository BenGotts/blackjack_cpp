/*********************************************************************
** Program Filename: assignment3.cpp
** Author: Benjamin Gottschalk
** Date: 1/19/2019
** Description: 21 game similar to blackjack 
** Input: floats for bank/bet, y(1)/n(0) for play again and another card
** Output: card value, total value, bank value, who won, play again
*********************************************************************/

#include <iostream> //access to cout, cin, endl
#include <ctime> //access to time()
#include <cstdlib> //access to rand() and srand()

using namespace std; //uses namespace to write the code easier


bool bank(float playerbank) { //bank function definition
	bool play;
	if(playerbank > 0) { //checks the player's bank and determines if they can play
		play = true;
	}
	else if(playerbank <= 0){
		play = false;
	}
	return play; //returns if they can play
}

int bets(float bank) { //bet funtion definition
	float bet;
	
	cout << "Place a bet ($" << bank << " in bank): "; //player places bet to wager
	cin >> bet;
		
	while(bet > bank){ //checks if the bet is bigger than their bank and asks again if it is
		cout << "Place a bet lower than your bank value: ";
		cin >> bet;
	}
	return bet; //returns bet value
}

int game(bool play, float bet, float bank) { //game function definition
	int value = 0, card, hit;
		
	card = (rand() % 11) + 1;
		
	cout << "\n" << card << " is your card" << endl; //gives player a card and asks if they want another
	cout << "Do you want another card? (1-yes/0-no): ";
	cin >> hit;
		
	value += card;
		
	while(hit) { //while they want a card, another is given and is tested if it is > 21
		card = (rand() % 11) + 1;
		value += card;
		
		cout << "\n" << card << " is your card, " << value << " in total" << endl;
		
		if(value > 21) { //checks if > 21
			cout << "Player busts, dealer wins" << endl;
			break;
		}
		else {
			cout << "Do you want another card? (1-yes/0-no): ";
			cin >> hit;
		}
		
	}

	return value; //returns total point value
}

int dealer() { //dealer function definition
	int value = 0, card;
	
	cout << "Dealer's turn\n";
	
	card = (rand() % 11) + 1;
	
	cout << "\n" << card << " is the dealer's card" << endl;
	
	value += card;
	
	while(value < 18) { //if dealer's point value is < 18, then they will automatically get another card
		card = (rand() % 11) + 1;
		
		value += card;
		
		cout << "\n" << card << " is the dealer's card, " << value << " in total" << endl;
	}

	return value; //returns dealer's point value
}

int win(int player, float bank, float bet) { //win function to test for win
	int dealer1;

	if(player > 21) {
		bank -= bet;
	}
	else {

		dealer1 = dealer(); //calls dealer funtion to get dealer's value

		if(dealer1 <= 21 && player > dealer1) { //testing all win possibilities
			cout << "\nPlayer wins" << endl;
			bank += bet;
		}
		else if(dealer1 <= 21 && player < dealer1) {
			cout << "\nDealer wins" << endl;
			bank -= bet;
		}
		else if(dealer1 == player) {
			cout << "\nIt's a tie" << endl;
		}
		else {
			cout << "\nDealer busts, player wins" << endl;
			bank += bet;
		}
	}
	cout << "$" << bank << " in the bank\n";

	return bank; //return player's bank value after adding/subtracting from it
}

bool cont(int players, float bank1, float bank2, float bank3, float bank4) { //function to see if they can continue playing
	bool play;
	
	switch(players) { //switch depending of number of players
			case 1: 
			if(not bank(bank1))
				play = false; break;
			case 2: 
			if(not bank(bank2) && not bank(bank1))
				play = false; break;
			case 3:
			if(not bank(bank3) && not bank(bank2) && not bank(bank1))
				play = false; break;
			case 4: 
			if(not bank(bank4) && not bank(bank3) && not bank(bank2) && not bank(bank1))
				play = false; break;
			default: play = true;
		}
	
	return play;
}

int main() { //main function
	srand(time(NULL));

	int players = 0, again = 0, player;
	float bank1 = 0.0, bank2 = 0.0, bank3 = 0.0, bank4 = 0.0, bet;
	bool play;

	while(players < 1 || players > 4) { //if player number is between 1-4 then its good, else reprompt
		cout << "How many players? (1-4): ";
		cin >> players;

		switch(players) {
			case 1: players = 1; break;
			case 2: players = 2; break;
			case 3: players = 3; break;
			case 4: players = 4; break;
			default: players = 0;
		}
	}

	for(int x = 1; x <= players; x++) { //initializing bank values depending on how many players
		cout << "\nPlayer " << x << ", enter a starting bank value: ";
		switch(x) {
			case 1: cin >> bank1; break;
			case 2: cin >> bank2; break;
			case 3: cin >> bank3; break;
			case 4: cin >> bank4; break;
			default: cout << "Invalid input"; exit(1);
		}
		cin.clear();
	}

do { //the actual gameplay
		
		for(int x = 1; x <= players; x++) { //starts with player 1 and goes up to the amount of players
			switch(x) { //checks if the player can play
				case 1: play = bank(bank1); break;
				case 2: play = bank(bank2); break;
				case 3: play = bank(bank3); break;
				case 4: play = bank(bank4); break;
			}
		
			if(not cont(players, bank1, bank2, bank3, bank4)){ //if no one can play, then just exit
					cout << "\nNo one can play" << endl;
					exit(1);
			}
			
			else if(play) {
				cout << "\nPlayer " << x << "'s turn\n" << endl;
				
				switch(x) { //bet using the player's bank
					case 1: bet = bets(bank1); break;
					case 2: bet = bets(bank2); break;
					case 3: bet = bets(bank3); break;
					case 4: bet = bets(bank4); break;
				}

				switch(x) { //calling the game funciton using their bank and bet while they can play
					case 1: player = game(play, bet, bank1); break;
					case 2: player = game(play, bet, bank2); break;
					case 3: player = game(play, bet, bank3); break;
					case 4: player = game(play, bet, bank4); break;
				}
				switch(x) { //checks if the player can win
					case 1: bank1 = win(player, bank1, bet); break;
					case 2: bank2 = win(player, bank2, bet); break;
					case 3: bank3 = win(player, bank3, bet); break;
					case 4: bank4 = win(player, bank4, bet); break;
				}


			}
			else {
				cout << "Player " << x << " can't play with $0 in bank" << endl;
				}
			}

		cout << "\nDo you want to play again? (1-yes/0-no): "; //asks if the group wants to play again
		cin >> again;

	} while(again);

	return 0; //says everything ran fine
}
