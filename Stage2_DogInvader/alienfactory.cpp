#include "alienfactory.h"
#include "nyancat.h"
#include "aliendecorator.h"
#include "alienhunting.h"
#include "alienred.h"

#define ALIEN_WIDTH 40

AlienFactory::AlienFactory(){}

AlienFactory::~AlienFactory(){}

void AlienFactory::set(BulletFactory *bulletFactory, Ship* ship, int windowHeight, int windowWidth) {
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    this->bulletFactory = bulletFactory;
    this->ship = ship;
}

Alien* AlienFactory::createAlien(int startx, int starty, AlienType type) {
    //some input parameter will decide what to build
    Alien *result = NULL;

    std::string filename = "nyancat_0.png";

    switch(type){
    case(Normal):
        result = new NyanCat(startx, starty, bulletFactory, ship, filename, ALIEN_WIDTH);
        break;
    case(Hunting):
        result = new NyanCat(startx, starty, bulletFactory, ship, filename, ALIEN_WIDTH);
        break;
    }

//    return new AlienRed(* new AlienHunting(*result));
//    return new AlienRed(*new AlienHunting(*result));
    return result;
}
