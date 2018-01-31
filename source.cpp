#include <iostream>
#include <windows.h>
#include <string.h>
#include <cctype>

using namespace std;

const int DEBUG = 1;
const int BOARDSIZE = 20;
const char a[5] = "YBGR";
const char b[5] = "ybgr";
const int color[4] = { 224, 176, 160, 192 };

HANDLE  hConsole;


void setup_b(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2]);
void setup_p(char pieces[4][21][5][5]);
void print_board(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2]);
int place_piece(int playerNumber, int piece, int orientation, int flip, int boardX, int boardY, char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2], char pieces[4][21][5][5]);
int check_piece(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2], int boardX, int boardY, int playerNumber, int orientation, int piece);
void lower_board(int q, char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2]);
void print_board(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2]);
void erase(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2]);
int game_over(int turnCounter);
void ori(int orientation, int playerNumber, int piece, char pieces[4][21][5][5], char result[5][5]);
void print_pieces(char pieces[4][21][5][5], int playerNumber, int usedPieces[4][21]);
void flip_piece(int flip, int playerNumber, int piece, char turned[5][5], char result[5][5]);

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int boardX = 1;
	char boardXChar[100];
	int turnCounter = 0;
	int boardY = 1;
	char boardYChar[100];
	int piece = 0;
	char pieceChar[100];
	int orientation = 0;
	char flip1[100];
	int flip;
	char orientationChar[100];
	int playerNumber = 0;
	char pieces[4][21][5][5];
	char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2];
	int usedPieces[4][21];
	int playAgain = 0;
	char playAgainChar[100];
	int go = 0;
	int v = 0;
	int v1 = 0;
	int v2 = 0;
	int v3 = 0;
	int passes[4];
	while (playAgain == 0)
	{
		for (int x = 0; x < 4; x++)
		{
			passes[x] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				usedPieces[i][j] = 1;
			}
		}
		setup_b(gameBoard);
		setup_p(pieces);
		int playerCounter = 0;
		system("cls");
		cout << "Welcome to Blokus!\n";
		cout << "By: Benjy Firester and Hovey Hu\n";
		cout << "Enjoy!\n";
		while (game_over(turnCounter) != 0 || go < 3)
		{
			for (int x = 0; x < 100; x++)
			{
				pieceChar[x] = '\0';
				boardXChar[x] = '\0';
				boardYChar[x] = '\0';
				orientationChar[x] = '\0';
				playAgainChar[x] = '\0';
				flip1[x] = '\0';
			}
			int q = 0;
			int y = 0;
			int r = 0;
			print_board(gameBoard);
			print_pieces(pieces, playerNumber, usedPieces);
			cout << "It is player " << playerNumber + 1 << "'s turn\n\n";
			if (passes[playerNumber] == 0)
			{
				if (turnCounter > 39)
				{

					cout << "Do you want to pass? y for yes, n for no.\n";
					char pass[100];
					cin.getline(pass, 100);
					cin.ignore(100000, '\n');
					while (pass[0] != 'y' && pass[0] != 'n')
					{
						cout << "Please enter a valid value for pass.\n";
						cin.getline(pass, 100);
						cin.ignore(100000, '\n');
					}
					if (pass[0] == 'y')
					{
						q = 1;
						r = 1;
						y = 1;
						go++;
						passes[playerNumber] = 1;
					}
				}
				while (q == 0 || r == 0 || y == 0)
				{

					cout << "what piece do you want to play?\n";
					cin.getline(pieceChar,100);
					while (v == 0)
					{
						v = 1;
						for (int x = 0; x < strlen(pieceChar); x++)
						{
							if (!isdigit(pieceChar[x]))
							{
								v = 0;
								cout << "Enter in an integer for a piece.\n";
								cin.getline(pieceChar, 100);
								break;
							}
						}
						if (v == 1)
						{
							piece = atoi(pieceChar) - 1;
							while (piece < 1 || piece > 21)
							{
								v = 0;
								cout << "Enter a valid piece.\n";
								cin.getline(pieceChar, 100);
								break;
							}
						}
					}

					cout << "where do you want to play the piece (the block in gray)?\n";
					cin.getline(boardXChar, 100);

					while (v1 == 0)
					{
						v1 = 1;
						for (int x = 0; x < strlen(boardXChar); x++)
						{
							if (!isdigit(boardXChar[x]))
							{
								v1 = 0;
								cout << "Enter in an integer for a coordinates.\n";
								cin.getline(boardXChar, 100);
								break;
							}
						}
						if (v1 == 1)
						{
							boardX = atoi(boardXChar);
							while (boardX < 1 || boardX > 20)
							{
								v1 = 0;
								cout << "Enter a valid coordinate.\n";
								cin.getline(boardXChar, 100);
								break;
							}
						}
					}
					cin.getline(boardYChar, 100);
					while (v2 == 0)
					{
							v2 = 1;
							for (int x = 0; x < strlen(boardYChar); x++)
							{
								if (!isdigit(boardYChar[x]))
								{
									v2 = 0;
									cout << "Enter in an integer for a coordinate.\n";
									cin.getline(boardYChar, 100);
									break;
								}
							}
							if (v2 == 1)
							{
								boardX = atoi(boardYChar);
								while (boardY < 1 || boardY > 20)
								{
									v2 = 0;
									cout << "Enter a valid coordinate.\n";
									cin.getline(boardYChar, 100);
									break;
								}
							}
					}
					
					cout << "What orientation do you want?(orientation 0:" << char(24) << " 1:" << char(26) << " 2:" << char(25) << " 3:" << char(27) << " \n";
					cin.getline(orientationChar, 100);
					while (v3 == 0)
					{
						v3 = 1;
						for (int x = 0; x < strlen(orientationChar); x++)
						{
							if (!isdigit(orientationChar[x]))
							{
								v3 = 0;
								cout << "Enter in an integer for orientation.\n";
								cin.getline(orientationChar, 100);
								break;
							}
						}
						while (orientation < 0 || orientation > 3)
						{
							v3 = 0;
							cout << "Enter a valid orientation.\n";
							cin.getline(orientationChar, 100);
						}
					}
					cout << "Do you want to flip the piece? (Mirror's the piece vertically) Type in a y for  yes, and a n for no.\n";
					cin.getline(flip1, 100);
					cin.ignore(100000, '\n');
					while (flip1[0] != 'y' && flip1[0] != 'n')
					{
						cout << "Please enter a valid value for flip.\n";
						cin.getline(flip1, 100);
						cin.ignore(100000, '\n');
					}
					if (flip1[0] == 'y')
					{
						flip = 1;
					}
					else
					{
						flip = 0;
					}
					y = usedPieces[playerNumber][piece];
					r = place_piece(playerNumber, piece, orientation, flip, boardX, boardY, gameBoard, pieces);
					if (r == 0)
					{
						erase(gameBoard);
						//system("cls");
						SetConsoleTextAttribute(hConsole, 207);
						cout << "Play a piece that does not overlap any other pieces(DO NOT STEP ON PIECES!). \nRe-input the piece.\n";
						SetConsoleTextAttribute(hConsole, 7);
					}
					else
					{
						q = check_piece(gameBoard, boardX, boardY, playerNumber, orientation, piece);
						if (r == 1 && q == 1 && y == 1)
						{
							lower_board(q, gameBoard);
							playerCounter = (playerCounter + 1) % 4;
							usedPieces[playerNumber][piece] = 0;

						}
						else
						{
							erase(gameBoard);
							if (y == 0)
							{
								cout << "Play a piece you did not already use.\n";
							}
							else
							{
								//system("cls");
								SetConsoleTextAttribute(hConsole, 207);
								cout << "Play a piece that does not border another piece of its own color and is diagonal to a piece of its own color. Re-input the piece.(FOLLOW THE RULE!)\n";
								SetConsoleTextAttribute(hConsole, 7);
							}

						}
					}

				}
			}
			if (go == 3)
			{
				break;
			}
			system("cls");
			playerNumber = (playerNumber + 1) % 4;
			turnCounter++;

		}
		cout << "player number " << playerNumber + 2 << " wins!\n";
		cout << "Would you like to play again? (y for yes, n for no)\n";
		cin.getline(playAgainChar, 100);
		cin.ignore(100000, '\n');
		while (playAgainChar[0] != 'y' && playAgainChar[0] != 'n')
		{
			cout << "Please enter a valid value for play again.\n";
			cin.getline(playAgainChar, 100);
			cin.ignore(100000, '\n');
		}
		if (playAgainChar[0] == 'y')
		{
			playAgain = 0;
		}
		else
		{
			playAgain = 1;
		}

	}

	cout << "I hope you liked our game!\n";
	system("pause");

	return 0;
}

void print_pieces(char pieces[4][21][5][5], int playerNumber, int usedPieces[4][21])
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
	//line 1:0~7
	for (int i = 0; i < 7; i++)
	{
		if (usedPieces[playerNumber][i] == 1)
		{
			cout << i + 1 << "         ";
		}
	}
	cout << endl;

	for (int x = 0; x < 5; x++)
	{
		for (int p = 0; p < 7; p++)
		{
			for (int y = 0; y < 5; y++)
			{
				if (pieces[playerNumber][p][x][y] == b[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, color[playerNumber]); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == a[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 114); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == ' '&&usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 7); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl;
	for (int i = 7; i < 14; i++)
	{
		if (usedPieces[playerNumber][i] == 1)
		{
			cout << i + 1 << "         ";
		}
	}
	cout << endl;
	for (int x = 0; x < 5; x++)
	{
		for (int p = 7; p < 14; p++)
		{
			for (int y = 0; y < 5; y++)
			{
				if (pieces[playerNumber][p][x][y] == b[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, color[playerNumber]); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == a[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 114); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == ' '&&usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 7); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl;
	for (int i = 14; i < 21; i++)
	{
		if (usedPieces[playerNumber][i] == 1)
		{
			cout << i + 1 << "         ";
		}
	}
	cout << endl;
	for (int x = 0; x < 5; x++)
	{
		for (int p = 14; p < 21; p++)
		{
			for (int y = 0; y < 5; y++)
			{
				if (pieces[playerNumber][p][x][y] == b[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, color[playerNumber]); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == a[playerNumber] && usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 114); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
				if (pieces[playerNumber][p][x][y] == ' '&&usedPieces[playerNumber][p] == 1)
				{
					SetConsoleTextAttribute(hConsole, 7); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void setup_b(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2])
{

	for (int x = 0; x < BOARDSIZE + 2; x++)
	{
		for (int y = 0; y < BOARDSIZE + 2; y++)
		{
			gameBoard[x][y] = ' ';
		}
	}
	gameBoard[0][0] = 'y';
	gameBoard[0][21] = 'b';
	gameBoard[21][21] = 'g';
	gameBoard[21][0] = 'r';
	for (int y = 1; y < BOARDSIZE + 1; y++)
	{
		gameBoard[0][y] = 'p';
	}
	for (int y = 1; y < BOARDSIZE + 1; y++)
	{
		gameBoard[21][y] = 'p';
	}
	for (int x = 1; x < BOARDSIZE + 1; x++)
	{
		gameBoard[x][0] = 'p';
	}
	for (int x = 1; x < BOARDSIZE + 1; x++)
	{
		gameBoard[x][21] = 'p';
	}
}

void setup_p(char pieces[4][21][5][5])

{
	// a color-yellow

	for (int m = 0; m < 21; m++)

	{

		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				pieces[0][m][i][j] = ' ';

			}

		}

	}

	// piece 0 

	pieces[0][0][0][0] = 'Y';

	// piece 1

	pieces[0][1][0][0] = 'Y';

	pieces[0][1][1][0] = 'y';

	//2

	pieces[0][2][0][0] = 'Y';

	pieces[0][2][1][0] = 'y';

	pieces[0][2][2][0] = 'y';

	//4

	pieces[0][4][0][0] = 'Y';

	pieces[0][4][1][0] = 'y';

	pieces[0][4][2][0] = 'y';

	pieces[0][4][3][0] = 'y';

	//6

	pieces[0][6][0][0] = 'Y';

	pieces[0][6][1][0] = 'y';

	pieces[0][6][2][0] = 'y';

	pieces[0][6][1][1] = 'y';

	//8

	pieces[0][8][0][0] = 'Y';

	pieces[0][8][1][0] = 'y';

	pieces[0][8][2][0] = 'y';

	pieces[0][8][2][1] = 'y';

	//10

	pieces[0][10][0][0] = 'Y';

	pieces[0][10][1][0] = 'y';

	pieces[0][10][2][0] = 'y';

	pieces[0][10][3][0] = 'y';

	pieces[0][10][3][1] = 'y';

	//12

	pieces[0][12][0][0] = 'Y';

	pieces[0][12][1][0] = 'y';

	pieces[0][12][2][0] = 'y';

	pieces[0][12][1][1] = 'y';

	pieces[0][12][2][1] = 'y';

	//14

	pieces[0][14][0][0] = 'Y';

	pieces[0][14][0][1] = 'y';

	pieces[0][14][1][1] = 'y';

	pieces[0][14][1][2] = 'y';

	pieces[0][14][2][1] = 'y';

	//16

	pieces[0][16][0][0] = 'Y';

	pieces[0][16][0][2] = 'y';

	pieces[0][16][1][1] = 'y';

	pieces[0][16][1][2] = 'y';

	pieces[0][16][1][0] = 'y';

	//18

	pieces[0][18][0][0] = 'Y';

	pieces[0][18][0][1] = 'y';

	pieces[0][18][1][1] = 'y';

	pieces[0][18][2][1] = 'y';

	pieces[0][18][2][2] = 'y';



	pieces[0][3][0][0] = 'Y';

	pieces[0][3][1][0] = 'y';

	pieces[0][3][1][1] = 'y';

	pieces[0][5][0][0] = 'Y';

	pieces[0][5][0][1] = 'y';

	pieces[0][5][1][1] = 'y';

	pieces[0][5][1][0] = 'y';

	pieces[0][7][0][0] = 'Y';

	pieces[0][7][1][0] = 'y';

	pieces[0][7][1][1] = 'y';

	pieces[0][7][2][1] = 'y';

	pieces[0][9][0][0] = 'Y';

	pieces[0][9][1][0] = 'y';

	pieces[0][9][2][0] = 'y';

	pieces[0][9][3][0] = 'y';

	pieces[0][9][4][0] = 'y';

	pieces[0][11][0][0] = 'Y';

	pieces[0][11][1][0] = 'y';

	pieces[0][11][2][0] = 'y';

	pieces[0][11][2][1] = 'y';

	pieces[0][11][2][2] = 'y';

	pieces[0][13][0][0] = 'Y';

	pieces[0][13][1][0] = 'y';

	pieces[0][13][1][1] = 'y';

	pieces[0][13][2][1] = 'y';

	pieces[0][13][2][2] = 'y';

	pieces[0][15][0][0] = 'Y';

	pieces[0][15][1][0] = 'y';

	pieces[0][15][1][1] = 'y';

	pieces[0][15][2][1] = 'y';

	pieces[0][15][3][1] = 'y';

	pieces[0][17][0][0] = 'Y';

	pieces[0][17][1][0] = 'y';

	pieces[0][17][1][1] = 'y';

	pieces[0][17][2][0] = 'y';

	pieces[0][17][3][0] = 'y';

	pieces[0][19][0][0] = 'Y';

	pieces[0][19][0][1] = 'y';

	pieces[0][19][0][2] = 'y';

	pieces[0][19][1][1] = 'y';

	pieces[0][19][2][1] = 'y';

	pieces[0][20][0][1] = 'y';

	pieces[0][20][1][0] = 'y';

	pieces[0][20][1][1] = 'Y';

	pieces[0][20][1][2] = 'y';

	pieces[0][20][2][1] = 'y';

	//check

	/*for (int i = 0; i < 5; i++)

	{

	for (int j = 0; j < 5; j++)

	{

	cout<<pieces[0][0][i][j];

	}

	cout << endl;

	}*/

	// copy it

	for (int m = 0; m < 21; m++)

	{

		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				if (pieces[0][m][i][j] == 'Y')

				{

					pieces[2][m][i][j] = a[2];

					pieces[3][m][i][j] = a[3];

					pieces[1][m][i][j] = a[1];

				}

				if (pieces[0][m][i][j] == 'y')

				{

					pieces[2][m][i][j] = b[2];

					pieces[3][m][i][j] = b[3];

					pieces[1][m][i][j] = b[1];

				}
				if (pieces[0][m][i][j] == ' ')
				{
					pieces[2][m][i][j] = ' ';

					pieces[3][m][i][j] = ' ';

					pieces[1][m][i][j] = ' ';
				}

			}

		}

	}

}

int check_piece(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2], int boardX, int boardY, int playerNumber, int orientation, int piece)

{

	for (int p = 0; p < 4; p++)
	{
		if (piece != 21)

		{
			for (int x = 1; x < BOARDSIZE + 1; x++)

			{

				for (int y = 1; y < BOARDSIZE + 1; y++)

				{

					if (gameBoard[x][y] == a[p])

					{

						if (gameBoard[x + 1][y] == b[p])

						{

							return 0;

						}

						if (gameBoard[x - 1][y] == b[p])

						{

							return 0;

						}

						if (gameBoard[x][y + 1] == b[p])

						{

							return 0;

						}

						if (gameBoard[x][y - 1] == b[p])

						{

							return 0;

						}
					}
				}

			}

			for (int x = 1; x < BOARDSIZE + 1; x++)

			{

				for (int y = 1; y < BOARDSIZE + 1; y++)

				{
					if (gameBoard[x][y] == a[p])

					{

						if (gameBoard[x + 1][y + 1] == b[p])

						{

							return 1;

						}

						if (gameBoard[x + 1][y - 1] == b[p])

						{

							return 1;

						}

						if (gameBoard[x - 1][y + 1] == b[p])

						{

							return 1;

						}

						if (gameBoard[x - 1][y - 1] == b[p])

						{

							return 1;

						}



					}

				}

			}

		}


		else

		{

			if (gameBoard[boardX + 2][boardY] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX - 2][boardY] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX][boardY + 2] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX][boardY - 2] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX + 1][boardY + 1] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX + 1][boardY - 1] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX - 1][boardY + 1] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX - 1][boardY - 1] == b[playerNumber])

			{

				return 0;

			}

			if (gameBoard[boardX + 2][boardY + 1] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX + 2][boardY - 1] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX - 2][boardY + 1] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX - 2][boardY - 1] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX + 1][boardY - 2] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX - 1][boardY - 2] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX + 1][boardY + 2] == b[playerNumber])

			{

				return 1;

			}

			if (gameBoard[boardX - 1][boardY + 2] == b[playerNumber])

			{

				return 1;

			}
			else
			{
				return 0;
			}

		}

	}

	return 0;


}

int place_piece(int playerNumber, int piece, int orientation, int flip, int boardX, int boardY, char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2], char pieces[4][21][5][5])

{

	int row, column;

	char turned[5][5];

	char result[5][5];



	ori(orientation, playerNumber, piece, pieces, turned);

	flip_piece(flip, playerNumber, piece, turned, result);

	//find 

	int u = 0;

	for (row = 0; row < 5 && u == 0; row++)

	{

		for (column = 0; column < 5; column++)

		{

			if (result[row][column] == a[playerNumber])

			{

				u = 1;

				break;

			}

		}

	}

	row--;

	if (gameBoard[boardX][boardY] == ' ')

	{

		gameBoard[boardX][boardY] = a[playerNumber];

	}

	else

	{
		for (int x = 0; x < 5; x++)
		{
				for (int y = 0; y < 5; y++)
				{
					if (result[x][y] == b[playerNumber])
					{
						SetConsoleTextAttribute(hConsole, color[playerNumber]); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
					}
					if (result[x][y] == a[playerNumber])
					{
						SetConsoleTextAttribute(hConsole, 114); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
					}
					if (result[x][y] == ' ')
					{
						SetConsoleTextAttribute(hConsole, 7); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
					}
				}
			SetConsoleTextAttribute(hConsole, 7);
			cout << endl;
		}

		return 0;

	}

	for (int i = 0; i < 5; i++)

	{

		for (int j = 0; j < 5; j++)

		{

			if (result[i][j] == b[playerNumber])

			{

				if (gameBoard[boardX + i - row][boardY + j - column] == ' ')

				{

					gameBoard[boardX + i - row][boardY + j - column] = a[playerNumber];

				}

				else

				{
					for (int x = 0; x < 5; x++)
					{
						for (int y = 0; y < 5; y++)
						{
							if (result[x][y] == b[playerNumber])
							{
								SetConsoleTextAttribute(hConsole, color[playerNumber]); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
							}
							if (result[x][y] == a[playerNumber])
							{
								SetConsoleTextAttribute(hConsole, 114); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
							}
							if (result[x][y] == ' ')
							{
								SetConsoleTextAttribute(hConsole, 7); cout << "  "; SetConsoleTextAttribute(hConsole, 7);
							}
						}
						SetConsoleTextAttribute(hConsole, 7);
						cout << endl;
					}


					return 0;

				}

			}

		}

	}

	return 1;

}

void lower_board(int q, char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2])
{
	if (q == 1);
	for (int x = 0; x < BOARDSIZE + 2; x++)
	{
		for (int y = 0; y < BOARDSIZE + 2; y++)
		{
			gameBoard[x][y] = tolower(gameBoard[x][y]);
		}
	}

}

void print_board(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2])
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < BOARDSIZE + 2; i++)
	{
		for (int j = 0; j < BOARDSIZE + 2; j++)
		{
			//cout << gameBoard[i][j];
			if (gameBoard[i][j] == b[0]){ SetConsoleTextAttribute(hConsole, 224); cout << "  "; }
			if (gameBoard[i][j] == b[1]){ SetConsoleTextAttribute(hConsole, 176); cout << "  "; }
			if (gameBoard[i][j] == b[2]){ SetConsoleTextAttribute(hConsole, 160); cout << "  "; }
			if (gameBoard[i][j] == b[3]){ SetConsoleTextAttribute(hConsole, 192); cout << "  "; }
			if (gameBoard[i][j] == 'p'&&i == 0 && j<10){ SetConsoleTextAttribute(hConsole, 112); cout << j << " "; }
			if (gameBoard[i][j] == 'p'&&i == 0 && j >= 10){ SetConsoleTextAttribute(hConsole, 112); cout << j; }
			if (gameBoard[i][j] == 'p'&&j == 0 && i<10){ SetConsoleTextAttribute(hConsole, 112); cout << i << " "; }
			if (gameBoard[i][j] == 'p'&&j == 0 && i >= 10){ SetConsoleTextAttribute(hConsole, 112); cout << i; }
			if (gameBoard[i][j] == 'p'&&i != 0 && j != 0){ SetConsoleTextAttribute(hConsole, 112); cout << "  "; }
			if (gameBoard[i][j] == ' ' && (i + j) % 2 == 0){ SetConsoleTextAttribute(hConsole, 112); cout << "  "; }
			if (gameBoard[i][j] == ' ' && (i + j) % 2 == 1){ SetConsoleTextAttribute(hConsole, 128); cout << "  "; }
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}
	cout << endl;
}

void erase(char gameBoard[BOARDSIZE + 2][BOARDSIZE + 2])
{
	for (int x = 1; x < BOARDSIZE + 1; x++)
	{
		for (int y = 1; y < BOARDSIZE + 1; y++)
		{
			if (gameBoard[x][y] != tolower(gameBoard[x][y]))
			{
				gameBoard[x][y] = ' ';
			}
		}
	}
}

int game_over(int turnCounter)
{
	if (turnCounter == 84)
	{
		return 0;
	}
	else
		return 1;

}

void ori(int orientation, int playerNumber, int piece, char pieces[4][21][5][5], char result[5][5])

{

	char copy[5][5];

	for (int i = 0; i < 5; i++)

	{

		for (int j = 0; j < 5; j++)

		{

			copy[i][j] = pieces[playerNumber][piece][i][j];

		}

	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			result[i][j] = pieces[playerNumber][piece][i][j];
		}
	}

	for (int k = 0; k < orientation; k++)

	{

		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				result[i][j] = copy[4 - j][i];

			}

		}
		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				copy[i][j] = result[i][j];

			}

		}

	}

}

void flip_piece(int flip, int playerNumber, int piece, char turned[5][5], char result[5][5])

{
	for (int i = 0; i < 5; i++)

	{

		for (int j = 0; j < 5; j++)

		{
			result[i][j] = '\0';
		}
	}

	if (flip == 1)

	{

		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				result[i][j] = turned[i][4 - j];

			}

		}

	}
	else
	{
		for (int i = 0; i < 5; i++)

		{

			for (int j = 0; j < 5; j++)

			{

				result[i][j] = turned[i][j];

			}

		}
	}

}
