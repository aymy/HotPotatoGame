#ifndef __UMPIRE_H__
#define __UMPIRE_H__

#include "player.h"
#include "potato.h"

class Umpire {
  protected:
    int round;    // round number
    int potato_type;    //the potato type for this round
    Player** active_players;    // the active player list
  public:
    Umpire( Player::PlayerList &players );
    void start();
};

#endif
