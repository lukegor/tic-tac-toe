// game_functions.h
#pragma once	// Include guards to prevent double inclusion

#include <string>
#include "global_variables.h"

using namespace std;

// enums
enum MarkerError
{
    NO_ERROR,
    FIELD_ALREADY_MARKED,
    INVALID_DECISION
};

// function declarations

                                    // calls list is incomplete as of 15.04.2023
void welcome();
void enter();
void clear_screen();
void chooseNickname();
void print_board();
void choice();                      // calls player_announcement(), makeChoice(), detect_error(), set_marker(),  marker_usage(), error_msg()
void makeChoice(int& decision);
void marker_usage(int decision);    // uses enum
void set_marker();
MarkerError detect_error(int decision);
MarkerError detect_error2();
void error_msg(MarkerError isError);
void determine_field(int decision);
void play_game();                    // calls isDraw(), choice(), print_board(), player()
void isOver(bool& over);
void keep_playing(bool over);
bool isDraw();
string whose_turn();
void player_announcement();         // calls whose_turn()
string who_won();
bool play_again();
void clear_values();
int getRandomInt();
void chooseGameMode();
void executeAIMove();                      // not only does it make an AI move, but also call isValidAIMove() within itself unlike what is done for Human Mode
bool isValidAIMove();
void mode3AIMove();