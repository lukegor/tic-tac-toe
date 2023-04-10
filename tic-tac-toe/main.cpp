#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <random>

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
void choice();                      // calls marker_usage(), set_marker(), detect_error()
void marker_usage(int decision);    // supposed to use enum
void set_marker();
MarkerError detect_error(int decision);
void error_msg(MarkerError isError);
void determine_field(int decision);
void play_game();                    // calls isDraw(), choice(), print_board(), player()
void isOver(bool &over);
void keep_playing(bool over);
bool isDraw();
char whose_turn();
void player_announcement();         // calls whose_turn()
char who_won();

/*
void play_again();
void clear_values();
*/

// global variables
const int DIMENSION_SIZE = 3;
char gameBoard[DIMENSION_SIZE][DIMENSION_SIZE] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char marker = 'X';
const char marker1 = 'X';
const char marker2 = 'O';
int row;
int col;
int turn_counter = 0;




int main()
{
    int checkpoint;
    welcome();
    enter();
    clear_screen();

    print_board();

    play_game();
    //play_again();

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

    MarkerError isError = detect_error(decision);

    if (isError == NO_ERROR)
    {
        marker_usage(decision);
        set_marker();
    }
    else
        error_msg(isError);

}

void marker_usage(int decision)
{
    determine_field(decision);

    gameBoard[row][col] = marker;
}

void determine_field(int decision)
{
    row = decision / 3 - 1;
    col = (decision - 3*row) - 1;
}

void set_marker()
{
    if (marker == marker1)
        marker = marker2;
    else if (marker == marker2)
        marker = marker1;
}

MarkerError detect_error(int decision)
{
    MarkerError isError = NO_ERROR;
    determine_field(decision);

    if(gameBoard[row][col] == marker1 || gameBoard[row][col] == marker2)
    {
        isError = FIELD_ALREADY_MARKED;
        return isError;
    }
    else if (decision < 1 || decision > 9)
    {
        isError = INVALID_DECISION;
        return isError;
    }
    else
        return isError;
}

void error_msg(MarkerError isError)
{
    if (isError == FIELD_ALREADY_MARKED)
    {
        cerr << "\n\n******************";
        cerr << "Disallowed action. The Field is already marked.";
        cerr << "******************\n\n";
    }
    else if (isError == INVALID_DECISION)
    {
        cerr << "\n\n******************";
        cerr << "Disallowed action. Invalid decision.";
        cerr << "******************\n\n";
    }
}

void play_game()
{
    bool over = false;

    while (over == false)
    {
        ++turn_counter;
        keep_playing(over);

        isOver(over);
    }
}

void isOver(bool &over)
{
    if((gameBoard[0][0] == marker1 && gameBoard[0][1] == marker1 && gameBoard[0][2] == marker1) ||
       (gameBoard[1][0] == marker1 && gameBoard[1][1] == marker1 && gameBoard[1][2] == marker1) ||
       (gameBoard[2][0] == marker1 && gameBoard[2][1] == marker1 && gameBoard[2][2] == marker1) ||
       (gameBoard[0][0] == marker1 && gameBoard[1][0] == marker1 && gameBoard[2][0] == marker1) ||
       (gameBoard[0][1] == marker1 && gameBoard[1][1] == marker1 && gameBoard[2][1] == marker1) ||
       (gameBoard[0][2] == marker1 && gameBoard[1][2] == marker1 && gameBoard[2][2] == marker1) ||
       (gameBoard[0][0] == marker1 && gameBoard[1][1] == marker1 && gameBoard[2][2] == marker1) ||
       (gameBoard[2][0] == marker1 && gameBoard[1][1] == marker1 && gameBoard[0][2] == marker1) ||
       (gameBoard[0][0] == marker2 && gameBoard[0][1] == marker2 && gameBoard[0][2] == marker2) ||
       (gameBoard[1][0] == marker2 && gameBoard[1][1] == marker2 && gameBoard[1][2] == marker2) ||
       (gameBoard[2][0] == marker2 && gameBoard[2][1] == marker2 && gameBoard[2][2] == marker2) ||
       (gameBoard[0][0] == marker2 && gameBoard[1][0] == marker2 && gameBoard[2][0] == marker2) ||
       (gameBoard[0][1] == marker2 && gameBoard[1][1] == marker2 && gameBoard[2][1] == marker2) ||
       (gameBoard[0][2] == marker2 && gameBoard[1][2] == marker2 && gameBoard[2][2] == marker2) ||
       (gameBoard[0][0] == marker2 && gameBoard[1][1] == marker2 && gameBoard[2][2] == marker2) ||
       (gameBoard[2][0] == marker2 && gameBoard[1][1] == marker2 && gameBoard[0][2] == marker2))
        {
        cout << "Game Over! Player" << who_won() << " has won! Congratulations!";
        over = true;
    }
    else if (isDraw())
    {
        cout << "The match ends in a draw!\n";
        over = true;
    }
}

void keep_playing(bool over)
{
    if(over == false)
    {
        choice();
        print_board();
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

char whose_turn()
{
    if (marker == marker1)
        return '1';
    else if (marker == marker2)
        return '2';
}

void player_announcement()
{
    cout << "\nPlayer" << whose_turn() << "'s turn!\n";
}


char who_won()
{
    if (turn_counter % 2 == 1)
        return '1';
    else if (turn_counter % 2 == 0)
        return '0';
}

/*
void play_again()
{
    cout << "\n\n\nWould you like to play again? [y/n]: ";
    char again;
    cin >> again;

    if (again == 'y')
    {
        clear_values();
        clear_screen();
    }
    else if (again == 'n')
    {
        exit(true);
    }
}

void clear_values()
{
    char gameBoard[DIMENSION_SIZE][DIMENSION_SIZE] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    char marker = 'X';
    int row = -1;
    int col = -1;
}
*/
