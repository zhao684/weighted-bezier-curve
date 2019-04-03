#pragma once
#include "glui.h"
#include <map>
#include <array>

extern GLUI *glui;
//extern GLUI *glui_left;
extern GLUI *glui_bottom;
extern GLUI_Checkbox *checkbox;
//extern GLUI_Spinner *spinner;
extern GLUI_RadioGroup *radio;
extern GLUI_Panel *panel;
extern GLUI_EditText *edittext;
extern GLUI_StaticText *addtext;

void buildGLUI(int displayWin);

int getMouseMode();
int getDrawingCurve();
std::string getDisplayMode();
std::string getDisplayMode2();
float getT();
float getT2();
void setT(float n);
void setT2(float n);
int getrDe();
void resetrDe();
float getColorr();
float getColorg();
float getColorb();