#ifndef JOIN_H
#define JOIN_H

#include "player.h"

class Join
{
public:
    int active[6];

    Join();
    virtual ~Join();
    virtual void resetGame();
    virtual void draw();
    virtual void update(int elapsed);
    virtual void handleAction(int id, bool down);

private:
};

#endif // JOIN_H
