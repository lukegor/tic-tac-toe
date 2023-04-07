#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;

void welcome();
void enter();

char tab[3][3];

int main()
{
    welcome();
    enter();

    return 0;
}

void welcome()
{
    cout << "Welcome to our Tic-Tac-Toe game\n\n";

    cout << "In order to play press ENTER...";
}

void enter()
{
    char key = getch();
    while (key != 13)
    {
        key = getch();
    }
}
