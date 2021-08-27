#ifndef OSTACOLI_H
#define OSTACOLI_H
#include "strada.hpp"
class ostacoli {
	protected:
		int xPos;
		int yPos;
		int damage;
		int multi;
		bool despawn;
	public:
		ostacoli();
		ostacoli(int x, int y, int dmg, int mul);
		int getDmg(int currLvl);
		int getX();
		int getY();
		void muovi();
		void setDespawn(bool d);
};
#endif