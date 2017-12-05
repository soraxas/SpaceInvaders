#include "aliendecorator.h"

AlienDecorator::AlienDecorator(Alien& decorator) : Alien(decorator), decorator(decorator){}
AlienDecorator::~AlienDecorator(){
    delete &decorator;
}
/**************** GETTERS *************************/
QPixmap AlienDecorator::getImage() const {
    return decorator.getImage();
}

void AlienDecorator::move(char m){
    decorator.move(m);
}

void AlienDecorator::shoot(int xSpeed, int ySpeed){
    decorator.shoot(xSpeed, ySpeed);
}

void AlienDecorator::nextFrame(){
    decorator.nextFrame();
}

void AlienDecorator::draw(QPainter *p) const{
    decorator.draw(p);
}

void AlienDecorator::setShipPtr(Ship* ship){
    decorator.setShipPtr(ship);
}

/**************** GETTERS *************************/
int AlienDecorator::getX() const {
    return decorator.getX();
}

int AlienDecorator::getY() const {
    return decorator.getY();
}

int AlienDecorator::getWidth() const{
    return decorator.getWidth();
}
int AlienDecorator::getHeight() const{
    return decorator.getHeight();
}

bool AlienDecorator::isComposite() const{
    return decorator.isComposite();
}

void AlienDecorator::setDead(){
    decorator.setDead();
}
bool AlienDecorator::isDead(){
    return decorator.isDead();
}

bool AlienDecorator::beenShotAt(int b_x1, int b_y1, int b_x2, int b_y2, std::vector<Explosion> &explosions, ExplosionFactory &factory){
        if(decorator.isDead())
            return false;
        int alien_x1 = decorator.getX() - decorator.getImage().width()/2;
        int alien_y1 = decorator.getY() - decorator.getImage().height()/2;
        int alien_x2 = decorator.getX() + decorator.getImage().width()/2;
        int alien_y2 = decorator.getY() + decorator.getImage().height()/2;

        // Check if two rectagle is overlaping
        if (b_x1 < alien_x2 && b_x2 > alien_x1
                && b_y1 < alien_y2 && b_y2 > alien_y1){
            // set this alien as dead
            decorator.setDead();
            // create explosion at this location
            explosions.push_back(factory.createExplosion(decorator.getX(), decorator.getY(), static_cast<int>(decorator.getWidth() * 1.7), AlienExplosion));
            return true;
        }
        return false;
}
