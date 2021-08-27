#include "ostacoli.hpp"

ostacoli::ostacoli() {}

ostacoli::ostacoli(int x, int y, int dmg, int mul) {
	xPos = x;
	yPos = y;
	damage = dmg;
	multi = mul;
	despawn = false;
}

int ostacoli::getDmg(int currLvl) {
	return damage + ((currLvl-1) * multi);
}

int ostacoli::getX() { return xPos; }

int ostacoli::getY() { return yPos; }

void ostacoli::muovi() {
	yPos++;
}

void ostacoli::setDespawn(bool d) {
	despawn = d;
}
