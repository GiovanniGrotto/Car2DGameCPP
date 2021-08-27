#include "car.hpp"
#include <iostream>
using namespace std;

car::car() {}

car::car(int posx, int posy, char sy) {
	posX = posx;
	posY = posy;
	symb = sy;
}

int car::getPosX() {
	return posX;
}
int car::getPosY() {
	return posY;
}

void car::muovi(eDir direction) {
	switch (direction) {
	case STOP:
		break;
	case 1:
		posY = posY - 4;
		break;
	case 2:
		posX = posX + 4;
		break;
	case 3:
		posY = posY + 4;
		break;
	case 4:
		posX = posX - 4;
		break;
	}
}

void car::scriviSuStrada(strada &s) {
	s.mappa[posY][posX] = symb;
	s.mappa[posY+1][posX] = symb;
	s.mappa[posY+2][posX] = symb;
	s.mappa[posY-1][posX] = symb;
	s.mappa[posY][posX-1] = symb;
	s.mappa[posY][posX+1] = symb;
	s.mappa[posY+2][posX-1] = symb;
	s.mappa[posY+2][posX+1] = symb;
}

void car::setSymb(char s) { symb = s; }
