#include "alien.h"
#include <iostream>

Alien::Alien(int startx, int starty, BulletFactory *bulletFactory, Ship* ship, std::string filename, int scaledToWidth)
    :  ax(startx), ay(starty), ship(ship), dead(false)
{
    path = ":/rsc/data/" + QString::fromStdString(filename);
    alienImage.load(path);
    alienImage = alienImage.scaledToWidth(scaledToWidth);
    this->bulletFactory = bulletFactory;
}

Alien::~Alien(){}

/**************** GETTERS *************************/
int Alien::getX() const {
    return ax;
}

int Alien::getY() const {
    return ay;
}

int Alien::getWidth() const{
    return getImage().width();
}
int Alien::getHeight() const{
    return getImage().height();
}

QPixmap Alien::getImage() const {
    return alienImage;
}

void Alien::draw(QPainter *p) const{
    if(this->dead)
        return;
    p->drawPixmap(getX() - getWidth()/2, getY() - getHeight()/2, getImage());
}

bool Alien::isComposite() const{
    return false;
}

void Alien::setShipPtr(Ship* ship){
    this->ship = ship;
}

void Alien::setDead(){
    this->dead = true;
}
bool Alien::isDead(){
    return dead;
}

bool Alien::beenShotAt(int b_x1, int b_y1, int b_x2, int b_y2, std::vector<Explosion> &explosions, ExplosionFactory &factory){
    if(isDead())
        return false;
    int alien_x1 = getX() - getImage().width()/2;
    int alien_y1 = getY() - getImage().height()/2;
    int alien_x2 = getX() + getImage().width()/2;
    int alien_y2 = getY() + getImage().height()/2;

    // Check if two rectagle is overlaping
    if (b_x1 < alien_x2 && b_x2 > alien_x1
            && b_y1 < alien_y2 && b_y2 > alien_y1){
        // set this alien as dead
        this->setDead();
        // create explosion at this location
        explosions.push_back(factory.createExplosion(getX(), getY(), static_cast<int>(getWidth() * 1.7), AlienExplosion));
        return true;
    }
    return false;
}

