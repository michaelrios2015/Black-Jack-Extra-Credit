//*********************************************** 
// COSC 501                                Optional Project 
// Michael Rios                             12/15/13 
// PROGRAM-NAME: optional project	 
//  
//Blackjack!!
//*********************************************** 

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

// your basic card it would be better with a string variable for the name of the card i.e. one, king, etc.
struct Card
{
int number;
string suite;
};

//the deck
Card deck[52];

//players and dealers hand 11 is the most cards one can get before going over 21
Card players_hand[11];
Card dealers_hand[11];

//creates the 52 cards in deck
void intialize_deck();

//places the cards in random order 
void shuffle_deck();

//resets all the important values to zero so we can play again
void set_to_zero(int& player_index, int& dealer_index, int& deck_index, int& game_over);

//displays the hand used to check will program and used at the end to show both hands
void display_hand(Card hand[], int hand_size);

//totals player or dealers hand, aces count as 11 or 1 depending on total score
int total(Card hand[], int hand_size);

//checks to see how many aces are in players or dealers hand 
int aces(Card hand[], int hand_size);

void main ()
{
	int game_over, deck_index, player_index, dealer_index, doubled, player_wins = 0, dealer_wins = 0; //some important variables
	char hit, cont = 'y', Double = 'n';
		
	intialize_deck(); //creates the deck with 13 of each suite
	
	while (cont != 'n') //allows user to play as many games as they want
	{	
		shuffle_deck();
		set_to_zero(player_index, dealer_index, deck_index, game_over);
		doubled = 0;
		Double = 'n';
		
		for (deck_index; deck_index < 2; deck_index++) //DEALS FIRST TWO CARD TO PLAYER
		{
			cout << "your " << deck_index+1 << " card is the " << deck[deck_index].number << " of " << deck[deck_index].suite << endl;
			players_hand[deck_index] = deck[deck_index]; //assigns card to players hand
		}

		player_index = deck_index;

		cout << "your total is " << total(players_hand, player_index) << endl; //PLAYER TOTAL
	
		cout << "the dealers first card is the " << deck[deck_index].number << " of " << deck[deck_index].suite << endl; //DEALERS FIRST CARDS
		dealers_hand[dealer_index] = deck[deck_index];

		deck_index++;
		dealer_index++; //moves the array up/goes to the next card 

		dealers_hand[dealer_index] = deck[deck_index];
		
		deck_index++;
		dealer_index++;
		
		if (total(players_hand, player_index) == 9 || total(players_hand, player_index) == 10) //DOUBLE
		{ 
			cout << "would you like to double?? (y/n)\n";
			cin >> Double;
		}

		if (Double == 'y')
		{
			doubled = 1;
			cout << "would you like another card (y/n)\n";
			cin >> hit;
			
			if (hit == 'y') //player can take another card
			{
						
				cout << "your next card is the " << deck[deck_index].number << " of " << deck[deck_index].suite << endl;
				players_hand[player_index] = deck[deck_index];
	
				deck_index++;
				player_index++;
				
				cout << "your total is " << total(players_hand, player_index) << endl;

				if (total(players_hand, player_index) > 21)//you have gone over 21 you lose
				{

					cout << "Your total is " << total(players_hand, player_index) << endl; 
					cout <<	"Sorry you went over 21: YOU LOSE!!\n";  
					dealer_wins++;
					game_over = 1;
				}

			}
		}

		else //REGULAR HIT -- PLAYER
		{
			cout << "would you like another card (y/n)\n";
			cin >> hit;

			while (hit != 'n' && total(players_hand, player_index) < 22) //allows player to continuing getting cards till they say 
			{															 //no or go over 21	
				
				cout << "your next card is the " << deck[deck_index].number << " of " << deck[deck_index].suite << endl;
				players_hand[player_index] = deck[deck_index];
			
				deck_index++;
				player_index++;

				if (total(players_hand, player_index) > 21) //over 21 you lose
				{
					cout << "Your total is " << total(players_hand, player_index) << endl; 
					cout <<	"Sorry you went over 21: YOU LOSE!!\n"; 
					dealer_wins++;
					game_over = 1;
				}
				else
				{
					cout << "would you like another card (y/n)\n";
					cin >> hit;
				}
			}	

		}
		while (!game_over) //DEALER - you have not gone over 21
		{
			while (total(dealers_hand, dealer_index) <= 17) //dealer keeps getting cards till they reach 17 or over 
			{
					
				cout << "the dealers next card is the " << deck[deck_index].number << " of " << deck[deck_index].suite << endl;
				dealers_hand[dealer_index] = deck[deck_index];
				
				deck_index++;
				dealer_index++;
				
				if (total(dealers_hand, dealer_index) > 21) //dealer goes over 21 you win
				{
					cout << "The dealers total is " << total(dealers_hand, dealer_index) << endl;
					cout << "YOU WIN!!! dealer goes over 21\n";
					if (!doubled)
						player_wins++; 
					else 
						player_wins = player_wins + 2; //doubled so you win counts as 2
					game_over = 1;
				}
			}
		
		
			if (!game_over) //SEE WHO WON
			{
				if (total(dealers_hand, dealer_index) > total(players_hand, player_index)) //dealers hand is bigger than players -- dealer wins
				{
					cout << "DEALER WINS: dealer total = " << total(dealers_hand, dealer_index) << " player total = " << total(players_hand, player_index) << endl;
					dealer_wins++;
					game_over = 1;
				}
				else if (total(dealers_hand, dealer_index) < total(players_hand, player_index)) //players hand is bigger than dealers -- players wins
				{
					cout << "PLAYER WINS: dealer total = " << total(dealers_hand, dealer_index) << " player total = " << total(players_hand, player_index) << endl;
					if (!doubled)
						player_wins++;
					else 
						player_wins = player_wins + 2;
					game_over = 1;
				}
				else 	
				{
					cout << "IT'S A TIE: dealer total =  " << total(dealers_hand, dealer_index) << " player total = " << total(players_hand, player_index) << endl;
					game_over = 1;
				}
			}
					
		}
	cout << "PLAYER'S Hand was: \n"; //shows both hands
	display_hand(players_hand, player_index);
	
	cout << "DEALER'S Hand was: \n";
	display_hand(dealers_hand, dealer_index);
	
	cout << "would you like to play again (y/n): \n";
	cin >> cont;

	}

	cout << "Player won " << player_wins << " games\n"; //shows how many games dealer and player won
	cout << "Dealer won " << dealer_wins << " games\n";
}

void set_to_zero(int& player_index, int& dealer_index, int& deck_index, int& game_over)
{
	player_index = 0, 
	dealer_index= 0, 
	deck_index = 0;
	game_over = 0;
}

void shuffle_deck()
{
	long seed;
	int k;
	Card temp[52];
	time_t *storage;
	storage = 0;
	
	seed = time(storage);  // use the system clock to produce an initial time 
	
	srand(seed);            // to seed the random number generator

	int random[52]; 

	k = 0;
	while(k < 52) //creates an array of 52 intergers (0-51) in random order
	{
	random[k] = rand() % 52;
	k++;
	}

	for (int i = 0; i < 52; i++) //uses random array to shuffle cards
	{
		temp[i] = deck[i]; //temp holds the card	
		deck[i] = deck[random[i]]; //a new card is assigned to place i
		deck[random[i]] = temp[i]; //old card is reassigned to place random
	}
}

void intialize_deck() //creates deck
{

	for (int i=0; i < 9; i++)
	{
		deck[i].number = i + 2;
		deck[i].suite = "Hearts";
	}

	for (int i=9; i < 12; i++)
	{
		deck[i].number = 10;
		deck[i].suite = "Hearts";
	}

	deck[12].number = 11;
	deck[12].suite = "Hearts";

	for (int i=13; i < 22; i++)	
	{
		deck[i].number = i - 11;
		deck[i].suite = "Jacks";
	}

	for (int i=22; i < 25; i++)
	{
		deck[i].number = 10;
		deck[i].suite = "Jacks";
	}

	deck[25].number = 11;
	deck[25].suite = "Jacks";


	for (int i=26; i < 35; i++)
	{
		deck[i].number = i - 24;
		deck[i].suite = "Spades";
	}

	for (int i=35; i < 38; i++)
	{
		deck[i].number = 10;
		deck[i].suite = "Spades";
	}

	deck[38].number = 11;
	deck[38].suite = "Spades";

	for (int i=39; i < 48; i++)
	{
		deck[i].number = i - 37;
		deck[i].suite = "Clubs";
	}

	for (int i = 48; i < 51; i++)
	{
		deck[i].number = 10;
		deck[i].suite = "Clubs";
	}

	deck[51].number = 11;
	deck[51].suite = "Clubs";

}

void display_hand(Card hand[], int hand_size)
{
	for(int i = 0; i < hand_size; i++)
		cout << "The " << i + 1 << " card is the " << hand[i].number << " of " << hand[i].suite << endl;
}

int total(Card hand[], int hand_size)
{
	int total = 0; 

	if (aces(hand, hand_size) == 0) //super easy no aces involved
	{
		for(int i = 0; i < hand_size; i++)
			total = total + hand[i].number;
	}
	else   
	{
		for(int i = 0; i < hand_size; i++)
			total = total + hand[i].number;
			if (total > 22) //there is an ace and the total has gone over 21
				total = total - aces(hand, hand_size)*10; //turn the ace(s) into 1(s)
				if (total < 12) //if the the new total has gone to 11 or below, i.e. you had a four and two aces
								//with a total of 6 when both aces are counted as ones, we add ten so one ace is counted as 11
								//and the others as 1
					total = total + 10;
	}
		
	return total;

}

int aces(Card hand[], int hand_size)
{
	int total = 0; 

	for(int i = 0; i < hand_size; i++)
		if (hand[i].number == 11)
			total++;

	return total;

}
	