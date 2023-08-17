// global_variables.h

#pragma once

#include <string>

using std::string;

// global variables
extern const int DIMENSION_SIZE;
extern char gameBoard[][3];
extern char marker;
extern const char marker1;
extern const char marker2;
extern int row;
extern int col;
extern int turn_counter;
extern int gameMode;
extern bool unsuccessfulChoice;
extern string player1;
extern string player2;
extern std::mt19937 engine;