#pragma once


#include <iostream>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <queue>
#include <deque>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <malloc.h>
#include "Shader.h"

#define COLONNE 60
#define RIGHE 60
#define a 90
#define l 90



struct pos {
	int x;
	int y;
};



class Snake {
public:
	int (*camp)[60];
	Snake(int x, int y,int cam[][60]);
	void avanti();
	void indietro();
	void destra();
	void sinistra();
	void mangia();
	int getX();
	int getY();
	bool colpito();
	~Snake();
	void gotoxy(int x, int y);
	bool nmkl;
private:
	pos actpos;
	std::deque<pos> ser;

};


