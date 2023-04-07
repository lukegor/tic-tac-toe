#include <iostream>
#include <conio.h>
#include <cstdlib>

using std::cout;
using std::cin;

void welcome();
void enter();
void clear_screen();
void board();
void choice();
void marker_usage(int decision);
void set_marker();
void gameover();
bool isDraw();
void player();

char gameBoard[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char marker = 'X';




int main()
{
    welcome();
    enter();
    clear_screen();

    board();

    gameover();

    return 0;
}




void welcome()
{
    cout << "Welcome to our Tic-Tac-Toe game\n\n";
    cout << "In order to start press ENTER...";
}

void enter()
{
    char key = getch();
    while (key != 13)
    {
        key = getch();
    }
}

void clear_screen()
{
    #if defined(_WIN32) || defined(_WIN64)
    system("cls");
    #else
    system("clear");
    #endif
}

void board()
{
    cout << "\n";
    cout << "  " << gameBoard[0][0] << " | " << gameBoard[0][1] << " | " << gameBoard[0][2] << "\n";
    cout << " ___|___|___\n";
    cout << "  " << gameBoard[1][0] << " | " << gameBoard[1][1] << " | " << gameBoard[1][2] << "\n";
    cout << " ___|___|___\n";
    cout << "  " << gameBoard[2][0] << " | " << gameBoard[2][1] << " | " << gameBoard[2][2] << "\n\n";
}

void choice()
{
    player();
    cout << "Choose field [1-9] to fill: ";

    int decision;
    cin >> decision;

    marker_usage(decision);

    set_marker();
}

void marker_usage(int decision)
{
    int row = decision / 3 - 1;
    int col = (decision - 3*row) - 1;

    gameBoard[row][col] = marker;
}

void set_marker()
{
    if (marker == 'X')
        marker = 'O';
    else if (marker == 'O')
        marker = 'X';
}

void gameover()
{
    bool over = false;

    while (over == false)
    {
        if((gameBoard[0][0] == marker && gameBoard[0][1] == marker && gameBoard[0][2] == marker) ||
           (gameBoard[1][0] == marker && gameBoard[1][1] == marker && gameBoard[1][2] == marker) ||
           (gameBoard[2][0] == marker && gameBoard[2][1] == marker && gameBoard[2][2] == marker) ||
           (gameBoard[0][0] == marker && gameBoard[1][0] == marker && gameBoard[2][0] == marker) ||
           (gameBoard[0][1] == marker && gameBoard[1][1] == marker && gameBoard[2][1] == marker) ||
           (gameBoard[0][2] == marker && gameBoard[1][2] == marker && gameBoard[2][2] == marker) ||
           (gameBoard[0][0] == marker && gameBoard[1][1] == marker && gameBoard[2][2] == marker) ||
           (gameBoard[2][0] == marker && gameBoard[1][1] == marker && gameBoard[0][2] == marker))
        {
            cout << "Player " << marker << " has won! Congratulations!";
            over = true;
        }
        else if (isDraw())
        {
            cout << "The match ends in a draw!";
            over = true;
        }
        else
        {
            choice();
            board();
        }
    }
}

bool isDraw()
{
    bool checker = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (gameBoard[i][j] == 'X' || gameBoard[i][j] == 'O') {}
            else
            {
                checker = false;
                return checker;
            }
        }
    }

    return checker;
}

void player()
{
    if (marker == 'X')
        cout << "\nPlayer1's turn\n";
    else if (marker == 'O')
        cout << "\nPlayer2's turn\n";
}
