#ifndef __POTATO_H__
#define __POTATO_H__

#include <iostream> 
#include "PRNG.h"

class Potato {
  public:
    virtual void reset() = 0;        // must be defined in derived class
    virtual bool countdown() = 0;    // must be defined in  derived class
};

class Mashed : public Potato {
  protected:
    int maxticks;     // the max number of ticks
    int ticks;        // the number of ticks left
  public:
    Mashed( unsigned int maxTicks = 10 );
    void reset();
    bool countdown();
};
class Fried : public Potato {
  protected:
    int ticks;        // the number of ticks left
  public:
    Fried( unsigned int maxTicks = 10 );
    void reset();
    bool countdown();
};

#endif
