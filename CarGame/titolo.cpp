#include "titolo.hpp"
#include "strada.hpp"
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

titolo::titolo() {}

void titolo::stampaTitolo() {
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "            _____  _____ _____ _____      _____            _____ ______ \n";
	Sleep(200);
	cout << "     /\\    / ____|/ ____|_   _|_   _|    |  __ \\     /\\   / ____|  ____| \n"; 
	Sleep(200);
	cout << "    /  \\  | (___ | |      | |   | |      | |__) |   /  \\ | |    | |__   \n";
	Sleep(200);
	cout << "   / /\\ \\  \\___ \\| |      | |   | |      |  _  /   / /\\ \\| |    |  __|   \n";
	Sleep(200);
	cout << "  / ____ \\ ____) | |____ _| |_ _| |_     | | \\ \\  / ____ \\ |____| |____  \n"; 
	Sleep(200);
	cout << " /_/    \\_\\_____/ \\_____|_____|_____|    |_|  \\_\\/_/    \\_\\_____|______| \n";
	cout << "                                           \n";
	cout << "                                           \n";

	cout << "Premere un tasto per continuare\n";
	while (!_kbhit()) {}
	char m = _getch();
}

int titolo::difficulty() {
	system("CLS");
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char m;
	int scelta = 0;
	bool ready = false;
	gotoxy(5, 1);
	cout << "Scelgi la difficolta' ";
	gotoxy(5, 5);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "Facile";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(5, 7);
	cout << "Medio";
	gotoxy(5, 9);
	cout << "Difficile";
	while (!ready) {
		if (_kbhit()) {
			m = _getch();
			if (m == 's' || m == 'S' || m==80) {
				scelta++;
				scelta %= 3;
			}
			else if (m == 'w' || m == 'W' || m == 72) {
				if (scelta != 0) scelta--;
				else scelta = 2;
			}
			else if (m == 13 || m == 32) {
				ready = true;
			}
			switch (scelta)
			{
			case 0:
				gotoxy(5, 5);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Facile";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(5, 7);
				cout << "Medio";
				gotoxy(5, 9);
				cout << "Difficile";
				break;
			case 1:
				gotoxy(5, 7);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Medio";
				gotoxy(5, 5);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Facile";
				gotoxy(5, 9);
				cout << "Difficile";
				break;
			case 2:
				gotoxy(5, 9);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Difficile";
				gotoxy(5, 5);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Facile";
				gotoxy(5, 7);
				cout << "Medio";
				break;
			}
		}
	}
	return scelta;
}