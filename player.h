#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "potato.h"
#include "PRNG.h"


class Player {
  protected:
    Player** active;    // active player list
    unsigned int playerid;    // current player id
  public:
    typedef Player** PlayerList; // container type of your choice
    Player( unsigned int id, Player::PlayerList &players );
    virtual unsigned int getId();
    virtual unsigned int toss( Potato &potato ) = 0; // must be defined in derived class
};

class RNPlayer : public Player {
  public:
    RNPlayer( unsigned int id, Player::PlayerList &players );
    unsigned int toss( Potato &potato );
};

class LRPlayer : public Player {
  protected:
    int times_called;    // the number of times this player catch the potato so far
  public:
    LRPlayer( unsigned int id, Player::PlayerList &players );
    unsigned int toss( Potato &potato );
};

#endif
