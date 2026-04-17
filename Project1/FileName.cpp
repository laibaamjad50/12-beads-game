#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector> 
#include <random>

using namespace std;

const int BOARD_SIZE = 5;
const float boxsize = 120.0f;
const float beadradius = boxsize / 6.5f;


void initializeBoard(char gameBoard[][BOARD_SIZE]);
void printBoard(char gameBoard[][BOARD_SIZE]);
int coinToss();
bool validCurrentPositionforPlayer1B(char gameBoard[][BOARD_SIZE], int row, int col);
bool validCurrentPositionforPlayer1Y(char gameBoard[][BOARD_SIZE], int row, int col);
bool validCurrentPositionforPlayer2Y(char gameBoard[][BOARD_SIZE], int row, int col);
bool validCurrentPositionforPlayer2B(char gameBoard[][BOARD_SIZE], int row, int col);
bool canMoveTheBead(char gameBoard[][BOARD_SIZE], int pr, int pc, int mr, int mc);
void movebead(char gameBoard[][BOARD_SIZE], int pr, int pc, int mr, int mc);
bool GameOver(char gameBoard[][BOARD_SIZE], char playerColor);
void DrawBoard(char gameBoard[][BOARD_SIZE], sf::RenderWindow& window);
void endscreen(string s);
void startGame();
void drawStartScreen();


int main()
{
	drawStartScreen();
	return 0;
}

void DrawBoard(char gameBoard[][BOARD_SIZE], sf::RenderWindow& window)
{
	
	sf::CircleShape bead(beadradius);
	bead.setOutlineThickness(4);
	bead.setOutlineColor(sf::Color::Black);

	sf::Color color;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			float x = j * boxsize + boxsize / 2;
			float y = i * boxsize + boxsize / 2 + 100;

			if (i == 0 && j == 0) {
				//diagnol lines
				sf::Vertex line3[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x + boxsize * 4, y + boxsize * 4), sf::Color::Magenta)
				};
				line3[0].color = sf::Color::Magenta;
				line3[1].color = sf::Color::Magenta;
				line3[0].position -= sf::Vector2f(1, 1);
				line3[1].position -= sf::Vector2f(1, 1);
				window.draw(line3, 2, sf::Lines);

			}
			else if (i == 0 && j == BOARD_SIZE - 1) {
				//second diagnol line
				sf::Vertex line3[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x - boxsize * 4, y + boxsize * 4), sf::Color::Magenta)
				};
				line3[0].color = sf::Color::Magenta;
				line3[1].color = sf::Color::Magenta;
				line3[0].position -= sf::Vector2f(1, 1);
				line3[1].position -= sf::Vector2f(1, 1);
				window.draw(line3, 2, sf::Lines);
			}


			if (j >= 0 && j <= BOARD_SIZE - 1 && i == 0) {
				//vertical lines
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x, y + (BOARD_SIZE - 1) * boxsize - boxsize * i), sf::Color::Magenta)
				};
				line[0].color = sf::Color::Magenta;
				line[1].color = sf::Color::Magenta;
				line[0].position -= sf::Vector2f(1, 1);
				line[1].position -= sf::Vector2f(1, 1);
				window.draw(line, 2, sf::Lines);
			}

			if (i >= 0 && i <= BOARD_SIZE - 1 && j == 0) {
				//horizontal lines
				sf::Vertex line2[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x + (BOARD_SIZE - 1) * boxsize - boxsize * j, y), sf::Color::Magenta)
				};
				line2[0].color = sf::Color::Magenta;
				line2[1].color = sf::Color::Magenta;
				line2[0].position -= sf::Vector2f(1, 1);
				line2[1].position -= sf::Vector2f(1, 1);
				window.draw(line2, 2, sf::Lines);
			}

			if (i == 0 && j == 2 || i == 2 && j == 0)
			{
				sf::Vertex line3[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x + boxsize * 2, y + boxsize * 2), sf::Color::Magenta)
				};
				line3[0].color = sf::Color::Magenta;
				line3[1].color = sf::Color::Magenta;
				line3[0].position -= sf::Vector2f(1, 1);
				line3[1].position -= sf::Vector2f(1, 1);
				window.draw(line3, 2, sf::Lines);
			}

			if (i == 0 && j == 2 || i == 2 && j == BOARD_SIZE - 1)
			{
				sf::Vertex line3[] =
				{
					sf::Vertex(sf::Vector2f(x, y), sf::Color::Magenta),
					sf::Vertex(sf::Vector2f(x - boxsize * 2, y + boxsize * 2), sf::Color::Magenta)
				};
				line3[0].color = sf::Color::Magenta;
				line3[1].color = sf::Color::Magenta;
				line3[0].position -= sf::Vector2f(1, 1);
				line3[1].position -= sf::Vector2f(1, 1);
				window.draw(line3, 2, sf::Lines);
			}

			if ((gameBoard[i][j] == 'B')) {
				bead.setPosition(x - beadradius, y - beadradius);
				bead.setFillColor(sf::Color::Blue);
				window.draw(bead);
			}
			else if ((gameBoard[i][j] == 'Y')) {
				bead.setPosition(x - beadradius, y - beadradius);
				bead.setFillColor(sf::Color::Yellow);
				window.draw(bead);
			}
		}
	}
}

void endscreen(string s)
{
	sf::RenderWindow window(sf::VideoMode(600, 700), "Bead Game", sf::Style::Resize | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error loading font!" << endl;
	}

	sf::Text title;
	title.setFont(font);
	title.setString("Game Over");
	title.setCharacterSize(60); 
	title.setFillColor(sf::Color::Blue); 
	title.setStyle(sf::Text::Bold);
	title.setPosition(150, 170); 

	sf::Text winner;
	winner.setFont(font);
	winner.setString(s);
	winner.setCharacterSize(60); 
	winner.setFillColor(sf::Color::White);
	winner.setStyle(sf::Text::Bold);
	winner.setPosition(130, 300); 

	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("background.jpg")) {
		cout << "Error loading background image!" << endl;
	}
	sf::Sprite background(bgTexture);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			else if (e.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			}

			else if (e.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		
		window.clear();
	   // background 
		window.draw(background);
		//background text
		window.draw(title);
		window.draw(winner);
		window.display();

	}
}

void startGame()
{
	char gameBoard[BOARD_SIZE][BOARD_SIZE];
	initializeBoard(gameBoard);
	sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * boxsize, BOARD_SIZE * boxsize + 100), "Bead Game");
	window.setFramerateLimit(60);
	sf::RenderWindow inputwindow(sf::VideoMode(BOARD_SIZE * boxsize, BOARD_SIZE * boxsize + 100), "Bead Game");
	inputwindow.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		
		cout << "Error loading font!" << endl;
		return;
	}

	sf::Text playerTurnText;
	playerTurnText.setFont(font);
	playerTurnText.setCharacterSize(50);
	playerTurnText.setFillColor(sf::Color::White);
	playerTurnText.setStyle(sf::Text::Bold);
	playerTurnText.setPosition(150, 50);

	sf::Text player1;
	player1.setFont(font);
	player1.setCharacterSize(20);
	player1.setFillColor(sf::Color::White);

	sf::Text player2;
	player2.setFont(font);
	player2.setCharacterSize(20);
	player2.setFillColor(sf::Color::White);


	int selectedRow = -1;
	int selectedCol = -1;
	int coin;
	int check = 0;

	string player1ColorInput;
	bool colorInputReceived = false;

	while (inputwindow.isOpen()) {
		sf::Event event;
		while (inputwindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				inputwindow.close();
				return;
			}
			else if (!colorInputReceived && event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == '\b' && player1ColorInput.size() > 0) { //backspace code
						player1ColorInput.pop_back();
					}
					else if (event.text.unicode == 13) { // Enterkey code

						if (player1ColorInput == "Blue" || player1ColorInput == "blue") {
							player1.setString("Blue");
							check = 1;
							colorInputReceived = true;
						}
						else if (player1ColorInput == "Yellow" || player1ColorInput == "yellow") {
							player1.setString("Yellow");
							check = 2;
							colorInputReceived = true;
						}
						else {
							cout << "Invalid input!" << endl;
						}
					}
					else {
						player1ColorInput += static_cast<char>(event.text.unicode);
					}
				}
			}
		}

		sf::Texture bgTexture;
		if (!bgTexture.loadFromFile("background.jpg")) {
			cout << "Error loading background image " << endl;
		}
		sf::Sprite background(bgTexture);
		inputwindow.draw(background);
		if (!colorInputReceived) {
			sf::Text colorInputText;
			colorInputText.setFont(font);
			colorInputText.setCharacterSize(30);
			colorInputText.setStyle(sf::Text::Bold);
			colorInputText.setFillColor(sf::Color::White);
			colorInputText.setString("Player 1 Color : Blue/Yellow \n\t\t\t\t\t\t" + player1ColorInput);
			colorInputText.setPosition(20, 250);
			inputwindow.draw(colorInputText);
		}
		else {
			inputwindow.draw(player1);
			inputwindow.draw(player2);
			inputwindow.close();
			
		}

		inputwindow.display();
	}
	if (check == 1) {
		player2.setString("Yellow");
	}
	else if (check == 2)
	{
		player2.setString("Blue");
	}


	coin = coinToss();
	while (window.isOpen())                 // main loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					int col = mousePos.x / boxsize;
					int row = (mousePos.y - 100) / boxsize;

					if (selectedRow == -1 && selectedCol == -1)
					{
						// First click
						if (coin == 1 && player1.getString() == "Blue" && validCurrentPositionforPlayer1B(gameBoard, row, col))
						{
							selectedRow = row;
							selectedCol = col;
						}
						else if (coin == 1 && player1.getString() == "Yellow" && validCurrentPositionforPlayer1Y(gameBoard, row, col))
						{
							selectedRow = row;
							selectedCol = col;
						}
						else if (coin == 2 && player2.getString() == "Blue" && validCurrentPositionforPlayer2B(gameBoard, row, col))
						{
							selectedRow = row;
							selectedCol = col;
						}
						else if (coin == 2 && player2.getString() == "Yellow" && validCurrentPositionforPlayer2Y(gameBoard, row, col))
						{
							selectedRow = row;
							selectedCol = col;
						}
					}
					else
					{
						// Second click
						int moveRow = row;
						int moveCol = col;

						if (canMoveTheBead(gameBoard, selectedRow, selectedCol, moveRow, moveCol))
						{
							if (coin == 1)
							{
								cout << "Player 1's turn" << endl;
								movebead(gameBoard, selectedRow, selectedCol, moveRow, moveCol);
								printBoard(gameBoard);
								if (GameOver(gameBoard, 'B'))
								{
									cout << "Game over! Player 1 wins" << endl;
									window.close();
									endscreen("Player 1 wins");
								}
								if (GameOver(gameBoard, 'Y'))
								{
									cout << "Game over! Player 1 wins" << endl;
									window.close();
									endscreen("Player 1 wins");
								}
								coin = 2;
							}
							else if (coin == 2)
							{
								cout << "Player 2's turn" << endl;
								movebead(gameBoard, selectedRow, selectedCol, moveRow, moveCol);
								printBoard(gameBoard);
								if (GameOver(gameBoard, 'Y'))
								{
									cout << "Game over! Player 2 wins" << endl;
									window.close();
									endscreen("Player 2 wins");
								}
								if (GameOver(gameBoard, 'B'))
								{
									cout << "Game over! Player 2 wins" << endl;
									window.close();
									endscreen("Player 2 wins");
								}
								coin = 1;
							}
						}
						else
						{
							cout << "Invalid move position!" << endl;
						}

						// Reset the selected bead
						selectedRow = -1;
						selectedCol = -1;
					}
				}
			}
		}
		sf::Color boardColor(5, 20, 25); 


		window.clear(boardColor);
		DrawBoard(gameBoard, window);

		//  player turn 
		if (coin == 1)
		{
			playerTurnText.setString("Player 1 turn");
		}
		else if (coin == 2)
		{
			playerTurnText.setString("Player 2 turn");
		}

		
		window.draw(playerTurnText);
		window.display();

	}
}

void drawStartScreen() {
	sf::RenderWindow window(sf::VideoMode(600, 700), "Bead Game", sf::Style::Resize | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error loading font!" << endl;
	}

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	playOption.setCharacterSize(50); 
	playOption.setFillColor(sf::Color::White);
	playOption.setStyle(sf::Text::Bold);
	playOption.setPosition(250, 250); 

	sf::Text quitOption;
	quitOption.setFont(font);
	quitOption.setString("Quit");
	quitOption.setCharacterSize(50); 
	quitOption.setFillColor(sf::Color::White);
	quitOption.setStyle(sf::Text::Bold);
	quitOption.setPosition(250, 350); 

	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("background.jpg")) {
		cout << "Error loading background image!" << endl;
	}
	sf::Sprite background(bgTexture);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			else if (e.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (e.mouseButton.button == sf::Mouse::Left) {
					if (playOption.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						cout << "Play option clicked!" << endl;
						//  starting game
						window.close();
						startGame();
					}
					else if (quitOption.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						cout << "Quit option clicked!" << endl;
						window.close();
					}
				}
			}

			else if (e.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		
		window.clear();
	
		window.draw(background);
		
		window.draw(playOption);
		window.draw(quitOption);
		window.display();

	}
}

void initializeBoard(char gameBoard[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (((i * BOARD_SIZE) + j) < 12)
            {
                gameBoard[i][j] = 'B';
            }
            else if (((i * BOARD_SIZE) + j) == 12)
            {
                gameBoard[i][j] = 'O';
            }
            else if (((i * BOARD_SIZE) + j) > 12)
            {
                gameBoard[i][j] = 'Y';
            }
        }
    }
}


void printBoard(char gameBoard[][BOARD_SIZE])
{
     cout <<  endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
             cout << gameBoard[i][j] << " ";
        }
         cout <<  endl;
    }
}

int coinToss()
{
     random_device rd;
     mt19937 gen(rd());
     uniform_int_distribution<> dis(1, 2);
    return dis(gen); 
}

bool validCurrentPositionforPlayer1B(char gameBoard[][BOARD_SIZE], int row, int col)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && gameBoard[row][col] == 'B')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validCurrentPositionforPlayer1Y(char gameBoard[][BOARD_SIZE], int row, int col)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && gameBoard[row][col] == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validCurrentPositionforPlayer2Y(char gameBoard[][BOARD_SIZE], int row, int col)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && gameBoard[row][col] == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validCurrentPositionforPlayer2B(char gameBoard[][BOARD_SIZE], int row, int col)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && gameBoard[row][col] == 'B')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool canMoveTheBead(char gameBoard[][BOARD_SIZE],int pr, int pc , int mr, int mc)
{
    int diffR = abs(mr - pr);
    int diffC = abs(mc - pc);
    
    if (!(mr >= 0 && mr < BOARD_SIZE && mc >= 0 && mc < BOARD_SIZE && gameBoard[mr][mc] == 'O'))
    {
        return false;
    }
    else if (((diffR == 1 && diffC == 0) || (diffR == 0 && diffC == 1) || (diffR == 1 && diffC == 1)) && ((pr % 2 == 0 && pc % 2 != 0 && mr % 2 != 0 && mc % 2 == 0) || (pr % 2 != 0 && pc % 2 == 0 && mr % 2 == 0 && mc % 2 != 0)))
    {
        // diagonal check 
        return false;
    }
    else if ((diffR == 2 && diffC == 2) && ((pr % 2 == 0 && pc % 2 != 0 && mr-1 % 2 != 0 && mc-1 % 2 == 0) || (pr % 2 != 0 && pc % 2 == 0 && mr-1 % 2 == 0 && mc-1 % 2 != 0)))
    {
        return false;
    }
    else if (pr < mr && diffR == 2 && diffC == 0 && (gameBoard[pr][pc] == gameBoard[pr + 1][pc] || gameBoard[pr + 1][pc] == 'O'))
    {
        // color check increasing row
        return false;
    }
    else if (pr > mr && diffR == 2 && diffC == 0 && (gameBoard[pr][pc] == gameBoard[pr - 1][pc] || gameBoard[pr - 1][pc] == 'O'))
    {
        // color check decreasing row
        return false;
    }
    else if (pc < mc && diffR == 0 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr][pc + 1] || gameBoard[pr][pc + 1] == 'O'))
    {
        // color check increasing col
        return false;
    }
    else if (pc > mc && diffR == 0 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr][pc - 1] || gameBoard[pr][pc - 1] == 'O'))
    {
        // color check decreasing col
        return false;
    }
    else if (pc < mc && pr<mr&& diffR == 2 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr + 1][pc + 1] || gameBoard[pr + 1][pc + 1] == 'O'))
    {
        // increasing diagonals through col
        return false;
    }
    else if (pc < mc && pr > mr && diffR == 2 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr - 1][pc + 1] || gameBoard[pr - 1][pc + 1] == 'O'))
    {
        // decreasing diagonals through col
        return false;
    }
    else if ( pc > mc && pr < mr && diffR == 2 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr + 1][pc - 1] || gameBoard[pr + 1][pc - 1] == 'O'))
    {
        // decreasing diagonals through row
        return false;
    }
    else if ( pc > mc && pr > mr && diffR == 2 && diffC == 2 && (gameBoard[pr][pc] == gameBoard[pr - 1][pc - 1] || gameBoard[pr - 1][pc - 1] == 'O'))
    {
        // increasing diagonals through row
        return false;
    }
    else if (gameBoard[pr][pc] == gameBoard[mr][mc])
    {
        return false;
    }
    else if ((diffR == 1 && diffC == 0) || (diffR == 0 && diffC == 1) || (diffC == 1 && diffR == 1) || (diffR == 2 && diffC == 0) || (diffR == 0 && diffC == 2) || (diffR == 2 && diffC == 2))
    {
        // two lines 
        if (mr >= 0 && mr < BOARD_SIZE && mc >= 0 && mc < BOARD_SIZE && gameBoard[mr][mc] == 'O')
        {
            return true;
        }
    }
    else 
        return false;
}

void movebead(char gameBoard[][BOARD_SIZE], int pr, int pc, int mr, int mc)
{
    int diffR =  abs(mr - pr);
    int diffC =  abs(mc - pc);

    if ((diffR == 1 && diffC == 0) || (diffR == 0 && diffC == 1) || (diffC == 1 && diffR == 1))
    {
        //  adjacent or diagonal position movement
         swap(gameBoard[pr][pc], gameBoard[mr][mc]);
    }
    else if ((diffR == 2 && diffC == 0) || (diffR == 0 && diffC == 2) || (diffR == 2 && diffC == 2))
    {
        // neighboring bead jump
        int r = (pr + mr) / 2;
        int c = (pc + mc) / 2;

        if (gameBoard[r][c] != 'O')
        {
             swap(gameBoard[pr][pc], gameBoard[mr][mc]);
            gameBoard[r][c] = 'O';
        }
    }
}

bool GameOver(char gameBoard[][BOARD_SIZE], char playerColor)
{
    char opponentColor;
    if (playerColor == 'B')
    {
        opponentColor = 'Y';
    }
    else
    {
        opponentColor = 'B';
    }

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (gameBoard[i][j] == opponentColor)
            {
                return false; 
            }
        }
    }
    return true; 
}