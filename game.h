#ifndef GAME_H
#define GAME_H

#include <deque>

#include "layer.h"
#include "tile.h"

enum {
    MODE_TITLE,
    MODE_CHOOSEAVATAR,
    MODE_LEVEL,
    MODE_GAMEOVER,
};

class Player;
class Actor;

typedef std::deque<Player *> PlayerList;
typedef std::deque<Actor *> ActorList;
typedef std::deque<Layer *> LayerList;

class Game {
public:
    int mode;
    Tile *tile;
    Layer *bgLayer;
    Layer *fgLayer;
    Layer *characterLayer;
    Layer *hobgoblinLayer;
    PlayerList playerList;
    ActorList enemyList;

    Game();
    ~Game();

    void resetGame();
    void setMode(int newMode);
    void update(int elapsed);
    void draw();
    void handleAction(int id,bool down);
};

extern Game game;

#endif
