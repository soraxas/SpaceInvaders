#include "alienhunting.h"
#include "aliendecorator.h"
#include <iostream>
#include <QtMath>

AlienHunting::AlienHunting(Alien& decorator) : AlienDecorator (decorator){
    resetCounter();
}

void AlienHunting::resetCounter(){
    shootCounter = 0;
    // now randomly shoot at frame 50 - 150
    shootAt = qrand() % 50;
    shootAt += 100;

    // now randomly re-position
    int leftMaxDelta = -200;
    int rightMaxDelta = -leftMaxDelta;
    delteX = leftMaxDelta + (qrand() % ((rightMaxDelta - leftMaxDelta) + 1));
}

void AlienHunting::move(char){
    if(decorator.isDead())
        return;
    if(decorator.ship->isDead)
        return;

    if(++shootCounter > shootAt){
        resetCounter();
        // calculate the angle to shoot
        int ySpeed = 10;
        int xSpeed = static_cast<int>((decorator.ax - decorator.ship->getX() + 0.) /
                                      (decorator.ay - decorator.ship->getY() + 0.) *
                                      ySpeed);
        decorator.shoot(xSpeed, ySpeed);
        return;
    }
    // track the ship
    if(decorator.ship->getX() + delteX < decorator.getX()){
        decorator.ax -= (qrand() % 3) + 2;
    }else{
        decorator.ax += (qrand() % 3) + 2;
    }
    return;
}

QPixmap AlienHunting::getImage() const{
    // rotate the image
    double deltaX = (decorator.ay - decorator.ship->getY());
    double deltaY = (decorator.ax - decorator.ship->getX());
    QMatrix rm;
    rm.rotate(qRadiansToDegrees(qAtan(-(deltaY)/deltaX)));
    return decorator.getImage().transformed(rm);
}
