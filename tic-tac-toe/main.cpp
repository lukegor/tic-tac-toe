#include <iostream>
#include <conio.h>
#include <cstdlib>

// using directives
using std::cout;
using std::cin;
using std::cerr;

// enums

enum MarkerError
{
    NO_ERROR,
    FIELD_ALREADY_MARKED,
    INVALID_DECISION
};

// function declarations
void welcome();
void enter();
void clear_screen();
void print_board();
void choice();                      // calls marker_usage() and set_marker()
MarkerError marker_usage(int decision);    // uses enum
void set_marker();
void gameover();                    // calls isDraw(), choice(), print_board(), player()
bool isDraw();
char player();
void player_announcement();         // calls player()

// global variables
const int BOARD_SIZE = 3;
char gameBoard[BOARD_SIZE][BOARD_SIZE] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char marker = 'X';
int row;
int col;




int main()
{
    welcome();
    enter();
    clear_screen();

    print_board();

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
    const int enter_button = 13;
    while (key != enter_button)
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

void print_board()
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
    player_announcement();
    cout << "Choose field [1-9] to fill: ";

    int decision;
    cin >> decision;

    marker_usage(decision);

    set_marker();
}

void marker_usage(int decision)
{
    if(gameBoard[row][col] == 'X' or gameBoard[row][col] == 'O')
    {
        cerr << "\n\n******************";
        cerr << "Disallowed action. ";
        cerr << "******************\n\n";

        //return FIELD_ALREADY_MARKED;
    }
    else if (decision < 1 || decision > 9)
    {
        cerr << "\n\n******************";
        cerr << "Disallowed action.";
        cerr << "******************\n\n";
        //return INVALID_DECISION;
    }
    else
    {
        row = decision / 3 - 1;
        col = (decision - 3*row) - 1;

        gameBoard[row][col] = marker;

        //return NO_ERROR;
    }
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
            cout << "Player" << player() << " has won! Congratulations!";
            over = true;
        }
        else if (isDraw())
        {
            cout << "The match ends in a draw!\n";
            over = true;
        }
        else
        {
            choice();
            print_board();
        }
    }
}

bool isDraw()
{
    bool isFilled = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (gameBoard[i][j] == 'X' || gameBoard[i][j] == 'O') {}
            else
            {
                isFilled = false;
                return isFilled;
            }
        }
    }

    return isFilled;
}

char player()
{
    if (marker == 'X')
        return '1';
    else if (marker == 'O')
        return '2';
}

void player_announcement()
{
    cout << "\nPlayer" << player() << "'s turn!\n";
}
