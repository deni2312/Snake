#include "../include/pch.h"
#include "../include/Snake.h"
Snake::Snake(int x, int y,int cam[][60])
{
	camp = cam;
	cam[y][x] = 'v';
	actpos.x = x;
	actpos.y = y;
	ser.push_front(actpos);
	nmkl = false;
}


void Snake::avanti()
{
	if (!nmkl) {
		pos ulnm;
		ulnm.x = ser.back().x;
		ulnm.y = ser.back().y;
		ser.pop_back();
		camp[ulnm.y][ulnm.x] = ' ';
		
	}

	actpos.y = actpos.y - 1;
	ser.push_front(actpos);
	camp[actpos.y][actpos.x] = 'v';
	nmkl = false;
}


void Snake::indietro()
{
	if (!nmkl) {
		pos ulnm;
		ulnm.x = ser.back().x;
		ulnm.y = ser.back().y;
		ser.pop_back();
		camp[ulnm.y][ulnm.x] = ' ';
		
	}

	actpos.y = actpos.y + 1;
	ser.push_front(actpos);
	camp[actpos.y][actpos.x] = 'v';
	nmkl = false;
}

void Snake::destra()
{
	if (!nmkl) {
		pos ulnm;
		ulnm.x = ser.back().x;
		ulnm.y = ser.back().y;
		ser.pop_back();
		camp[ulnm.y][ulnm.x] = ' ';
		
	}

	actpos.x = actpos.x + 1;
	ser.push_front(actpos);
	camp[actpos.y][actpos.x] = 'v';
	
	nmkl = false;
}


void Snake::sinistra()
{

	if (!nmkl) {
		pos ulnm;
		ulnm.x = ser.back().x;
		ulnm.y = ser.back().y;

		ser.pop_back();
		camp[ulnm.y][ulnm.x] = ' ';
		
	}

	actpos.x = actpos.x - 1;
	ser.push_front(actpos);
	camp[actpos.y][actpos.x] = 'v';
	

	nmkl = false;
}

void Snake::mangia()
{

	nmkl = true;
}

int Snake::getX()
{
	return actpos.x;
}

int Snake::getY()
{
	return actpos.y;
}

bool Snake::colpito()
{
	if (ser.size() != 0) {
		if (ser.size() != 1) {
			for (int i = 0; i < ser.size(); i++) {
				if (i != 0) {
					if (ser.at(i).x == actpos.x && ser.at(i).y == actpos.y) {
						return true;
					}
				}
			}
		}
	}
	return false;
}


Snake::~Snake()
{
}

void Snake::gotoxy(int x, int y) {
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
