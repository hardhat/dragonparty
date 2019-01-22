#ifndef PLAYER_H
#define PLAYER_H
#include "actor.h"

class Tile;

class Player : public Actor {

public:
	Player(Tile *tile);
	virtual void resetGame();
	virtual void update(int elapsed);
	virtual void draw();
	virtual void handleAction(int id,bool down);
};

#endif
