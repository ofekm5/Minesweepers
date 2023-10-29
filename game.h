#ifndef GAME_h
#define GAME_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define maxboardsize 22

int const Boardsize[]={0, 8, 12, 15};//All size of choice by the user

//Func declerations
void Mainmenu(int measurements[]);
void boardSetting(char board[][maxboardsize], int measurements[]);
void bombseeder(char board[][maxboardsize], int measurements[], int numofbombs);
void boardprinting(int measurements[], char board[][maxboardsize], bool coverbombs);
void playingTime(char board[][maxboardsize], int measurements[], int numofbombs);
void calculatebombsnear(char board[][maxboardsize], int measurements[], int row, int column, bool revealflags);
void revealemptycells(char board[][maxboardsize], int measurements[], int row, int column , int *cellslefttoopen);
void printcolumn(int measurements[]);
void printrow(int measurements[], char board[][maxboardsize], bool coverbombs);
bool cheatmode(char board[][maxboardsize], int measurements[], int numofbombs, int *cellslefttoopen);
bool playersturn(char board[][maxboardsize], int measurements[], int row, int column, int *cellslefttoopen);



#endif
