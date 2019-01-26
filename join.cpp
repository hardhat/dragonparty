#include "main.h"
#include "game.h"
#include "player.h"
#include "font.h"
#include "join.h"

Join::Join(Tile *tile)
{
    this->tile=tile;

    resetGame();
}

Join::~Join()
{
}

void Join::resetGame()
{
    for(int i=0;i<6;i++) {
        playerDone[i]=false;
    }
    for(int i=0;i<6;i++) {
        playerJoin[i]=false;
    }
    int i=0;
    for(PlayerList::iterator p=game.playerList.begin();p!=game.playerList.end();p++) {
        Player *player=*p;

        player->resetGame(player->type,4+i*2,0);
        player->health=-1;
        i++;
    }
}

void Join::update(int elapsed)
{
}

void Join::draw()
{
    maptop=0;

    for(int j=0;j<4;j++) {
        for(int i=0;i<4;i++) {
            tile->draw(90+i+j*10,16+i,5+j);
        }
    }

    drawMessage(FONT_HEADLINE,"Select your player",10,-8);
    drawMessage(FONT_NOTICE,"Left and right then hit A",10,30);

    for(int i=0;i<6;i++) {
        char buffer[256];
        sprintf(buffer,"Player %d",i+1);
        Player *player=game.playerList[i];
        drawMessage(FONT_LABEL,buffer,4,48+i*32);

        if(playerJoin[i]) {
            if(playerDone[i]) {
                    tile->draw(player->avatarId,6,4+i*2);
            } else {
                for(int j=0;j<3;j++) {
                    if(player->type==j) tile->draw(24,6+j*2,4+i*2);
                    tile->draw(player->getAvatarId(j),6+j*2,4+i*2);
                }
            }
        } else {
            drawMessage(FONT_LABEL,"Hit START to join",6*16,48+i*32);
        }
    }
}

void Join::handleAction(int which,int id,bool down)
{
    if(which<0 || (unsigned int)which>=game.playerList.size()) return;

    Player *player = game.playerList[which];
    int count=0;

    D("player %d: ",which);
    D("id %d, ",id);
    D("down? %d\n",down?1:0);

    if(!down) return;
    switch(id) {
    case DPAD_START:
    case DPAD_UP:
        playerJoin[which]=true;
        playerDone[which]=false;
        break;
    case DPAD_LEFT:
        if(!playerJoin[which]) break;
        if(playerDone[which]) break;
        player->setType(player->type-1);
        break;
    case DPAD_RIGHT:
        if(!playerJoin[which]) break;
        if(playerDone[which]) break;
        player->setType(player->type+1);
        break;
    case DPAD_A:
        if(!playerJoin[which]) break;
        playerDone[which]=true;
        player->resetGame(player->type,4+which*2,116);
        D("player %d: done\n",which);
        break;
    case DPAD_SELECT:
        for(int i=0;i<6;i++) {
            D("player %d: ",which);
            D("join? %d,",playerJoin[i]?1:0);
            D("done? %d\n",playerDone[i]?1:0);
            if(playerJoin[i] && !playerDone[i]) return;
            if(playerJoin[i]) count++;
        }
        if(count==0) return;
        D("player %d: select\n",which);
        game.setMode(MODE_LEVEL);
        break;
    }
}
