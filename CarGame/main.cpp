#include <iostream>
#include "titolo.hpp"
 #include "gameManager.hpp"
using namespace std;

int main() {
    titolo title = titolo();
    title.stampaTitolo();
    int diff;
    gameManager game;
    do {
        diff = title.difficulty();
        game = gameManager(diff);
        game.start();
    } while (game.restart());
    return 0;

}




