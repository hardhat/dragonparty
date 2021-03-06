#ifndef GAME_H
#define GAME_H

#include <deque>

#include "layer.h"
#include "tile.h"

enum GameMode {
    MODE_TITLE,
    MODE_CHOOSEAVATAR,
    MODE_LEVEL,
    MODE_GAMEOVER,
};

enum DPadKey {
    DPAD_LEFT,
    DPAD_UP,
    DPAD_RIGHT,
    DPAD_DOWN,
    DPAD_A,
    DPAD_B,
    DPAD_SELECT=10,
    DPAD_START,
};

class Player;
class Actor;
class Join;

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
    Join *join;
    int totalTime;

    Game();
    ~Game();

    void resetGame();
    void setMode(int newMode);
    void update(int elapsed);
    void draw();
    void handleAction(int which,int id,bool down);

    bool playersWin();
    bool enemiesActive();
    bool canMoveTo(Player *player,int tx,int ty);
    bool isObstacle(int tx,int ty);
    int canCollect(int tx,int ty);
    int collect(int tx,int ty);
    void spawnEnemies();
    Actor *targetEnemy(Player *player);
    Player *targetPlayer(Actor *enemy);
    bool enemyOnScreen();
};

extern Game game;

void D(const char *format,const char *param);
void D(const char *format,int param);
void D(const char *format,float param);

#endif
