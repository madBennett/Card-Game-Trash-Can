/*
CS281 – Spring 2021
Card Game Project
Madison Bennett
29 May 2021
The purpose of this program is to play and test the game trash can
*/

#include "Player.h"

Player::Player()
{
	startingAmount = 10;
	currentAmount = startingAmount;
	roundWon = false;
	
	deck = new Card[startingAmount];
	completedDeck = new bool[startingAmount];
	
	for (int i = 0; i < currentAmount; i++)
	{
		completedDeck[i] = false;
	}
}

Card Player::useCard(CardDeck& PlayingDeck, Card& PlayingCard)
{
	Card temp;

	int cardIndex;

	switch (PlayingCard.number)
	{
	case 11: 
		//jack: place holder, need to replace to win

		std::cout << std::endl << "Which card would you like to replace: #";
		std::cin >> cardIndex;
		cardIndex -= 1;

		PlayingCard.isFlipped = true; 

		temp = deck[cardIndex];

		deck[cardIndex] = PlayingCard;

		temp.printCard();

		return temp;

		break;
	case 12: 
		//queen: end turn

		return PlayingCard;	
		
		break;
	case 13: 
		//king: draw again
		temp = PlayingDeck.draw();
		
		temp.printCard();

		return temp;

		break;
	default:
		cardIndex = (PlayingCard.number - 1);

		if (cardIndex >= currentAmount)
			return PlayingCard;

		if (isCardInDeck(PlayingCard))
		{
			return PlayingCard;
		}
		else
		{
			PlayingCard.isFlipped = true;

			temp = deck[cardIndex];

			deck[cardIndex] = PlayingCard;
			completedDeck[cardIndex] = true;

			return temp;
		}
	}
}

Card Player::useCardAI(CardDeck& PlayingDeck, Card& PlayingCard)
{
	Card temp;

	int cardIndex = 0;

	switch (PlayingCard.number)
	{
	case 11: 
		//jack: place holder, need to replace to win

		showDeck();

		PlayingCard.isFlipped = true;

		std::cout << std::endl << "Which card would you like to replace: #";

		//check for next open possition
		while (deck[cardIndex].isFlipped and cardIndex < currentAmount)
		{
			// old : (completedDeck[cardIndex] and cardIndex < currentAmount)
			cardIndex++;

			//skip if flipped jack
			if (deck[cardIndex].number == 11 and PlayingCard.isFlipped)
				cardIndex++;
		}

		//if no available space
		if (cardIndex == currentAmount)
		{
			std::cout << std::endl << "Cannot Place in deck." 
				<< std::endl << "Draw new card." << std::endl;

			if (PlayingDeck.isEmpty())
			{
				PlayingDeck.reset();
				PlayingDeck.shuffle();
			}
			
			PlayingCard = PlayingDeck.draw();

			return PlayingCard;
		}

		std::cout << cardIndex + 1 << std::endl;

		temp = deck[cardIndex];

		deck[cardIndex] = PlayingCard;

		return temp;

		break;
	case 12: 
		//queen: end turn
		return PlayingCard;

		break;
	case 13: 
		//king: draw again
		temp = PlayingDeck.draw();

		temp.printCard();

		return temp;

		break;
	default:
		cardIndex = (PlayingCard.number - 1);

		if (cardIndex >= currentAmount)
			return PlayingCard;

		if (isCardInDeck(PlayingCard))
		{
			return PlayingCard;
		}
		else
		{
			PlayingCard.isFlipped = true;

			temp = deck[cardIndex];

			deck[cardIndex] = PlayingCard;
			completedDeck[cardIndex] = true;

			return temp;
		}
	}
}

void Player::reset()
{
	delete[] deck;
	delete[] completedDeck;
}

void Player::nextRound(CardDeck& PlayingDeck)
{
	if (roundWon)
		if (currentAmount > 1)
			currentAmount--;
		else
			return; //if player has won game
	
	Card* tempDeck = new Card[currentAmount];
	bool* tempCompletedDeck = new bool[currentAmount];

	for (int i = 0; i < currentAmount; i++)
	{
		tempDeck[i] = PlayingDeck.draw();
	}

	for (int i = 0; i < currentAmount; i++)
	{
		tempCompletedDeck[i] = false;
	}

	reset();

	roundWon = false;

	deck = tempDeck;
	completedDeck = tempCompletedDeck;
}

void Player::setCurrentAmount(int newCurrentAmount)
{
	if (newCurrentAmount >= 1)
		currentAmount = newCurrentAmount;
}

void Player::showDeck()
{
	for (int i = 0; i < currentAmount; i++)
	{
		if (deck[i].isFlipped) //checking if it is a filled in card and thus visable
		{
			if (deck[i].number == 11)
				std::cout << "J ";
			else
				std::cout << deck[i].number << " ";
		}
		else
			std::cout << "X ";
		if ((i + 1) % 5 == 0) //puts cards on a new line so it is readable
			std::cout << std::endl;
	}
}

int Player::getCurrentAmount()
{
	return currentAmount;
}	 

bool Player::isCardInDeck(Card& PlayingCard)
{
	if (PlayingCard.number == 11 or PlayingCard.number == 12 or PlayingCard.number == 13)
		return false;
	
	if (PlayingCard.number - 1 >= currentAmount)
		return false;

	int cardIndex = PlayingCard.number - 1;

	return (completedDeck[cardIndex]);
}

bool Player::hasWonRound()
{
	int count = 0;

	while (completedDeck[count] and count < currentAmount)
		count++;

	roundWon = (count == currentAmount);

	return roundWon;
}

bool Player::hasWonGame()
{
	return (roundWon and (currentAmount == 1));
}

Player::~Player()
{
	reset();
}
