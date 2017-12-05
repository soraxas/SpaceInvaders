#include "explosionfactory.h"
#include "explosion.h"

#define ALIEN_EXPLOSION_IMAGES_NUM 7
#define SHIP_EXPLOSION_IMAGES_NUM 24

ExplosionFactory::ExplosionFactory()
{
    sound[AlienExplosion] = new QSound(":/rsc/data/alienExplosion.wav");
    sound[ShipExplosion] = new QSound(":/rsc/data/shipExplosion.wav");
}

ExplosionFactory::~ExplosionFactory(){
    for(auto&& s : sound)
        delete s.second;
}

Explosion ExplosionFactory::createExplosion(int x, int y, int scaledToWidth, ExplosionType type){
    sound[type]->play();
    return Explosion(x, y, scaledToWidth, type);
}

