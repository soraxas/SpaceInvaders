#include "explosion.h"
#include <QString>
#include <QSound>

#define ALIEN_EXPLOSION_IMAGES_NUM 7
#define SHIP_EXPLOSION_IMAGES_NUM 24

Explosion::Explosion(int x, int y, int scaledToWidth, ExplosionType type) : x(x), y(y)
{
    finished = false;
    this->explosionImage_frameDelay = 0;
    this->explosionImage_frame = 0;

    // load all image to array
    switch (type) {
    case(AlienExplosion):
        for (int i = 0; i < ALIEN_EXPLOSION_IMAGES_NUM; ++i){
            QPixmap img;
            QString path = ":/rsc/data/alienExplosion_" + QString::number(i) + ".png";
            img.load(path);
            img = img.scaledToWidth(static_cast<int>(scaledToWidth * 1.5));
            explosionImage.push_back(img);
        }
        break;
    case(ShipExplosion):
        for (int i = 0; i < SHIP_EXPLOSION_IMAGES_NUM; ++i){
            QPixmap img;
            QString path = ":/rsc/data/shipExplosion_" + QString::number(i) + ".png";
            img.load(path);
            img = img.scaledToWidth(static_cast<int>(scaledToWidth * 1.5));
            explosionImage.push_back(img);
        }
        break;
    }
}


void Explosion::draw(QPainter * painter){
    if(finished)
        return;
    painter->drawPixmap(x - explosionImage[0].width()/2, y - explosionImage[0].height()/2, explosionImage[explosionImage_frame]);
}

void Explosion::nextFrame(){
    if(finished)
        return;
    if (++explosionImage_frameDelay > 3){
        explosionImage_frameDelay = 0;
        if (++explosionImage_frame >= explosionImage.size()){
            finished = true;
        }
    }
}
