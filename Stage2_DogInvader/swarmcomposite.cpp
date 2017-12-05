#include "swarmcomposite.h"
#include "alien.h"

#include <iostream>

SwarmComposite::SwarmComposite(){}

SwarmComposite::~SwarmComposite(){
    for(SwarmComponent * c : aliens) {
        delete c;
    }
}

void SwarmComposite::add(SwarmComponent *c){
    aliens.push_back(c);
}

void SwarmComposite::move(char m){
    for(SwarmComponent* a: aliens ){
        bool isBehind = false;
        if(m == 'S'){
            // if move is shoot, only the first row shoot.
            for(SwarmComponent* b: aliens){
                // if we encounter any aline in front of us, we dont shoot
                if((dynamic_cast<Alien*>(a)->getY() < dynamic_cast<Alien*>(b)->getY()) &&
                        (dynamic_cast<Alien*>(a)->getX() == dynamic_cast<Alien*>(b)->getX()) )
                    isBehind = true;
            }
        }
        if (!isBehind)
            a->move(m);
    }
}

void SwarmComposite::nextFrame(){
    // switch the frame of nyancat
    for(SwarmComponent* a: aliens ){
        a->nextFrame();
    }
}

void SwarmComposite::draw(QPainter *p) const{
    for(SwarmComponent* a: aliens ){
        a->draw(p);
    }
}

int SwarmComposite::getWidth() const {
    if(aliens.size() < 1){
        // not yet available
        return -1;
    }
    return aliens.back()->getWidth();
}

int SwarmComposite::getHeight() const {
    if(aliens.size() < 1){
        // not yet available
        return -1;
    }
    return aliens.back()->getHeight();
}

bool SwarmComposite::isComposite() const{
    return true;
}

void SwarmComposite::setShipPtr(Ship* ship){
    for(SwarmComponent* a: aliens ){
        a->setShipPtr(ship);
    }
}

bool SwarmComposite::beenShotAt(int topLeftX, int topLeftY, int botRightX, int botRightY, std::vector<Explosion> &explosions, ExplosionFactory &factory){
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i]->beenShotAt(topLeftX, topLeftY, botRightX, botRightY, explosions, factory)){
            // remove alien since it's dead
            delete aliens[i];
            aliens.erase(aliens.begin() + i);
            return true;
        }
    }
    return false;
}
