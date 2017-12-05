#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <QFile>
#include "director.h"
#include "bulletbuilderdefault.h"
#include "spaceshipbuilderdefault.h"
#include "config.h"

// This is the main engine that is incharge for every actions (eg reading config file, movement)
namespace si {
class logicEngine{
public:
    logicEngine(int screenWidth, int screenHeight);
    virtual ~logicEngine();

    SpaceShip * getSpaceShip();
    bullet ** getBulletsArray();
    void fireBullet();
    void update();
    void cycleColor();
    void cycleShape();
    int m_maxNumBullets; // max number that the screen could have
    bool m_paused; // denote is the game pausing
    bool m_debug;
    void printInfo(QPainter * p); // print debug information on screen
private:
    void saveConfig();
    void loadConfig();
    void updateSpaceShip();
    void updateBullets();

    si::SpaceShip * m_spaceship;
    si::bullet ** m_bullets;
    si::Director m_director;

    int m_screenWidth;
    int m_screenHeight;
    int m_actionFrameCounter; // the frame number for each action
    int m_curAction; // current action number (given in the config file)
    config * m_config;
};
}

#endif // LOGICENGINE_H
