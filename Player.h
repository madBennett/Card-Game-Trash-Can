/*
CS281 – Spring 2021
Card Game Project
Madison Bennett
29 May 2021
The purpose of this program is to play and test the game trash can
*/

#pragma once
#include "CardDeck.h"

class Player
{
private:
	int startingAmount;
	int currentAmount;
	bool roundWon;
	Card* deck;
	bool* completedDeck;

public:

	Player();

	Card useCard(CardDeck&, Card&);	 
	Card useCardAI(CardDeck&, Card&); 	
	void reset();		  

	void nextRound(CardDeck&);	  
	void setCurrentAmount(int);	   

	void showDeck();			 
	int getCurrentAmount();		
	bool isCardInDeck(Card&);		 
	bool hasWonRound();			 
	bool hasWonGame();			   

	~Player();			  
};

