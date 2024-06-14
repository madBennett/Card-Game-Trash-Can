/*
CS281 – Spring 2021
Card Game Project
Madison Bennett
29 May 2021
The purpose of this program is to play and test the game trash can
*/

#pragma once
#include <iostream>

class Card
{
	public:
		int number;
		std::string suit;
		bool isFlipped;

		Card() { number = 0; suit = ""; isFlipped = false; }
		void printCard()
		{
			std::cout << std::endl << "Current Card is ";
			switch (number)
			{
			case 11:
				std::cout << "Jack of ";
				break;
			case 12:
				std::cout << "Queen of ";
				break;
			case 13:
				std::cout << "King of ";
				break;
			default:
				std::cout << number << " of ";
			}

			std::cout << suit << std::endl;
		}
};

class CardDeck
{
	private:
		int maxSize;
		int size;
		Card* deck;
		void initalizeSuit(std::string, int, int);

	public:
		CardDeck();

		void shuffle();
		void reset();
		void displayCards();

		bool isFull();
		bool isEmpty();

		Card peek();
		Card draw();
		int getSize();

		~CardDeck();
};

