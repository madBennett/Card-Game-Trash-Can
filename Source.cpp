/*
CS281 – Spring 2021
Card Game Project
Madison Bennett
29 May 2021
The purpose of this program is to play and test the game trash can
*/

#include "CardDeck.h"
#include "Player.h"
#include <iomanip>

void playerTurn(Player&, CardDeck&, Card&, int);
int playerSubTurn(Player&, CardDeck&, Card&);
bool AITurn(Player&, CardDeck&, Card&, int);

void checkDeck(CardDeck&);

void clearScreen();
void pauseScreen();

int main()
{
	int input;
	int cardAmount = 0;
	bool endRound = false, endGame = false;
	
	CardDeck PlayingDeck;
	Card PlayingCard;

	Player Player1;
	Player Player2;
	
	//Title Screen
	for (int i = 0; i < 12; i++)
		std::cout << std::endl;

	std::cout << std::right;
	std::cout << std::setw(70) << "---Trash Can---" << std::endl;

	for (int i = 0; i < 12; i++)
		std::cout << std::endl;

	std::cout << std::right;
	std::cout << std::setw(75) << "---Enter to Continue!---" << std::endl;
	std::cin.get();

	clearScreen();
	
	//Title Menu
	do
	{
		for (int i = 0; i < 9; i++)
			std::cout << std::endl;

		std::cout << std::setw(70) << "---Trash Can---" << std::endl;

		for (int i = 0; i < 9; i++)
			std::cout << std::endl;

		std::cout << std::left;
		std::cout << std::setw(53) << " ";
		std::cout << std::setw(65) << "1. Play Game" << std::endl << std::endl;

		std::cout << std::setw(53) << " ";
		std::cout << std::setw(65) << "2. Rules" << std::endl << std::endl;

		std::cout << std::setw(53) << " ";
		std::cout << std::setw(65) << "3. Run Test Engine" << std::endl << std::endl;

		std::cout << std::setw(53) << " ";
		std::cout << std::setw(65) << "4. Exit" << std::endl << std::endl;

		std::cout << std::right;
		std::cout << std::endl << std::setw(52) << "Choice: ";
		std::cin >> input;

		clearScreen();

		checkDeck(PlayingDeck);

		switch (input)
		{
		case 1:
			PlayingDeck.shuffle();

			do
			{
				checkDeck(PlayingDeck);

				if (PlayingDeck.getSize() < (Player1.getCurrentAmount() + Player2.getCurrentAmount()))
				{
					PlayingDeck.reset();
					PlayingDeck.shuffle();
				}

				Player1.nextRound(PlayingDeck);
				Player2.nextRound(PlayingDeck);

				PlayingCard = PlayingDeck.draw();

				do
				{
					//Check if cards are left
					checkDeck(PlayingDeck);

					//Player Turn
					playerTurn(Player1, PlayingDeck, PlayingCard, 1);

					clearScreen();

					if (Player1.hasWonRound())
						break;

					checkDeck(PlayingDeck);

					//AI Turn
					while (!AITurn(Player2, PlayingDeck, PlayingCard, 2))
					{
						pauseScreen();

						if (Player2.hasWonRound())
							break;
					}

					pauseScreen();

					if (Player1.hasWonRound())
						endRound = true;
					else if (Player2.hasWonRound())
						endRound = true;
					else
						endRound = false;

				} while (!endRound);

				clearScreen();

				for (int i = 0; i < 9; i++)
					std::cout << std::endl;

				if (Player1.hasWonRound())
				{
					std::cout << std::setw(70) << "Player 1 has won the round!" << std::endl;

					endGame = Player1.hasWonGame();
				}
				else
				{
					std::cout << std::setw(70) << "Player 2 has won the round!" << std::endl;
					endGame = Player2.hasWonGame();
				}
				
				for (int i = 0; i < 12; i++)
					std::cout << std::endl;
				
				pauseScreen();

			} while (!endGame);

			if (Player1.hasWonGame())
			{
				for (int i = 0; i < 9; i++)
					std::cout << std::endl;
				
				std::cout << std::setw(70) << "Player 1 has won the game!" << std::endl;
				
				for (int i = 0; i < 12; i++)
					std::cout << std::endl;

			}
			else
			{
				for (int i = 0; i < 9; i++)
					std::cout << std::endl;

				std::cout << std::setw(70) << "Player 2 has won the game!" << std::endl;

				for (int i = 0; i < 12; i++)
					std::cout << std::endl;

			}

			break;
		case 2:
			std::cout << "\n\n" << std::right;
			std::cout << std::setw(80) << "---Rules of Trash Can---\n\n\n\n";

			std::cout << "-Each Player will start out with a deck of ten cards. They cannot look at the cards and they will remain face down."
				<< "\n\n-The player will then have the choice of drawing a card or using the top card of the 'Trash Can'"
				<< "\n\n-If the Player cannot use a card they have drawn they 'dispose' of it in the 'Trash Can'"
				<< "\n\n-If the Player draws a card they already have in their deck their turn will end."
				<< "\n\n-Kings, Queens, and Jacks are special cards."
					<< "\n\t-If a King is drawn the player will then draw again."
					<< "\n\t-If a Queen is drawn the player's turn ends."
					<< "\n\t-If a Jack is drawn it can be used as a placeholder for any card, though must be replaced to win."
				<< "\n\n-To win the round the player must replace each of the cards in their deck with the correspond number."
				<< "\n\n-After a player wins a round their deck will be reduced by one."
				<< "\n\n-To win the player must win a round with only one card."
				<< "\n\n";

			pauseScreen();

			break;
		case 3:
			do
			{
				std::cout << std::right;
				std::cout << std::setw(70) << "---Test Menu---" << std::endl;

				for (int i = 0; i < 9; i++)
					std::cout << std::endl;
				std::cout << std::left;
				std::cout << std::setw(53) << " ";
				std::cout << std::setw(65) << "1. Run Game at Any Round" << std::endl << std::endl;

				std::cout << std::setw(53) << " ";
				std::cout << std::setw(65) << "2. Run Card Test" << std::endl << std::endl;

				std::cout << std::setw(53) << " ";
				std::cout << std::setw(65) << "3. Exit" << std::endl << std::endl;

				std::cout << std::right;
				std::cout << std::endl << std::setw(52) << "Choice: ";
				std::cin >> input;

				switch (input)
				{
				case 1:	//broken fix
					std::cout << "Card Amount: ";
					std::cin >> cardAmount;
					
					PlayingDeck.reset();
					PlayingDeck.shuffle();

					while (cardAmount < 1)
					{
						std::cout << "Invaild input." << std::endl;
						std::cin >> cardAmount;
					}

					Player1.setCurrentAmount(cardAmount);
					Player2.setCurrentAmount(cardAmount);
					
					PlayingDeck.shuffle();

					do
					{
						checkDeck(PlayingDeck);

						if (PlayingDeck.getSize() < (cardAmount * 2))
						{
							PlayingDeck.reset();
							PlayingDeck.shuffle();
						}

						Player1.nextRound(PlayingDeck);
						Player2.nextRound(PlayingDeck);

						PlayingCard = PlayingDeck.draw();

						do
						{
							//Check if cards are left
							checkDeck(PlayingDeck);

							//Player Turn
							playerTurn(Player1, PlayingDeck, PlayingCard, 1);

							clearScreen();

							if (Player1.hasWonRound())
								break;

							checkDeck(PlayingDeck);

							//AI Turn
							while (!AITurn(Player2, PlayingDeck, PlayingCard, 2))
							{
								pauseScreen();

								if (Player2.hasWonRound())
									break;
							}

							pauseScreen();

							if (Player1.hasWonRound())
								endRound = true;
							else if (Player2.hasWonRound())
								endRound = true;
							else
								endRound = false;

						} while (!endRound);

						clearScreen();

						for (int i = 0; i < 9; i++)
							std::cout << std::endl;

						if (Player1.hasWonRound())
						{
							std::cout << std::setw(70) << "Player 1 has won the round!" << std::endl;

							endGame = Player1.hasWonGame();
						}
						else
						{
							std::cout << std::setw(70) << "Player 2 has won the round!" << std::endl;
							endGame = Player2.hasWonGame();
						}

						for (int i = 0; i < 12; i++)
							std::cout << std::endl;

						pauseScreen();

					} while (!endGame);

					if (Player1.hasWonGame())
					{
						for (int i = 0; i < 9; i++)
							std::cout << std::endl;

						std::cout << std::setw(70) << "Player 1 has won the game!" << std::endl;

						for (int i = 0; i < 12; i++)
							std::cout << std::endl;

					}
					else
					{
						for (int i = 0; i < 9; i++)
							std::cout << std::endl;

						std::cout << std::setw(70) << "Player 2 has won the game!" << std::endl;

						for (int i = 0; i < 12; i++)
							std::cout << std::endl;

					}
					
					break;
				case 2:		
					do
					{
						clearScreen();

						std::cout << std::right;
						std::cout << std::setw(75) << "---Card Deck Test Menu---" << std::endl;

						for (int i = 0; i < 6; i++)
							std::cout << std::endl;

						std::cout << std::left;
						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "1. Display Deck" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "2. Peek at Top Card" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "3. Draw Card" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "4. Get Size" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "5. Shuffle Deck" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "6. Reset Deck" << std::endl << std::endl;

						std::cout << std::setw(53) << " ";
						std::cout << std::setw(65) << "7. Exit to Test Engine" << std::endl << std::endl << std::endl;

						std::cout << std::right;
						std::cout << std::endl << std::setw(52) << "Choice: ";
						std::cin >> input;

						switch (input)
						{
						case 1:
							PlayingDeck.displayCards();

							break;
						case 2:
							PlayingCard = PlayingDeck.peek();

							std::cout << PlayingCard.number << " of " << PlayingCard.suit << std::endl;

							break;
						case 3:
							PlayingCard = PlayingDeck.draw();

							std::cout << PlayingCard.number << " of " << PlayingCard.suit << std::endl;

							break;
						case 4:
							std::cout << "The size of the deck is " << PlayingDeck.getSize() << " cards" << std::endl;
							
							break;
						case 5:
							PlayingDeck.shuffle();

							std::cout << "The Deck has been Shuffled" << std::endl;

							break;
						case 6:
							PlayingDeck.reset();

							std::cout << "The Deck has been Reset" << std::endl;

							break;
						case 7:
							std::cout << "Exiting to Test Engine..." << std::endl;
						}
						
						
						pauseScreen();
						clearScreen();
					} while (input != 7);
					break;
				case 3:
					break;
				default:
					std::cout << "Invaild Input";
				}

			} while (input != 3);

			break;
		case 4:
			break;
		default:
			std::cout << "Invaild Input";
		}
	} while (input != 4);

	return 0;
}

void playerTurn(Player& currentPlayer, CardDeck& PlayingDeck, Card& PlayingCard, int playerNumber)
{
	int input;
	
	do
	{
		clearScreen();

		std::cout << "Player " << playerNumber << "'s turn:" << std::endl;

		currentPlayer.showDeck();

		std::cout << std::endl;

		PlayingCard.printCard();

		std::cout << std::endl << "What would you like to do?" << std::endl
			<< "1. Use Card" << std::endl
			<< "2. Draw Card" << std::endl
			<< "3. End Turn" << std::endl
			<< "\tChoice: ";
		std::cin >> input;

		switch (input)
		{
		case 1:
			input = playerSubTurn(currentPlayer, PlayingDeck, PlayingCard);

			break;
		case 2:
			std::cout << std::endl << "Using New Current Card..." << std::endl;

			PlayingCard = PlayingDeck.draw();

			PlayingCard.printCard();

			input = playerSubTurn(currentPlayer, PlayingDeck, PlayingCard);

			break;
		case 3:
			std::cout << "End of Turn." << std::endl;
			pauseScreen();

			break;
		default:
			std::cout << "Invalid Input.";
			pauseScreen();
		}
	} while (input != 3);
}

int playerSubTurn(Player& currentPlayer, CardDeck& PlayingDeck, Card& PlayingCard)
{
	int input = 0;

	checkDeck(PlayingDeck);
	
	switch (PlayingCard.number)
	{
	case 11:
		std::cout << std::endl << "Jack Drawn" << std::endl;
		break;
	case 12:
		std::cout << std::endl << "Queen Drawn" << std::endl;
		break;
	case 13:
		std::cout << "King Drawn" << std::endl << "Draw Again" << std::endl;
		break;
	default:
		if (PlayingCard.number > currentPlayer.getCurrentAmount() and PlayingCard.number != 11
			and PlayingCard.number != 13)	//cant place card into deck
		{
			std::cout << "Cannot Place in deck." << std::endl;
			input = 3;
		}

		if (currentPlayer.isCardInDeck(PlayingCard))
		{
			//currentPlayer.showDeck();
			std::cout << std::endl << "Card is already in deck" << std::endl;
		}
	}
	PlayingCard = currentPlayer.useCard(PlayingDeck, PlayingCard);

	std::cout << std::endl;

	currentPlayer.showDeck();

	PlayingCard.printCard();

	//Card verification
	if (currentPlayer.isCardInDeck(PlayingCard) or PlayingCard.number == 12)
	{
		std::cout << std::endl << "End of turn" << std::endl;
		input = 3;
	}

	pauseScreen();

	return input;
}

bool AITurn(Player& currentPlayer, CardDeck& PlayingDeck, Card& PlayingCard, int playerNumber)
{
	//return true if turn over false if not
	clearScreen();

	std::cout << "Player " << playerNumber << "'s turn:" << std::endl;

	currentPlayer.showDeck();

	std::cout << std::endl;

	PlayingCard.printCard();

	if (currentPlayer.isCardInDeck(PlayingCard) or PlayingCard.number == 12 
		or PlayingCard.number > currentPlayer.getCurrentAmount())
	{
		if (PlayingCard.number != 13 and PlayingCard.number != 11)
		{
			checkDeck(PlayingDeck);

			std::cout << "Player Drew a card." << std::endl;

			PlayingCard = PlayingDeck.draw();

			PlayingCard.printCard();
		}
	}

	//Card verification
	if (PlayingCard.number > currentPlayer.getCurrentAmount() and PlayingCard.number != 11 
		and PlayingCard.number !=13)	//can place card into deck
	{
		std::cout << "Cannot Place in deck." << std::endl;
		return true;
	}

	if (currentPlayer.isCardInDeck(PlayingCard) or PlayingCard.number == 12)
	{
		std::cout << std::endl << "End of turn" << std::endl;
		return true;
	}

	switch (PlayingCard.number)
	{
	case 11:
		PlayingCard = currentPlayer.useCardAI(PlayingDeck, PlayingCard);

		//prevents infinate loop of jacks
		if (PlayingCard.number == 11. and PlayingCard.isFlipped)
		{
			checkDeck(PlayingDeck);

			PlayingCard = PlayingDeck.draw();
		}
		
		PlayingCard.printCard();
		//run again for card flipped by jack

		break;
	case 13:
		std::cout << "Draw Again" << std::endl;

		PlayingCard = PlayingDeck.draw();

		PlayingCard.printCard();

		break;
	}

	PlayingCard = currentPlayer.useCardAI(PlayingDeck, PlayingCard);

	std::cout << std::endl;

	currentPlayer.showDeck();

	return false;
}

void checkDeck(CardDeck& PlayingDeck)
{
	if (PlayingDeck.isEmpty())
	{
		PlayingDeck.reset();
		PlayingDeck.shuffle();
	}
}

void clearScreen()
{
	system("CLS");
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
}

void pauseScreen()
{
	std::cout << std::endl << std::endl;

	std::cout << std::right;
	std::cout << std::setw(75) << "---Enter to Continue!---" << std::endl;

	std::cin.clear();
	std::cin.ignore(1000, '\n');
	

	std::cin.get();
}