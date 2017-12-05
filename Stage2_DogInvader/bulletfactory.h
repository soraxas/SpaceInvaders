#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include "bullet.h"
#include "rainbowbullet.h"
#include "plainbullet.h"

#include <QSound>
#include <vector>

class BulletFactory
{
public:
    BulletFactory();
    virtual ~BulletFactory();
    void set(int windowHeight, int windowWidth);
    //Factory functions.
    void makeBullet(int speed, int x, int y, int damage, std::string type, bool isPlayer);
    void makeBullet(int xSpeed, int ySpeed, int x, int y, int damage, std::string type, bool isPlayer);

    std::list<Bullet*> bullets;
private:
    int windowHeight;
    int windowWidth;
    std::map<std::string, QSound*> bulletSound;


};

#endif // BULLETFACTORY_H
