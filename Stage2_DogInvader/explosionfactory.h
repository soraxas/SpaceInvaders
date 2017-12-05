#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H

#include <QSound>
#include "explosion.h"
#include <vector>

class ExplosionFactory
{
public:
    ExplosionFactory();
    ~ExplosionFactory();
    Explosion createExplosion(int x, int y, int scaledToWidth, ExplosionType type);
private:
    std::map<ExplosionType, QSound*> sound;
};

#endif // EXPLOSIONFACTORY_H
