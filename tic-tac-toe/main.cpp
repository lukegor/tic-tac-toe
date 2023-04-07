#include <iostream>
#include <conio.h>
#include <cstdlib>

using std::cout;
using std::cin;

void welcome();
void enter();
void board();

char tab[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

int main()
{
    welcome();
    enter();
    system("CLS");

    board();

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
