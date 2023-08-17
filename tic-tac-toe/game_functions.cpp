#pragma once

// game_functions.cpp
#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <cctype>
#include <random>
#include <chrono>
#include "game_functions.h"
#include "global_variables.h"

using namespace std;

void welcome()
{
    cout << "Welcome to our Tic-Tac-Toe game\n\n";
    cout << "In order to start press ENTER...";
}

void enter()
{
    char key = _getch();
    const int enter_button = 13;
    while (key != enter_button)
    {
        key = _getch();
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

void chooseNickname()
{
    cout << "\n";
    cout << "Choose your nickname or press ENTER to go with default [Player1]: ";

    string name;

    getline(cin, name);

    if (name.empty() == false)
        player1 = name;

    if (gameMode == 1)
    {
        cout << "Choose your nickname or press ENTER to go with default [Player2]: ";
        getline(cin, name);
        if (name.empty() == false)
            player2 = name;
    }
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

    makeChoice(decision);

    MarkerError isError;

    if (gameMode == 1)
    {
        isError = detect_error(decision);


        if (isError == NO_ERROR)
        {
            marker_usage(decision);
            set_marker();
        }
        else
        {
            unsuccessfulChoice = true;
            error_msg(isError);
        }
    }
    else if ((gameMode == 2 || gameMode == 3) && turn_counter % 2 == 1)  // player move in AIMode
    {
        cout << "\n\n\n" << turn_counter << "\n\n\n";
        isError = detect_error(decision);


        if (isError == NO_ERROR)
        {
            marker_usage(decision);
            set_marker();
        }
        else
        {
            unsuccessfulChoice = true;
            error_msg(isError);
        }
    }
    else if ((gameMode == 2 || gameMode == 3) && turn_counter % 2 == 0)  // executeAIMove in AIMode
    {
        marker_usage(decision);
        set_marker();
    }
}

void makeChoice(int& decision)
{
    if (gameMode == 1 || ((gameMode == 2 || gameMode == 3) && turn_counter % 2 == 1))
    {
        cin >> decision;
    }
    else if ((gameMode == 2 || gameMode == 3) && turn_counter % 2 == 0)
    {

        executeAIMove();

        decision = (row * DIMENSION_SIZE + col + 1);
        cout << decision;
    }
}

void marker_usage(int decision)
{
    determine_field(decision);

    gameBoard[row][col] = marker;
}

void determine_field(int decision)
{
    row = decision / 3 - 1;
    col = (decision - 3 * row) - 1;
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


    if (decision < 1 || decision > 9)
    {
        isError = INVALID_DECISION;
        return isError;
    }
    else if (gameBoard[row][col] == marker1 || gameBoard[row][col] == marker2)
    {
        isError = FIELD_ALREADY_MARKED;
        return isError;
    }
    else
        return isError;
}

MarkerError detect_error2()
{
    MarkerError isError = NO_ERROR;
    int decision = (row * DIMENSION_SIZE + col + 1);

    if (decision < 1 || decision > 9)
    {
        isError = INVALID_DECISION;
        return isError;
    }
    else if (gameBoard[row][col] == marker1 || gameBoard[row][col] == marker2)
    {
        isError = FIELD_ALREADY_MARKED;
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
        cerr << "Prohibited action. The Field is already marked.";
        cerr << "******************\n\n";
    }
    else if (isError == INVALID_DECISION)
    {
        cerr << "\n\n******************";
        cerr << "Prohibited action. Invalid decision.";
        cerr << "******************\n\n";
    }
}

void play_game()
{
    bool over = false;

    while (over == false)
    {
        if (unsuccessfulChoice == false)
        {
            ++turn_counter;
        }
        else
        {
            unsuccessfulChoice = false;
        }

        keep_playing(over);

        isOver(over);
    }
}


void isOver(bool& over)
{
    if ((gameBoard[0][0] == marker1 && gameBoard[0][1] == marker1 && gameBoard[0][2] == marker1) ||
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
        cout << "Game Over! Player " << who_won() << " has won! Congratulations!";
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
    if (over == false)
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

string whose_turn()
{
    if (marker == marker1)
        return player1;
    else if (marker == marker2)
        return player2;
}

void player_announcement()
{
    cout << "\nPlayer " << whose_turn() << "'s turn!\n";
}


string who_won()
{
    if (turn_counter % 2 == 1)
        return player1;
    else if (turn_counter % 2 == 0)
        return player2;
}


bool play_again()
{
    cout << "\n\n\nWould you like to play again? [y/n]: ";
    char again;
    cin >> again;

    if (again == 'y')
    {
        clear_values();
        clear_screen();
        return true;
    }
    return false;
}

void clear_values()
{
    for (int i = 0; i < DIMENSION_SIZE; ++i)
    {
        for (int j = 0; j < DIMENSION_SIZE; ++j)
        {
            gameBoard[i][j] = '0' + (i * DIMENSION_SIZE + j + 1);
        }
    }
    print_board();
    marker = 'X';
    row = -1;
    col = -1;
    turn_counter = 0;
    gameMode = 1;
    unsuccessfulChoice = false;
    player1 = "Player1";
    player2 = "Player2";
}

int getRandomInt()          // using Mersenne Twister engine from <random>
{
    std::uniform_int_distribution<> dist(0, 2);

    int random_num = dist(engine);
    return random_num;
}

void chooseGameMode()
{
    cout << "Choose game mode";
    cout << "\n\n\n";
    cout << "\t1. Human vs Human\n";
    cout << "\t2. Human vs AI (easy)\n";
    cout << "\t3. UNAVAILABLE - TO BE INTRODUCED   Human vs AI (medium)";
    cout << "\n\n\n";
    cout << "\tYour choice is [1/2]: ";

    int mode;
    cin >> mode;
    cin.ignore();

    while (mode != 1 && mode != 2)
    {
        cerr << "\n\n";
        cerr << "Invalid mode chosen. Please choose again [1/2]: ";
        cin >> mode;
        cin.ignore();       // fixes error that causes 2 error communicates to be displayed
    }


    gameMode = mode;
}

bool isValidAIMove()
{
    MarkerError result = detect_error2();
    if (result == FIELD_ALREADY_MARKED || result == INVALID_DECISION)
    {
        return false;
    }
    else if (result == NO_ERROR)
    {
        return true;
    }
}

bool chooseAndAssessAIMove()
{
    if (gameMode == 2)
    {
        row = getRandomInt();
        col = getRandomInt();
    }
    /*
    else if (gameMode == 3)
    {
        //mode3AIMove();
    }
    */
    bool test = isValidAIMove();
    return test;
}

void executeAIMove()
{

    if (marker == marker2)
    {
        bool test = chooseAndAssessAIMove();

        if (test == false) { executeAIMove(); }
        else
        {
            gameBoard[row][col] = marker2;
        }
    }
    else {}
}