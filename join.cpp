#include "Join.h"

Join::Join()
{
    //ctor
}

Join::~Join()
{
    //dtor
}

void Join::resetGame()
{

}

void Join::update(int elapsed)
{
}

void Join::draw()
{
    int oldmaptop=maptop; maptop=0;

    drawMessage(FONT_HEADLINE,"Select your player",10,30);
    drawMessage(FONT_LABEL)
    maptop=oldmaptop;
}

void Join::handleAction(int id,bool down)
{
    Player *player = game.playerList.front();

    if(!down) return;
    switch(id) {
    case DPAD_LEFT:
        player->type++;
        player->avatarId=;
        break;
    case DPAD_RIGHT:
        player->type--;
        player->avatarId=;
        breaks
    case DPAD_UP:
        // do nothing.
        break;
    case DPAD_DOWN:
        playerDone[0]=true;
        break;
    }
}
