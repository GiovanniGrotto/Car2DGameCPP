#include "strada.hpp"
using namespace std;

strada::strada() {
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			mappa[i][j] = '?';
		}
	}
}

void strada::clean() {
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) mappa[i][j]='|';
			else mappa[i][j] = '?';
		}
	}
}

void strada::stampa(bool isShield) {
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			gotoxy(j, i);
			if (mappa[i][j] == '?') {
				SetConsoleTextAttribute(hconsole, 15);
				cout << ' ';
			}
			else {
				if (mappa[i][j] == '^') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == '=') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == '#') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'O') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'x') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'X') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '2') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == 'P') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '+') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '\\') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '/') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '@') {
					if(isShield)
						SetConsoleTextAttribute(hconsole, 9);
					else
						SetConsoleTextAttribute(hconsole, 15);
				}
				else if(mappa[i][j] == '|') SetConsoleTextAttribute(hconsole, 15);
				cout << mappa[i][j];
			}
		}
	}
}

int strada::getH() { return heigth; }
int strada::getW() { return width; }
