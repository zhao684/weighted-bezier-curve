#pragma once
#include "glui.h"
#include <map>
#include <string>
#include <array>

// global variables
extern int displayWin, winSizeX, winSizeY;

//CMY, empty board = B, empty storage = S, empty others = E


// stubs of call back functions
void showWin();
void resizeWin(int w, int h);
void myMouse(int, int, int, int);
void myIdle();
void cleanup();