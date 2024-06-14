/*
CS281 – Spring 2021
Card Game Project
Madison Bennett
29 May 2021
The purpose of this program is to play and test the game trash can
*/

#include "CardDeck.h"

#include <ctime>
#include <cstdlib>
#include <iomanip>

CardDeck::CardDeck()
{
	maxSize = 52;
	size = maxSize;
	deck = new Card[maxSize];

	//for shuffle
	srand((unsigned)time(0));

	initalizeSuit("Hearts", 0, maxSize / 4);
	initalizeSuit("Clubs", maxSize / 4, maxSize / 2);
	initalizeSuit("Diamonds", maxSize / 2, (3 * maxSize / 4));
	initalizeSuit("Spades", (3 * maxSize / 4), maxSize);
}

void CardDeck::initalizeSuit(std::string suit, int begining, int end)
{
	int num = 1;

	for (int i = begining; i < end; i++)
	{
		deck[i].number = num;
		deck[i].suit = suit;
		num++;
	}
}

void CardDeck::shuffle()
{
	for (int i = 0; i < size; i++)
	{
		int randomNumber = (rand() % 52);

		Card temp = deck[i];

		deck[i] = deck[randomNumber];
		deck[randomNumber] = temp;

	}
}

void CardDeck::reset()
{
	delete[] deck;

	size = maxSize;
	deck = new Card[maxSize];	 

	initalizeSuit("Hearts", 0, maxSize / 4);
	initalizeSuit("Clubs", maxSize / 4, maxSize / 2);
	initalizeSuit("Dimonds", maxSize / 2, (3 * maxSize / 4));
	initalizeSuit("Spades", (3 * maxSize / 4), maxSize);
}

void CardDeck::displayCards()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << std::right;
		
		std::cout << std::setw(2) << deck[i].number << " of ";

		std::cout << std::left;

		std::cout << std::setw(15) << deck[i].suit;

		if ((i + 1) % 4 == 0)
			std::cout << std::endl;
	}
}

bool CardDeck::isEmpty()
{
	return (size == 0);
}

bool CardDeck::isFull()
{
	return (size == maxSize);
}

Card CardDeck::peek()
{
	return deck[size - 1];
}

Card CardDeck::draw()
{
	if (!isEmpty())
	{
		Card temp = deck[size - 1];

		size--;

		return temp;
	}
}

int CardDeck::getSize()
{
	return size;
}

CardDeck::~CardDeck()
{
	delete [] deck;
}
