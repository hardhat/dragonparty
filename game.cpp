#include <SDL.h>
#include "main.h"
#include "game.h"
#include "tile.h"
#include "layer.h"
#include "font.h"
#include "sound.h"
#include "actor.h"
#include "player.h"

Game game;

Game::Game() {
    tile=0;
    mode=0;
    bgLayer=0;
    fgLayer=0;
    characterLayer=0;
    hobgoblinLayer=0;
}

Game::~Game() {
}

void Game::resetGame()
{
    for(PlayerList::iterator p=playerList.begin();p!=playerList.end();p++) {
        Player *player=*p;
        delete player;
    }
    playerList.clear();

    for(ActorList::iterator p=enemyList.begin();p!=enemyList.end();p++) {
        Actor *enemy=*p;
        delete enemy;
    }
    enemyList.clear();

    if(hobgoblinLayer) {
        delete hobgoblinLayer;
        hobgoblinLayer=0;
    }

    if(!tile) {
        tile=new Tile("DRAGON_by_Mike_Hackett_alpha.png",16,16);
        bgLayer=new Layer(tile);
        fgLayer=new Layer(tile);
        characterLayer=new Layer(tile);
        hobgoblinLayer=new Layer(tile);
    }

    mode=0;
    //layertop=0;

    bgLayer->load("data/level_background.csv");
    fgLayer->load("data/level_foreground.csv");
    characterLayer->load("data/level_characters.csv");
    hobgoblinLayer->load("data/level_hobgoblin.csv");

    playerList.push_back(new Player(tile));
}

void Game::update(int elapsed)
{
    if(playerList.size()==0) return;

}

void Game::draw()
{
    bgLayer->draw();
    fgLayer->draw();

    for(ActorList::iterator p=enemyList.begin();p!=enemyList.end();p++) {
        Actor *enemy=*p;
        enemy->draw();
    }
    for(PlayerList::iterator p=playerList.begin();p!=playerList.end();p++) {
        Player *player=*p;
        player->draw();
    }
}

void Game::handleAction(int id,bool down)
{
    if(playerList.size()>0) {
        Player *player=playerList.front();
        player->handleAction(id,down);
    }
}

void Game::setMode(int newMode)
{
    mode=newMode;
}

