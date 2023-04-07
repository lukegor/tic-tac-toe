#include <iostream>
#include <conio.h>
#include <cstdlib>

using std::cout;
using std::cin;

void welcome();
void enter();
void board();
void choice();
void marker_usage(int decision);
void set_marker();
void gameover();
bool isDraw();

char tab[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char marker = 'X';

int main()
{
    welcome();
    enter();
    system("CLS");

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

void board()
{
    cout << "\n";
    cout << "  " << tab[0][0] << " | " << tab[0][1] << " | " << tab[0][2] << "\n";
    cout << " ___|___|___\n";
    cout << "  " << tab[1][0] << " | " << tab[1][1] << " | " << tab[1][2] << "\n";
    cout << " ___|___|___\n";
    cout << "  " << tab[2][0] << " | " << tab[2][1] << " | " << tab[2][2] << "\n";
}

void choice()
{
    cout << "\n\nChoose field [1-9] to fill: ";

    int decision;
    cin >> decision;

    marker_usage(decision);

    set_marker();
}

void marker_usage(int decision)
{
    int row = decision / 3 - 1;
    int col = (decision - 3*row) - 1;

    tab[row][col] = marker;
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
        if((tab[0][0] == marker && tab[0][1] == marker && tab[0][2] == marker) ||
           (tab[1][0] == marker && tab[1][1] == marker && tab[1][2] == marker) ||
           (tab[2][0] == marker && tab[2][1] == marker && tab[2][2] == marker) ||
           (tab[0][0] == marker && tab[1][0] == marker && tab[2][0] == marker) ||
           (tab[0][1] == marker && tab[1][1] == marker && tab[2][1] == marker) ||
           (tab[0][2] == marker && tab[1][2] == marker && tab[2][2] == marker) ||
           (tab[0][0] == marker && tab[1][1] == marker && tab[2][2] == marker) ||
           (tab[2][0] == marker && tab[1][1] == marker && tab[0][2] == marker))
        {
            cout << "Player " << marker << " has won! Congratulaions!";
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
        for (int j = 0; j < 3; ++i)
        {
            if (tab[i][j] == 'X' || tab[i][j] == 'O') {}
            else
            {
                checker = false;
                return checker;
            }
        }
    }

    return checker;
}
