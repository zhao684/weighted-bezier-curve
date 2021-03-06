// Zhao_Tianyu_Assignment_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "glui.h"
#include "GL/freeglut.h"
#include "buildGLUI.h"
#include "Zhao_Tianyu_Assignment_5.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>

// globalss for header file
int displayWin, displayWeight, displayUI, winSizeX, winSizeY;
int mode;
int pointNum = 0;
int moving = -2;
int coeff[32][32];
int currWeightIndex = -2;
int haveFirst;
float firstMousex = -1;
float firstMousey = -1;
int drawing = 1;
float cr = 0; float cg = 1; float cb = 0;
float prp = 0.8; float pgp = 0.8; float pbp = 0;
float prn = 0.6; float pgn = 0; float pbn = 0;
float dr = 0; float dg = 1; float db = 1;
float por = 0; float pog = 0.8; float pob = 0;
float hullr = 0.3; float hullg = 0.3; float hullb = 0.3;
float backr = 0, backg = 0, backb = 0;
float curvePointr = 1, curvePointg = 0, curvePointb = 0;
float cr2 = 0; float cg2 = 1; float cb2 = 0;
float prp2 = 0.8; float pgp2 = 0.8; float pbp2 = 0;
float prn2 = 0.6; float pgn2 = 0; float pbn2 = 0;
float dr2 = 0; float dg2 = 1; float db2 = 1;
float por2 = 0; float pog2 = 0.8; float pob2 = 0;
float hullr2 = 0.3; float hullg2 = 0.3; float hullb2 = 0.3;
float curvePointr2 = 1, curvePointg2 = 0, curvePointb2 = 0;
std::string displayMode1 = "00000";
std::string displayMode2 = "00000";
std::string dis;
std::string changeColor;
std::pair<float, float> firstP1;
std::pair<float, float> firstP2;
std::pair<float, float> lastP;
std::vector<std::pair<float, float>> pVec1;
std::vector<std::pair<float, float>> pVec2;
std::vector<std::pair<float, float>> pAtMiddle;
std::vector<float> weight;
std::vector<float> wVec1;
std::vector<float> wVec2;
std::vector<std::pair<float, float>> reset;


void cleanup() {//TODO
	pAtMiddle.clear();
	reset.clear();
	weight.clear();
	pVec1.clear();
	pVec2.clear();
	wVec1.clear();
	wVec2.clear();
	displayMode1 = "00000";
	displayMode2 = "00000";
	firstMousex = -1;
	firstMousey = -1;
	drawing = 1;
	pointNum = 0;
	moving = -2;
	cr = 0; cg = 1; cb = 0;
	prp = 0.8; pgp = 0.8; pbp = 0;
	prn = 0.6; pgn = 0; pbn = 0;
	dr = 0; dg = 1; db = 1;
	por = 0; pog = 0.8; pob = 0;
	hullr = 0.3;hullg = 0.3; hullb = 0.3;
	backr = 0; backg = 0; backb = 0;
	curvePointr = 1; curvePointg = 0; curvePointb = 0;
	cr2 = 0; cg2 = 1; cb2 = 0;
	prp2 = 0.8; pgp2 = 0.8; pbp2 = 0;
	prn2 = 0.6; pgn2 = 0; pbn2 = 0;
	dr2 = 0; dg2 = 1; db2 = 1;
	por2 = 0; pog2 = 0.8; pob2 = 0;
	hullr2 = 0.3; hullg2 = 0.3; hullb2 = 0.3;
	curvePointr2 = 1; curvePointg2 = 0; curvePointb2 = 0;
}
std::pair<float, float> drawDeLine(float t, int mode, int drawing) {
	if (drawing == 1&&mode!=3 || getDrawingCurve()==1&&mode == 3) {
		pAtMiddle = pVec1;
		weight = wVec1;
	}
	else if(drawing == 2 && mode != 3 || getDrawingCurve() == 2 && mode == 3){
		pAtMiddle = pVec2;
		weight = wVec2;
	}
	std::vector<std::pair<float, float>> midPoints = pAtMiddle;
	std::vector<std::pair<float, float>> temp;
	std::vector<float> updatew = weight;
	std::vector<float> tempw;
	std::pair<float, float> prevP;
	int FDflag = 0;
	while (midPoints.size() > 1) {
		float wik;
		for (int i = 0; i < midPoints.size() - 1; i++) {
			wik = (1 - t) * updatew.at(i) + t * updatew.at(i + 1);

			std::pair<float, float> thisP = midPoints.at(i);
			std::pair<float, float> nextP = midPoints.at(i + 1);
			float newx = thisP.first*(1 - t)*updatew.at(i) / wik + nextP.first * t * updatew.at(i+1) / wik;
			float newy = thisP.second*(1 - t)*updatew.at(i) / wik + nextP.second* t * updatew.at(i+1) / wik;
			temp.push_back(std::make_pair(newx, newy));
			if (i == 0 && FDflag == 0) {
				FDflag = 1;
				if (drawing == 1) {
					firstP1 = std::make_pair(newx, newy);
				}
				else {
					firstP2 = std::make_pair(newx, newy);
				}
			}
			tempw.push_back(wik);
			if (i != 0 && mode == 1) {
				glBegin(GL_LINES);
				glVertex2f(prevP.first, prevP.second);
				glVertex2f(newx,newy);
				glEnd();
			}
			prevP = std::make_pair(newx, newy);
		}
		midPoints = temp;
		updatew = tempw;
		temp.clear();
		tempw.clear();
	}
	prevP = midPoints.front();
	return prevP;
}
void drawCurve(int drawing) {
	if (drawing == 1) {
		weight = wVec1;
		pAtMiddle = pVec1;
		pointNum = pAtMiddle.size();
		float x = 0; float y = 0; float dvb = 0;
		if (displayMode1[3] == '1') {

			glBegin(GL_LINES);
			for (float t = 0; t < 1; t = t + 0.02) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 0) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			glEnd();
			//glColor3f(1, 1, 1);
		}
		if (displayMode1[4] == '1') {
			//glColor3f(0, 1, 0);
			glBegin(GL_LINES);
			for (float t = 0; t > -5; t = t - 0.02) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 0) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			glVertex2d(x / dvb, y / dvb);
			for (float t = 1; t < 6; t = t + 0.02) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 1) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			//glColor3f(1, 1, 1);
			glEnd();
		}
	}
	else {
		weight = wVec2;
		pAtMiddle = pVec2;
		pointNum = pAtMiddle.size();
		float x = 0; float y = 0; float dvb = 0;
		if (displayMode2[3] == '1') {

			glBegin(GL_LINES);
			for (float t = 0; t < 1; t = t + 0.01) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 0) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			glEnd();
			//glColor3f(1, 1, 1);
		}
		if (displayMode2[4] == '1') {
			//glColor3f(0, 1, 0);
			glBegin(GL_LINES);
			for (float t = 0; t > -5; t = t - 0.01) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 0) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			glVertex2d(x / dvb, y / dvb);
			for (float t = 1; t < 6; t = t + 0.01) {
				pointNum = pAtMiddle.size();
				x = 0; y = 0; dvb = 0;
				for (int i = 0; i < pAtMiddle.size(); i++) {
					x += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].first * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					y += 1.0 * coeff[pointNum - 1][i] * pAtMiddle[i].second * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
					dvb += 1.0 * coeff[pointNum - 1][i] * std::pow((1 - t), (pointNum - 1 - i)) * std::pow((t), i) * weight.at(i);
				}
				glVertex2d(x / dvb, y / dvb);
				if (t != 1) {
					glVertex2d(x / dvb, y / dvb);
				}
			}
			//glColor3f(1, 1, 1);
			glEnd();
		}
	}
	glutPostRedisplay();
	//glFlush();
}

void drawBar(int i, float wei) {
	if (wei > 0) {
		glColor3f(0.8, 0.8, 0);
	}
	else {
		glColor3f(0.7, 0, 0);
	}
	glBegin(GL_POLYGON);
	glVertex2f(2 + i, 0); glVertex2f(2 + i + 1, 0);
	glVertex2f(2 + i + 1, 0); glVertex2f(2 + i + 1, wei);
	glVertex2f(2 + i + 1, wei); glVertex2f(2 + i, wei);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(2 + i, 0); glVertex2f(2 + i + 1, 0);
	glVertex2f(2 + i + 1, 0); glVertex2f(2 + i + 1, wei);
	glVertex2f(2 + i + 1, wei); glVertex2f(2 + i, wei);
	glVertex2f(2 + i, wei); glVertex2f(2 + i, 0);
	glEnd();
	glutPostRedisplay();
}
void showWeight() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 35, -6, 11);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 350, 170);
	// draw scale
	glBegin(GL_LINES);
	glVertex2f(1, 0); glVertex2f(34, 0);
	glVertex2f(2, -5); glVertex2f(2, 10);
	glVertex2f(1, 5); glVertex2f(3, 5);
	glVertex2f(1, 10); glVertex2f(3, 10);
	glVertex2f(1, -5); glVertex2f(3, -5);
	glEnd();
	//
	if (getDrawingCurve() == 1) {
		pointNum = wVec1.size();
		if (pointNum > 1) {
			//draw bar for first point
			if (pointNum > 1) {
				for (int i = 0; i < wVec1.size(); i++) {
					drawBar(i, wVec1.at(i));
				}
			}
			glColor3f(1, 1, 1);
		}
	}
	else {
		pointNum = wVec2.size();
		if (pointNum > 1) {
			//draw bar for first point
			if (pointNum > 1) {
				for (int i = 0; i < wVec2.size(); i++) {
					drawBar(i, wVec2.at(i));
				}
			}
			glColor3f(1, 1, 1);
		}

	}
	glutPostRedisplay();
	//glFlush();
}
void showWin() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backr, backg, backb,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 500, 500);
	glLineWidth(1);
	//draw hull
	if (getDrawingCurve() == 1) {
		displayMode1 = getDisplayMode();
	}
	else {
		displayMode2 = getDisplayMode2();
	}

	pAtMiddle = pVec1;
	weight = wVec1;
	
	pointNum = pAtMiddle.size();
	if (pointNum > 1 && displayMode1[1] == '1') {
		glColor3f(hullr,hullg,hullb);
		glBegin(GL_POLYGON);
		for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
			glVertex2f(it->first,it->second);
		}
		glEnd();
		glColor3f(1,1,1);
	}
	//draw poly
	if (pointNum > 1 && displayMode1[0] == '1') {
		glColor3f(por, pog, pob);
		glBegin(GL_LINES);
		for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
			glVertex2f(it->first, it->second);
			if (it != pAtMiddle.begin()) {
				glVertex2f(it->first, it->second);
			}
		}
		//glVertex2f(lastP.first, lastP.second);
		glEnd();
		glColor3f(1, 1, 1);
	}
	//draw curve
	if (pointNum > 1 && (displayMode1[3] == '1' || displayMode1[4] == '1')) {
		glColor3f(cr, cg, cb);
		drawCurve(1);
		glColor3f(1, 1, 1);
	}
	//draw De Line
	if (pointNum > 1 && displayMode1[2] == '1') {
		glColor3f(dr, dg, db);
		drawDeLine(getT(), 1,1);
		glBegin(GL_POINTS);
		glVertex2f(firstP1.first, firstP1.second);
		haveFirst = 1;
		glEnd();
		std::pair<float, float> prevP = drawDeLine(getT(), 2,1);
		glColor3f(curvePointr, curvePointg, curvePointb);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(prevP.first, prevP.second);
		glEnd();
		glColor3f(1, 1, 1);
	}
	else {
		haveFirst = 0;
	}
	
	//draw points
	glPointSize(5);
	int index = 0;
	if (pAtMiddle.size() > 0) {
		glBegin(GL_POINTS);
		for (int i = 0; i < pAtMiddle.size(); i++) {
			if (weight.at(i) < 0) {
				glColor3f(prn, pgn, pbn);
			}
			else {
				glColor3f(prp, pgp, pbp);
			}
			glVertex2d(pAtMiddle.at(i).first, pAtMiddle.at(i).second);
		}
		glEnd();
		glColor3f(1, 1, 1);
	}
	//draw second curve
	
	pAtMiddle = pVec2;
	weight = wVec2;
	pointNum = pAtMiddle.size();
	if (pointNum > 1 && displayMode2[1] == '1') {
		glColor3f(hullr2, hullg2, hullb2);
		glBegin(GL_POLYGON);
		for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
			glVertex2f(it->first, it->second);
		}
		glEnd();
		glColor3f(1, 1, 1);
	}
	//draw poly
	if (pointNum > 1 && displayMode2[0] == '1') {
		glColor3f(por2, pog2, pob2);
		glBegin(GL_LINES);
		for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
			glVertex2f(it->first, it->second);
			if (it != pAtMiddle.begin()) {
				glVertex2f(it->first, it->second);
			}
		}
		glEnd();
		glColor3f(1, 1, 1);
	}
	//draw curve
	if (pointNum > 1 && (displayMode2[3] == '1' || displayMode2[4] == '1')) {
		glColor3f(cr2, cg2, cb2);
		drawCurve(2);
		glColor3f(1, 1, 1);
	}
	//draw De Line
	if (pointNum > 1 && displayMode2[2] == '1') {
		glColor3f(dr2, dg2, db2);
		drawDeLine(getT2(), 1,2);
		glBegin(GL_POINTS);
		glVertex2f(firstP2.first, firstP2.second);
		haveFirst = 1;
		glEnd();
		std::pair<float, float> prevP = drawDeLine(getT2(), 2,2);
		glColor3f(curvePointr2, curvePointg2, curvePointb2);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(prevP.first, prevP.second);
		glEnd();
		glColor3f(1, 1, 1);
	}
	else {
		haveFirst = 0;
	}

	//draw points
	glPointSize(5);
	index = 0;
	if (pAtMiddle.size() > 0) {
		glBegin(GL_POINTS);
		for (int i = 0; i < pAtMiddle.size(); i++) {
			if (weight.at(i) < 0) {
				glColor3f(prn2, pgn2, pbn2);
			}
			else {
				glColor3f(prp2, pgp2, pbp2);
			}
			glVertex2d(pAtMiddle.at(i).first, pAtMiddle.at(i).second);
		}
		glEnd();
		glColor3f(1, 1, 1);
	}
	glutPostRedisplay();
	//glFlush();
}
void mouse_active_move_weight(int x, int y) {
	//int xtoc = x / 10;
	if (getDrawingCurve() == 1) {
		float ytoc = -(y - 110) / 10.0;
		if (currWeightIndex != -2) {
			if (ytoc > 10) {
				ytoc = 10;
			}
			if (ytoc < -5) {
				ytoc = -5;
			}
			wVec1.at(currWeightIndex) = ytoc;
			showWeight();
			glutPostRedisplay();
		}
	}else {
		float ytoc = -(y - 110) / 10.0;
		if (currWeightIndex != -2) {
			if (ytoc > 10) {
				ytoc = 10;
			}
			if (ytoc < -5) {
				ytoc = -5;
			}
			wVec2.at(currWeightIndex) = ytoc;
			showWeight();
			glutPostRedisplay();
		}
	}
}
static void mouse_press_weight(int button, int state, int x, int y) {

	int xtoc = x / 10;
	float ytoc = -(y - 110) / 10.0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (getDrawingCurve() == 1) {
			if (xtoc >= 2 && xtoc <= pVec1.size()+1) {
				currWeightIndex = xtoc - 2;
			}
		}
		else {
			if (xtoc >= 2 && xtoc <= pVec2.size()+1) {
				currWeightIndex = xtoc - 2;
			}
		}
		glutMotionFunc(mouse_active_move_weight);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		currWeightIndex = -2;
	}
	glutPostRedisplay();
}

void mouse_active_move(int x, int y) {
	float xtoc = (x - 250.0) / 250.0;
	float ytoc = -(y - 250.0) / 250.0;
	if (getDrawingCurve() == 1) {
		if (mode == 2 && moving != -2) {
			if (moving == -1) {
				pVec1.back().first = xtoc;
				pVec1.back().second = ytoc;
			}
			else if (moving == -3) {
				float y1 = pVec1.at(0).first;
				float y2 = pVec1.at(1).second;
				//if (ytoc < y2 && ytoc > y1) {
				setT((ytoc - y1) / (y2 - y1));
				//}
			}
			else {
				pVec1[moving].first = xtoc;
				pVec1[moving].second = ytoc;
			}
		}
	}
	else {
		if (mode == 2 && moving != -2) {
			if (moving == -1) {
				pVec2.back().first = xtoc;
				pVec2.back().second = ytoc;
			}
			else if (moving == -3) {
				float y1 = pVec2.at(0).first;
				float y2 = pVec2.at(1).second;
				//if (ytoc < y2 && ytoc > y1) {
				setT2((ytoc - y1) / (y2 - y1));
				//}
			}
			else {
				pVec2[moving].first = xtoc;
				pVec2[moving].second = ytoc;
			}
		}
	}
	showWin();
}

static void mouse_press(int button, int state, int x, int y) {
	if (getDrawingCurve() == 1) {
		pAtMiddle = pVec1;
		weight = wVec1;
	}
	else {
		pAtMiddle = pVec2;
		weight = wVec2;
	}
	float xtoc = (x - 250.0) / 250.0;
	float ytoc = - (y - 250.0) / 250.0;
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	if (getrDe() == 2) {
		if (reset.size() > 0) {
			pAtMiddle = reset;
			pointNum = pAtMiddle.size();
			reset.clear();
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mode = getMouseMode();
		if (mode == 1) {				//define
			if(pointNum < 32){
				pAtMiddle.push_back(std::make_pair(xtoc,ytoc));
				weight.push_back(1);
				pointNum++;
			}
			reset.clear();
			
		}
		else if (mode == 2 && pAtMiddle.size()>0) {			//move
			glutMotionFunc(mouse_active_move);
			float absxl = std::abs(std::abs(pAtMiddle.back().first) - std::abs(xtoc));
			float absyl = std::abs(std::abs(pAtMiddle.back().second) - std::abs(ytoc));
			float absx, absy;
			if (getDrawingCurve() == 1) {
				absx = std::abs(std::abs(firstP1.first) - std::abs(xtoc));
				absy = std::abs(std::abs(firstP1.second) - std::abs(ytoc));
			}else{
				absx = std::abs(std::abs(firstP2.first) - std::abs(xtoc));
				absy = std::abs(std::abs(firstP2.second) - std::abs(ytoc));
			}
			if (absxl < 0.02 && absyl < 0.02) {
				moving = -1; //last point
			}else if (absx < 0.02 && absy < 0.02) {
				moving = -3;
			}else{
				int index = 0;
				for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
					absx = std::abs(std::abs(it->first) - std::abs(xtoc));
					absy = std::abs(std::abs(it->second) - std::abs(ytoc));
					if (absx < 0.02 && absy < 0.02) {
						moving = index;
						break;
					}
					index++;
				}
			}
			reset.clear();
		}
		else if (mode == 3 && pAtMiddle.size() > 0) {			//delete
			if (pointNum > 1) {
				lastP = pAtMiddle.back();
				float absx = std::abs(std::abs(lastP.first) - std::abs(xtoc));
				float absy = std::abs(std::abs(lastP.second) - std::abs(ytoc));
				if (absx < 0.02 && absy < 0.02) {
					pAtMiddle.pop_back();
					weight.pop_back();
				}
				else {
					int index = 0;
					for (std::vector<std::pair<float, float>>::iterator it = pAtMiddle.begin(); it != pAtMiddle.end(); ++it) {
						absx = std::abs(std::abs(it->first) - std::abs(xtoc));
						absy = std::abs(std::abs(it->second) - std::abs(ytoc));
						if (absx < 0.02 && absy < 0.02) {
							break;
						}
						index++;
					}
					if (index < pAtMiddle.size()) {
						pAtMiddle.erase(pAtMiddle.begin() + index);
						weight.erase(weight.begin() + index);
					}
				}
			}
			reset.clear();
		}

		if (getDrawingCurve() == 1) {
			pVec1 = pAtMiddle;
			wVec1 = weight;
		}
		else {
			pVec2 = pAtMiddle;
			wVec2 = weight;
		}
		// raise degree weight need to be set
		if (getrDe() == 1) {
			if (getDrawingCurve() == 1) {
				pointNum = pVec1.size();
				if (pointNum < 32) {
					lastP = pVec1.back();
					std::vector<std::pair<float, float>> temp;
					temp.push_back(pVec1.front());
					for (int i = 1; i < pVec1.size(); i++) {
						std::pair<float, float> prevP = pVec1.at(i - 1);
						std::pair<float, float> thisP = pVec1.at(i);
						float nowx = 1.0 * prevP.first * i / 1.0 / pointNum + 1.0 * thisP.first * (1.0 - i / 1.0 / pointNum);
						float nowy = 1.0 * prevP.second * i / 1.0 / pointNum + 1.0 * thisP.second * (1.0 - i / 1.0 / pointNum);
						temp.push_back(std::make_pair(nowx, nowy));

					}
					temp.push_back(lastP);
					reset = pVec1;
					pVec1 = temp;
					wVec1.push_back(1);
					resetrDe();
				}
			}
			else {
				pointNum = pVec2.size();
				if (pointNum < 32) {
					lastP = pVec2.back();
					std::vector<std::pair<float, float>> temp;
					temp.push_back(pVec2.front());
					for (int i = 1; i < pVec2.size(); i++) {
						std::pair<float, float> prevP = pVec2.at(i - 1);
						std::pair<float, float> thisP = pVec2.at(i);
						float nowx = 1.0 * prevP.first * i / 1.0 / pointNum + 1.0 * thisP.first * (1.0 - i / 1.0 / pointNum);
						float nowy = 1.0 * prevP.second * i / 1.0 / pointNum + 1.0 * thisP.second * (1.0 - i / 1.0 / pointNum);
						temp.push_back(std::make_pair(nowx, nowy));

					}
					temp.push_back(lastP);
					reset = pVec2;
					pVec2 = temp;
					wVec2.push_back(1);
					resetrDe();
				}
			}
			glutPostRedisplay();
			//TODO
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (mode == 2) {
			moving = -2;
		}
	}
}
void ColorMenu(int selection) {
	float tempr, tempg, tempb;
	tempr = getColorr();
	tempg = getColorg();
	tempb = getColorb();
	if (getDrawingCurve() == 1) {
		switch (selection) {
		case 0:
			backr = tempr; backg = tempg; backb = tempb;
			break;
		case 1:
			hullr = tempr; hullg = tempg; hullb = tempb;
			break;
		case 2:
			cr = tempr; cg = tempg; cb = tempb;
			break;
		case 3:
			curvePointr = tempr; curvePointg = tempg; curvePointb = tempb;
			break;
		case 4:
			prp = tempr; pgp = tempg; pbp = tempb;
			break;
		case 5:
			prn = tempr; pgn = tempg; pbn = tempb;
			break;
		case 6:
			por = tempr; pog = tempg; pob = tempb;
			break;
		case 7:
			dr = tempr; dg = tempg; db = tempb;
		}
	}
	else {
		switch (selection) {
		case 0:
			backr = tempr; backg = tempg; backb = tempb;
			break;
		case 1:
			hullr2 = tempr; hullg2 = tempg; hullb2 = tempb;
			break;
		case 2:
			cr2 = tempr; cg2 = tempg; cb2 = tempb;
			break;
		case 3:
			curvePointr2 = tempr; curvePointg2 = tempg; curvePointb2 = tempb;
			break;
		case 4:
			prp2 = tempr; pgp2 = tempg; pbp2 = tempb;
			break;
		case 5:
			prn2 = tempr; pgn2 = tempg; pbn2 = tempb;
			break;
		case 6:
			por2 = tempr; pog2 = tempg; pob2 = tempb;
			break;
		case 7:
			dr2 = tempr; dg2 = tempg; db2 = tempb;
		}
	}

	glutPostRedisplay();
}
void resizeWin(int w, int h) { ; }
void myMouse(int, int, int, int) { ; }
void myIdle() { ; }
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	winSizeX = 681;
	winSizeY = 500;
	glutInitWindowSize(winSizeX, winSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 500, 500);
	displayWin = glutCreateWindow("Bézier Curves");
	glutDisplayFunc(showWin);
	glutMouseFunc(mouse_press);
	int root = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Set Background Color", 0);
	glutAddMenuEntry("Set Convex Hull Color", 1);
	glutAddMenuEntry("Set Curve Color", 2);
	glutAddMenuEntry("Set Curve Point Color", 3);
	glutAddMenuEntry("Set Positive Control Point Color", 4);
	glutAddMenuEntry("Set Negative Control Point Color", 5);
	glutAddMenuEntry("Set Control Polygon Color", 6);
	glutAddMenuEntry("Set DeCasteljau Color", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutInitWindowSize(350, 170);
	displayWeight = glutCreateWindow("Weight");
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
	glutDisplayFunc(showWeight);
	glutMouseFunc(mouse_press_weight);

	buildGLUI(displayWin);
	//Background, convex hull, curve, curve point, control point, control polygon, DeCasteljau.

	//构建杨辉三角
	for (int i = 0; i < 32; i++) {
		coeff[i][i] = 1;
		coeff[i][0] = 1;
	}
	for (int i = 2; i < 32; i++) {
		for (int j = 1; j <= i - 1; j++) {
			coeff[i][j] = coeff[i - 1][j - 1] + coeff[i - 1][j];
		}
	}


	glutMainLoop();
	return 0;
}