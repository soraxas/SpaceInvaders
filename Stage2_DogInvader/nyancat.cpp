#include "nyancat.h"
#define NYANCAT_IMAGES_NUM 12
#include <iostream>

NyanCat::NyanCat(int startx, int starty, BulletFactory* bulletFactory, Ship* ship, std::string filename, int scaledToWidth)
    : Alien(startx, starty, bulletFactory, ship, filename, scaledToWidth)
{
    this->nyancatImageFrameDelay = 0;
    // randomise the initial frame number
    this->nyancatImageFrame = qrand() % NYANCAT_IMAGES_NUM;

    // load all nyan pointer to array
    nyancatImage = new QPixmap[NYANCAT_IMAGES_NUM];

    for (int i = 0; i < NYANCAT_IMAGES_NUM; ++i){
        path = ":/rsc/data/nyancat_" + QString::number(i) + ".png";
        nyancatImage[i].load(path);
        nyancatImage[i] = nyancatImage[i].scaledToWidth(scaledToWidth);
    }
}

NyanCat::~NyanCat(){
    delete [] nyancatImage;
}

QPixmap NyanCat::getImage() const{
    return nyancatImage[nyancatImageFrame];
}

void NyanCat::move(char m){
    switch(m){
    case('_'): // stay
        break;
    case('L'): ax = ax - 3;
        break;
    case('R'): ax = ax + 3;
        break;
    case('U'): ay = ay - 3;
        break;
    case('D'): ay = ay + 3;
        break;
    case('S'): //there is currently only one bullet type...
        shoot();
        break;
    }
}

void NyanCat::shoot(int xSpeed, int ySpeed){
    bulletFactory->makeBullet(xSpeed, ySpeed, ax - alienImage.width()/ 4, ay + alienImage.height()/2, 10, "RainbowBullet", false);
}

void NyanCat::nextFrame(){
    // switch the frame of nyancat
    if (++nyancatImageFrameDelay > 3){
        nyancatImageFrameDelay = 0;
        if (++nyancatImageFrame >= NYANCAT_IMAGES_NUM){
            nyancatImageFrame = 0;
        }
    }
}

