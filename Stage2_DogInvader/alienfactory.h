#ifndef ALIENFACTORY_H
#define ALIENFACTORY_H

#include "alien.h"
#include <string>

enum AlienType{Normal, Hunting}; // defining the type of alien

class AlienFactory
{
public:
    AlienFactory();
    virtual ~AlienFactory();
    void set(BulletFactory *bulletFactory, Ship* ship, int windowHeight, int windowWidth);
    Alien* createAlien(int startx, int starty, AlienType type);

private:
    int windowHeight;
    int windowWidth;
    BulletFactory *bulletFactory;
    Ship* ship;
};



#endif // ALIENFACTORY_H
