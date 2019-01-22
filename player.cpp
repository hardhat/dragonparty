#include <stdio.h>

#include "main.h"
#include "player.h"

Player::Player(Tile *tile) : Actor(tile)
{
	//printf("Player::Player()\n");
	//resetGame();
}

void Player::resetGame()
{
	Actor::resetGame();
	avatarId=40;
	avatarDeadId=50;
	shieldId=4;
    tx=10;
    ty=12;
}

void Player::update(int elapsed)
{
	Actor::update(elapsed);
}

void Player::draw()
{
	Actor::draw();
}

void Player::handleAction(int id,bool down)
{

}
