#include "bulletfactory.h"

BulletFactory::BulletFactory() {
    bulletSound["PlainBullet"] = new QSound(":/rsc/data/PlainBullet.wav");
    bulletSound["RainbowBullet"] = new QSound(":/rsc/data/RainbowBullet.wav");
}

BulletFactory::~BulletFactory(){
    // free bullets pointer
    for(auto&& b : bullets)
        delete b;
    // free sound file
    for(auto&& bs : bulletSound)
        delete bs.second;
}

void BulletFactory::set(int windowHeight, int windowWidth) {
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;

}

void BulletFactory::makeBullet(int speed, int x, int y, int damage,std::string bType, bool isPlayer){
  makeBullet(0, speed, x, y, damage, bType, isPlayer);
}

//change the method signature once 1) there are different bullet types
void BulletFactory::makeBullet(int xSpeed, int ySpeed, int x, int y, int damage,std::string bType, bool isPlayer)
{
    //If it is a player bullet, change speed to -ve
    if (isPlayer) {
        ySpeed = (-1) * ySpeed;
    }
//int speed = xSpeed;
//int damage = 19;
    if (bType == "PlainBullet") {
        // Bullet *result = new PlainBullet(ySpeed, x, y, this->windowWidth, this->windowHeight);
        Bullet *result = new PlainBullet(ySpeed, x, y, damage, bType, &bullets);
        result->type = bType;
        bullets.push_back(result);
    } else if(bType == "RainbowBullet"){
        Bullet *result = new RainbowBullet(xSpeed, ySpeed, x, y, this->windowWidth, this->windowHeight, bType, &bullets);
        result->type = bType;
        bullets.push_back(result);
    }
    // play sound when making a bullet
    bulletSound[bType]->play();
}
