#include "gameManager.hpp"
using namespace std;

gameManager::gameManager() {}

gameManager::gameManager(int d) {
	diff = d;
	flashes = 0;
	maxOstacoli = 5 * (d + 1);
	numOstacoli = 0;
	punteggio = maxPunti = 100;
	scudStart = doubleStart = 0;
	livello = 1;
	street = strada();
	user = car(street.getW() / 2, street.getH() - 3, '@');
	quit = pause = isShield = isDouble = false;
	gameTick = 0;
	headTronco = NULL;
	headChiodo = NULL;
	headBuco = NULL;
	headEnemy = NULL;
	headPunti = NULL;
	scud = scudo(0, -1, 0, 0, '/', '\\');
	doub = raddoppia(0, -1, 0, 0, 'X', '2');
}

void gameManager::start() {
	srand(time(NULL));
	char m = 32;
	system("CLS");
	preGame();
	user.scriviSuStrada(street);
	street.stampa(isShield);

	while (punteggio>0 && !quit) {
		if (isShield && scudStart == gameTick - durataScudo) {
			scud.setSpawned(false);
			isShield = false;
		}
		if (isDouble && doubleStart == gameTick - durataDoppia) {
			doub.setSpawned(false);
			isDouble = false;
		}
		gameTick++;
		if (gameTick % 50 == 0)
			if (isDouble)
				punteggio += 2 * addTick;
			else punteggio += addTick;
		if (punteggio > maxPunti) maxPunti = punteggio;
		if(punteggio>100)	livello = punteggio / 100;
		if(livello % 5 == 0) maxOstacoli = (5 * (diff+ 1) + (livello / 5));
		if(gameTick % 4 == 0)
			setSpawn();
		if (flashes > 0) flashes--;
		if (flashes % 2 != 0) user.setSymb(' ');
		else user.setSymb('@');
		muoviUser();
		if (pause) pausa();

		if (scud.getSpawned())
			scud.muovi();
		if (doub.getSpawned())
			doub.muovi();
		muoviTronco(headTronco);
		muoviBuco(headBuco);
		muoviChiodo(headChiodo);
		muoviEnemy(headEnemy);
		muoviPunti(headPunti);
		
		if (scud.getSpawned())
			isShield = scud.checkCollision(user.getPosX(), user.getPosY());
		if (doub.getSpawned())
			isDouble = doub.checkCollision(user.getPosX(), user.getPosY());
		checkCollisionTronco(headTronco, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionBuco(headBuco, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionChiodo(headChiodo, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionEnemy(headEnemy, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionPunti(headPunti, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isDouble);

		headTronco = manageTronco(headTronco, numOstacoli);
		headBuco = manageBuco(headBuco, numOstacoli);
		headChiodo = manageChiodo(headChiodo, numOstacoli);
		headEnemy = manageEnemy(headEnemy, numOstacoli);
		headPunti = managePunti(headPunti, numOstacoli);

		street.clean();
		user.scriviSuStrada(street);
		printTronco(street, headTronco);
		printBuco(street, headBuco);
		printChiodo(street, headChiodo);
		printEnemy(street, headEnemy);
		printPunti(street, headPunti);
		if (scud.getSpawned())
			scud.stampaSuStrada(street);
		if (doub.getSpawned())
			doub.stampaSuStrada(street);
		street.stampa(isShield);


		gotoxy(street.getW() + 1, 4);
		cout << "Punteggio: " << punteggio << "   ";
		gotoxy(street.getW() + 1, 5);
		cout << "Livello: " << livello << "   ";
		gotoxy(street.getW() + 1, 10);
		if (isShield)	cout << "Shield: " << durataScudo - (gameTick - scudStart) << "      " ;
		else cout << "                                          ";
		gotoxy(street.getW() + 1, 11);
		if (isDouble)	cout << "Double: "<< durataDoppia - (gameTick - doubleStart) << "         ";
		else cout << "                                          ";
	}
	system("cls");
	gotoxy(10, 10);
	cout << "GAME OVER";
	gotoxy(10, 11);
	cout<<"Highscore: " << maxPunti;
	Sleep(1000);
	gotoxy(10, 20);
}

void gameManager::muoviUser() {
	char m;
	if (_kbhit()) {
		m = _getch();
		if (m == 's' || m == 'S' || m == 80) user.getPosY() < street.getH() - 3 ? user.muovi(DOWN) : user.muovi(STOP);
		else if (m == 'w' || m == 'W' || m == 72) user.getPosY() > 3 ? user.muovi(UP) : user.muovi(STOP);
		else if (m == 'a' || m == 'A' || m == 75) user.getPosX() > 3 ? user.muovi(LEFT) : !isShield ? fuoriStrada(&flashes, &punteggio, user, true) : user.muovi(RIGHT);
		else if (m == 'd' || m == 'D' || m == 77) user.getPosX() < street.getW() - 3 ? user.muovi(RIGHT) : !isShield ? fuoriStrada(&flashes, &punteggio, user, false) : user.muovi(LEFT);
		else if (m == 'p' || m == 'P') pause = true;
		else user.muovi(STOP);
	}
}

void gameManager::preGame() {
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, 2);
	gotoxy(street.getW() / 2, street.getH() / 2);
	cout << "3";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 15);
	cout << "2";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "1";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 15);
	cout << "START";
	Sleep(1000);
}

void gameManager::setSpawn() {
	int i = rand() % 20;
	int x;
	switch (i)
	{
		case 0:
		case 7:
		case 14:
			x = rand() % (street.getW() - 5) + 1;
			if (checkTronco(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headTronco = addTronco(headTronco, x,diff);
			}
			break;
		case 1:
		case 8:
			x = rand() % (street.getW() - 4) + 1;
			if (checkEnemy(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headEnemy = addEnemy(headEnemy, x, diff);
			}
			break;
		case 2:
		case 9:
		case 12:
			x = rand() % (street.getW() - 4) + 1;
			if (checkBuco(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headBuco = addBuco(headBuco, x, diff);
			}
			break;
		case 3:
		case 10:
			x = rand() % (street.getW() - 4) + 1;
			if (checkPunti(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headPunti = addPunti(headPunti, x);
			}
			break;
		case 4:
		case 11:
		case 15:
			x = rand() % (street.getW() - 3) + 1;
			if (checkChiodo(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headChiodo = addChiodo(headChiodo, x, diff);
			}
			break;
		case 5:
			//RADDOPPIA
			x = rand() % (street.getW() - 3) + 1;
			if (checkDouble(street, x) && doub.getSpawned() == false && !isDouble) {
				doub.setSpawned(true);
				doub.setPosX(x);
				doub.setPosY(-1);
				doubleStart = gameTick;
			}
			break;
		case 6:
			//SCUDO
			x = rand() % (street.getW() - 3) + 1;
			if (checkScudo(street, x) && scud.getSpawned() == false && !isShield) {
				scud.setSpawned(true);
				scud.setPosX(x);
				scud.setPosY(-1);
				scudStart = gameTick;
			}
			break;
		}
}

void gameManager::fuoriStrada(int* f, int* p, car& user, bool dx) {
	*f = MAX_FLASHES;
	*p -= 50 * diff	;
	if (dx) user.muovi(RIGHT);
	else user.muovi(LEFT);
}

bool gameManager::restart() {
	system("cls");
	bool ready = false;
	char m;
	int scelta = 0;
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "__   __            _                     " << endl;
	cout << "\\ \\ / /           | |                    " << endl;
	cout << " \\ V /___  _   _  | |     ___  ___  ___  " << endl;
	cout << "  \\ // _ \\| | | | | |    / _ \\/ __|/ _ \\ " << endl;
	cout << "  | | (_) | |_| | | |___| (_) \\__ \\  __/ " << endl;
	cout << "  \\_/\\___/ \\__,_| \\_____/\\___/|___/\\___| " << endl;
	cout << "                                         " << endl;
	gotoxy(5, 8);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "Esci";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(5, 10);
	cout << "Ricomincia";
	while (!ready) {
		if (_kbhit()) {
			m = _getch();
			if (m == 's' || m == 'S' || m == 80) {
				scelta++;
				scelta %= 2;
			}
			else if (m == 'w' || m == 'W' || m == 72) {
				if (scelta != 0) scelta--;
				else scelta = 1;
			}
			else if (m == 13 || m == 32) {
				ready = true;
			}
			switch (scelta)
			{
			case 0:
				gotoxy(5, 8);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Esci";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(5, 10);
				cout << "Ricomincia";
				break;
			case 1:
				gotoxy(5, 10);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Ricomincia";
				gotoxy(5, 8);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Esci";
				break;
			}
		}
	}
	if (scelta == 0) return false;
	else return true;
}

void gameManager::pausa() {
	bool ready = false;
	char m;
	int scelta = 0;
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(street.getW() / 2 - 4, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "Esci";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
	cout << "Riprendi";
	while (!ready) {
		if (_kbhit()) {
			m = _getch();
			if (m == 's' || m == 'S' || m == 80) {
				scelta++;
				scelta %= 2;
			}
			else if (m == 'w' || m == 'W' || m == 72) {
				if (scelta != 0) scelta--;
				else scelta = 1;
			}
			else if (m == 13 || m == 32 || m == 'p' || m == 'P') {
				if (m == 'p' || m == 'P')
					scelta = 1;
				ready = true;
			}
			switch (scelta)
			{
			case 0:
				gotoxy(street.getW() / 2 - 4, street.getH() / 2);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Esci";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
				cout << "Riprendi";
				break;
			case 1:
				gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Riprendi";
				gotoxy(street.getW() / 2 - 4, street.getH() / 2);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Esci";
				break;
			}
		}
	}
	if (scelta == 0) quit = true;
	else {
		gotoxy(street.getW() / 2 - 4, street.getH() / 2 );
		cout << "          ";
		gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
		cout << "          ";
		pause = false;
		preGame();
	}
}