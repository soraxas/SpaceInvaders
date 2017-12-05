#include "rainbowbullet.h"
#include <QtMath>

RainbowBullet::RainbowBullet(int xSpeed, int ySpeed, int bx, int by, int windowWidth, int windowHeight,
                             std::string path, std::list<Bullet*> *bullets)
    : Bullet(ySpeed, bx, by, 10, path, bullets), frameWindow(0, 0, windowWidth, windowHeight),
      xSpeed(xSpeed), ySpeed(ySpeed)
{
    // rotate the image based on the speed
    QMatrix rm;
    rm.rotate(qRadiansToDegrees(qAtan(-(xSpeed + .0)/ySpeed)));
    this->bulletImage = bulletImage.transformed(rm);
}

//this will be <= for an enemy ship.
bool RainbowBullet::inFrame(int y){
    // all parts of image must be out of frame to consider it as outside
    int topLeftX  = bx - getImage().width()/2;
    int topLeftY  = by - getImage().height()/2;
    int botRightX = bx + getImage().width()/2;
    int botRightY = by + getImage().height()/2;
    return frameWindow.contains(topLeftX, topLeftY) || frameWindow.contains(botRightX, botRightY);
}
#include <iostream>
// in future we could have special bullets (which changes bx)
void RainbowBullet::nextFrame() {
    bx += xSpeed;
    by += ySpeed;
    if(!inFrame(by))
       deleteSelf();
}
