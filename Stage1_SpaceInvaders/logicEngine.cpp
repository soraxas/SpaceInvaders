#include <QSound>
#include <QString>
#include "logicEngine.h"
#include "helpers.h"

#define MAX_NUM_BULLETS 30 // max number of bullets on screen at a given time
#define ACTION_DURATION 30 // the duration/num of frams for each actions
#define SPACESHIP_SPEED 3 // the speed of spaceship


namespace si {

logicEngine::logicEngine(int screenWidth, int screenHeight){
    m_screenHeight = screenHeight;
    m_screenWidth = screenWidth;

    // load config file
    loadConfig();

    // we use the DEFAULT SETTINGS which is load directly from config file.
    m_director.setSpaceShipBuilder(new SpaceShipBuilderDefault(m_config));
    m_director.setBulletBuilder(new BulletBuilderDefault);

    // build spaceship
    m_spaceship = m_director.buildSpaceShip();
    // set the y coordinate with the consideration of height of pixmap
    m_spaceship->setY(m_screenHeight - m_spaceship->getHeight());

    // set defined maximum number of bullets allowed at once ON SCREEN
    m_maxNumBullets = MAX_NUM_BULLETS;

    // build array for the bullets
    m_bullets = m_director.buildBulletsArray(MAX_NUM_BULLETS);

    // counter for the duration of each action
    m_actionFrameCounter = 0;
    m_curAction = 0;

    // default value for option
    m_paused = false;
    m_debug = false;
}

logicEngine::~logicEngine(){
    delete m_config;
}
// cycle throguh color
void logicEngine::cycleColor(){
    // we use the fact that underlying enum is integer to cycle through it
    m_config->m_color = color(m_config->m_color + 1);
    if (m_config->m_color == END_OF_COLOR){ // reached the end of enum
        m_config->m_color = color(0); // go back to first item
    }
    // save the current location of spaceship
    int curX = m_spaceship->getX();
    int curY = m_spaceship->getY();

    // build a new spaceship and save config
    m_director.setSpaceShipBuilder(new SpaceShipBuilderDefault(m_config));
    m_spaceship = m_director.buildSpaceShip();
    m_spaceship->setX(curX);
    m_spaceship->setY(curY);

    saveConfig();
}

void logicEngine::cycleShape(){
    // we use the fact that underlying enum is integer to cycle through it

    m_config->m_shape = spaceShipShape(m_config->m_shape + 1);
    if (m_config->m_shape == END_OF_SPACESHIPSHAPE){ // reached the end of enum
        m_config->m_shape = spaceShipShape(0); // go back to first item
    }
    // save the current location of spaceship
    int curX = m_spaceship->getX();
    int curY = m_spaceship->getY();

    // build a new spaceship and save config
    m_director.setSpaceShipBuilder(new SpaceShipBuilderDefault(m_config));
    m_spaceship = m_director.buildSpaceShip();
    m_spaceship->setX(curX);
    m_spaceship->setY(curY);

    saveConfig();
}

SpaceShip * logicEngine::getSpaceShip(){
    return m_spaceship;
}

bullet ** logicEngine::getBulletsArray(){
    return m_bullets;
}

void logicEngine::fireBullet(){
    // find an empty spot within the bullet array and add it
    for (int i = 0; i < m_maxNumBullets; ++i){
        // skip for non-null pointer (ie. empty slot)
        if (m_bullets[i] != nullptr){
            continue;
        }
        // create a new bullet
        bullet * b = m_director.buildBullet();

        // calculate the location of the bullet
        int bx = m_spaceship->getX() + (m_spaceship->getWidth()/2) - (b->getWidth()/2);
        int by = m_spaceship->getY() - b->getHeight();
        // set the location
        b->setX(bx);
        b->setY(by);

        // assign the bullet to the slot
        m_bullets[i] = b;

        // play the sound of shooting
        b->playSound();
        break;
    }
}
// update location of spaceship & bullets
void logicEngine::update(){
    this->updateSpaceShip();
    this->updateBullets();

}

void logicEngine::updateSpaceShip(){
    // if paused, or all action had been performed, do nothing
    if (m_paused || m_curAction + 1 > m_config->m_numMovements){
        return;
    }
    // check if we need to move to next action
    if (m_actionFrameCounter == 0){
        // we only shoot on the first frame of an action (as oppose to move left or right)
        if (m_config->m_movements[m_curAction] == SHOOT){
            fireBullet();
        }
    }
    // check if reached the duration of an action, go to the next action
    if (++m_actionFrameCounter > ACTION_DURATION){
        m_actionFrameCounter = 0;
        ++m_curAction; // next action
    }
    // get current spaceship location and the max-X that it could move to
    int spaceShipX = m_spaceship->getX();
    int maxX = m_screenWidth - m_spaceship->getWidth();
    // switch to the given action
    switch(m_config->m_movements[m_curAction]){
    case(LEFT):
        spaceShipX -= SPACESHIP_SPEED;
        // if out of screen, force it to zero (ie cannot move)
        if (spaceShipX < 0){
            spaceShipX = 0;
        }
        break;
    case(RIGHT):
        spaceShipX += SPACESHIP_SPEED;
        // if out of screen, force it to maximum X(ie cannot move)
        if (spaceShipX > maxX){
            spaceShipX = maxX;
        }
        break;
    case(SHOOT):
        // stand still if shooting
        break;
    }
    m_spaceship->setX(spaceShipX);
}

void logicEngine::updateBullets(){
    // update all bullets within the array
    for (int i = 0; i < m_maxNumBullets; ++i){
        // skip null pointer (ie. empty slot)
        if (m_bullets[i] == nullptr){
            continue;
        }
        // check if the bullet y is already out of the screen. If so, remove it.
        else if (m_bullets[i]->getY() < -100){
            delete m_bullets[i];
            m_bullets[i] = nullptr;
            continue;
        }
        // update the y location of all bullets
        m_bullets[i]->update();
    }
}
// loca the config file
void logicEngine::loadConfig(){
    QFile file("./config.ini"); // config file location
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Error in reading config");
        throw;
    }
    m_config = new config(& file);
    // check the validity of startX
    if (m_config->m_startX < 0 || m_config->m_startX > m_screenWidth){
        qDebug("ERROR: 'StartX' is not within the screen width");
        throw;
    }
}
// save config to file
void logicEngine::saveConfig(){
    QFile file ("./config.ini");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
        qDebug("ERROR in saving config");
        throw;
    }
    QTextStream out (&file);

    // ===== save all configs to file =====
    out << "size=";
    out << Helpers::enumToString(m_config->m_size);
    out << "\r\n"; // line break

    out << "spaceShipType=";
    out << Helpers::enumToString(m_config->m_shape);
    out << "\r\n"; // line break

    out << "startX=" << QString::number(m_config->m_startX);
    out << "\r\n"; // line break

    out << "color=";
    out << Helpers::enumToString(m_config->m_color);
    out << "\r\n"; // line break

    out << "movement=\n";
    for (int i = 0; i < m_config->m_numMovements; ++i){
        out << Helpers::enumToString(m_config->m_movements[i]);
        out << "\r\n";
    }
}

// print all useful information if debug option is enabled
void logicEngine::printInfo(QPainter *p){
    if (!m_debug){
        return;
    }
    p->setPen(Qt::yellow);
    int line_height = 18;
    QString str;

    // print keyboard hint
    p->drawText(5, line_height, "[F1] Toggle info | [S] Change shape | [C] Change color | [P] Pause/Resume");

    // print spaceship x, y
    str = "Spaceship X:";
    str += QString::number(m_spaceship->getX());
    str += " Y:";
    str += QString::number(m_spaceship->getY());
    p->drawText(20, line_height * 2, str);

    // print current size
    str = "Spaceship Size: ";
    str += Helpers::enumToString(m_config->m_size);
    p->drawText(20, line_height * 3, str);

    // print current color
    str = "Spaceship Color: ";
    str += Helpers::enumToString(m_config->m_color);
    p->drawText(20, line_height * 4, str);

    // print current shape
    str = "Spaceship Shape: ";
    str += Helpers::enumToString(m_config->m_shape);
    p->drawText(20, line_height * 5, str);

    str = "Current action: ";
    if (m_paused)
        str += "--PAUSED--";
    else if (m_curAction < m_config->m_numMovements)
        str += Helpers::enumToString(m_config->m_movements[m_curAction]);
    else
        str += "--FINISHED--";
    p->drawText(20, line_height * 6, str);
}

}//end namespace si

