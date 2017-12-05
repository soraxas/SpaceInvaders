/* incahrge of building everything (eg. spaceship, laser etc. for now) */

#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "spaceship.h"
#include "spaceshipbuilder.h"
#include "bullet.h"
#include "bulletbuilder.h"

namespace si{

class Director
{
public:
    Director();
    virtual ~Director();
    void setSpaceShipBuilder(si::SpaceShipBuilder * builder);
    void setBulletBuilder(si::BulletBuilder * builder);
    SpaceShip * buildSpaceShip();
    bullet * buildBullet();
    bullet ** buildBulletsArray(int num);

private:
    si::SpaceShipBuilder * m_spaceShipBuilder;
    si::BulletBuilder * m_bulletBuilder;
    bullet ** m_bulletsArray;
    SpaceShip * m_spaceship;
    int m_bulletsArraySize;
    void deleteBulletsArray();
};

} //end namespace si

#endif // DIRECTOR_H
