#include "glui.h"
#include "GL/freeglut.h"
#include "buildGLUI.h"
#include "Zhao_Tianyu_Assignment_5.h"
#include <map>
#include <array>
#include <string>
#include <iostream>

// items for header file
GLUI *glui;
//GLUI *glui_left;
GLUI *glui_bottom;
GLUI_Checkbox *checkbox;
GLUI_Spinner *spinner;
GLUI_RadioGroup *radio;
GLUI_Panel *panel;
GLUI_EditText *edittext;
float t=0.5;
float t1 = 0.5;
float t2 = 0.5;
int mouseMode = 0; // 1 define ; 2 move ; 3 delete
int drawCurve = 1;
int ctrlPloy = 0;
int conHull = 0;
int decLine = 0;
int curve = 0;
int extCurve = 0;
int rDegree = 0;
float colorr, colorg, colorb;



std::string displayMode = "00000";
std::string displayModea = "00000";


void showMe(int r) {

}

int mouseStatus = -1;       // live variable of radio group
void doSomething(int r) {   // radio group call back
  //printf("radio group %d\n   ", mouseStatus);
  switch (mouseStatus) {
  case 0:
	  mouseMode = 1;
    break;
  case 1:
	  mouseMode = 2;
    break;
  case 2:
	  mouseMode = 3;
    break;
  }
}

int mouseStatus2 = -1;       // live variable of radio group
void doSomethingElse(int r) {   // radio group call back
  //printf("radio group %d\n   ", mouseStatus);
	switch (mouseStatus) {
	case 0:
		drawCurve = 1;
		break;
	case 1:
		drawCurve = 2;
		break;
	}
}

void raise(int) {
	rDegree = 1;
	std::cout << "degree: " << rDegree << std::endl;
}
void undo(int) {
	rDegree = 2;
}

void clearAll(int) {
	cleanup();
}
void gotoExit(int) { exit(0);}

void param_ctrl(int select) {
	if (select == 1) {
		if (drawCurve == 1) {
			t1 = t;
		}
		else {
			t2 = t;
		}
	}
}
void buildGLUI(int displayWin) {
  //GLUI_Master.set_glutReshapeFunc(resizeWin);
  //GLUI_Master.set_glutMouseFunc(myMouse);
  //GLUI_Master.set_glutIdleFunc(myIdle);
  glui = GLUI_Master.create_glui_subwindow(displayWin, GLUI_SUBWINDOW_RIGHT);

  GLUI_Panel *panel1 = new GLUI_Panel(glui, "Please Input", GLUI_PANEL_EMBOSSED);
  GLUI_Spinner *sp = new GLUI_Spinner(panel1, "t: ", GLUI_SPINNER_FLOAT, &t, 1, param_ctrl);
	sp->set_float_limits(0, 1, GLUI_LIMIT_CLAMP);



  GLUI_Panel *panel2 = new GLUI_Panel(glui, "Show", GLUI_PANEL_EMBOSSED);
  new GLUI_Checkbox(panel2, "Control Polygon", &ctrlPloy, 12, showMe);
  new GLUI_Checkbox(panel2, "Convex Hull", &conHull, 12, showMe);
  new GLUI_Checkbox(panel2, "DeCasteljau Lines", &decLine, 12, showMe);
  new GLUI_Checkbox(panel2, "Curve", &curve, 12, showMe);
  new GLUI_Checkbox(panel2, "Extended Curve", &extCurve, 12, showMe);



  GLUI_Panel *panel3 = new GLUI_Panel(glui, "Mouse Mode", GLUI_PANEL_EMBOSSED);
  GLUI_RadioGroup *actionGroup = new GLUI_RadioGroup(panel3, &mouseStatus, -1, doSomething);
  new GLUI_RadioButton(actionGroup, "Define Control Point");
  new GLUI_RadioButton(actionGroup, "Move Control Point");
  new GLUI_RadioButton(actionGroup, "Delete Control Point");
  
  new GLUI_Button(panel3, "Raise Degree", 60, raise);
  new GLUI_Button(panel3, "Undo Raising", 60, undo);
 /* new GLUI_RadioButton(actionGroup, "Shade On");
  new GLUI_RadioButton(actionGroup, "Shade Off");
  */

  GLUI_Panel *panel5 = new GLUI_Panel(glui, "Color", GLUI_PANEL_EMBOSSED);
  new GLUI_EditText(panel5, "R (float)", /*GLUI_EDITTEXT_FLOAT,*/ &colorr, 13, param_ctrl);
  new GLUI_EditText(panel5, "G (float)", /*GLUI_EDITTEXT_FLOAT,*/ &colorg, 13, param_ctrl);
  new GLUI_EditText(panel5, "B (float)", /*GLUI_EDITTEXT_FLOAT,*/ &colorb, 13, param_ctrl);

  GLUI_Panel *panel6 = new GLUI_Panel(glui, "Mouse Mode", GLUI_PANEL_EMBOSSED);
  GLUI_RadioGroup *actionGroup2 = new GLUI_RadioGroup(panel6, &mouseStatus, -1, doSomethingElse);
  new GLUI_RadioButton(actionGroup2, "First Line");
  new GLUI_RadioButton(actionGroup2, "Second Line");


  GLUI_Panel *panel4 = new GLUI_Panel(glui, "  ", GLUI_PANEL_NONE);
  new GLUI_Button(panel4, "Reset", 60, clearAll);
  new GLUI_Button(panel4, "EXIT", 70, gotoExit);


  
  
}

int getMouseMode() {
	return mouseMode;
}
int getDrawingCurve() {
	return drawCurve;
}
std::string getDisplayMode() {
	if (ctrlPloy) { displayMode[0] = '1'; }
	else { displayMode[0] = '0'; }
	if (conHull) { displayMode[1] = '1'; }
	else { displayMode[1] = '0'; }
	if (decLine) { displayMode[2] = '1'; }
	else { displayMode[2] = '0'; }
	if (curve) { displayMode[3] = '1'; }
	else { displayMode[3] = '0'; }
	if (extCurve) { displayMode[4] = '1'; }
	else { displayMode[4] = '0'; }
	//std::cout << displayMode << std::endl;
	return displayMode;
}
std::string getDisplayMode2() {
	if (ctrlPloy) { displayModea[0] = '1'; }
	else { displayModea[0] = '0'; }
	if (conHull) { displayModea[1] = '1'; }
	else { displayModea[1] = '0'; }
	if (decLine) { displayModea[2] = '1'; }
	else { displayModea[2] = '0'; }
	if (curve) { displayModea[3] = '1'; }
	else { displayModea[3] = '0'; }
	if (extCurve) { displayModea[4] = '1'; }
	else { displayModea[4] = '0'; }
	//std::cout << displayMode << std::endl;
	return displayModea;
}
float getT() {
	return t1;
}
float getT2() {
	return t2;
}
int getrDe() {
	return rDegree;
}
void resetrDe() {
	rDegree = 0;
}
void setT(float n) {
	t1 = n;
}
void setT2(float n) {
	t2 = n;
}
float getColorr() {
	return colorr;
}
float getColorg() {
		return colorg;
}
float getColorb() {
	return colorb;
}