#ifndef JOIN_H
#define JOIN_H

#include "player.h"

class Join
{
public:
    bool playerJoin[6];
    bool playerDone[6];

    Tile *tile;

    Join(Tile *tile);
    virtual ~Join();
    virtual void resetGame();
    virtual void draw();
    virtual void update(int elapsed);
    virtual void handleAction(int which,int id, bool down);

private:
};

#endif // JOIN_H
