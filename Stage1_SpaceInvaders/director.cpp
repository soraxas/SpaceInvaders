#include "director.h"

#define SPACESHIP_START_Y 350 // default y location


namespace si{

Director::Director(){
    // first set all to null pointer (so we know if we need to free stuff)
    m_bulletsArray = nullptr;
    m_spaceship = nullptr;
    m_spaceShipBuilder = nullptr;
    m_bulletBuilder = nullptr;
}
Director::~Director(){
    if (m_spaceship){ // if pointer is not null
        delete m_spaceship;
    }
    if (m_spaceShipBuilder){
        delete m_spaceShipBuilder;
    }
    if (m_bulletBuilder){
        delete m_bulletBuilder;
    }
    this->deleteBulletsArray(); // delete all bullets within array
}

void Director::setSpaceShipBuilder(si::SpaceShipBuilder * builder){
    // if there is existing builder, delete it first
    if (m_spaceShipBuilder){
        delete m_spaceShipBuilder;
    }
    m_spaceShipBuilder = builder;
}

void Director::setBulletBuilder(si::BulletBuilder * builder){
    // if there is existing builder, delete it first
    if (m_bulletBuilder){
        delete m_bulletBuilder;
    }
    m_bulletBuilder = builder;
}

SpaceShip* Director::buildSpaceShip(){
    // if we already created a spaceship before, use the existing memory address
    if (!m_spaceship){
        m_spaceship = new SpaceShip();
    }
    m_spaceship->setPixmap(m_spaceShipBuilder->getDefenderPixmap());
    m_spaceship->setSize(m_spaceShipBuilder->getDefenderSize());
    m_spaceship->setColor(m_spaceShipBuilder->getDefenderColor());
    m_spaceship->setX(m_spaceShipBuilder->getDefenderStartX());
    m_spaceship->setY(SPACESHIP_START_Y);
    return m_spaceship;
}

bullet ** Director::buildBulletsArray(int num){
    // if already created one array before, delete the existing one and return a new one
    if (m_bulletsArray){
        this->deleteBulletsArray();
    }
    m_bulletsArray = new bullet*[num];
    // initialise all bullet ptr to nullptr
    for (int i = 0; i < num; ++i){
        m_bulletsArray[i] = nullptr;
    }
    m_bulletsArraySize = num;
    return m_bulletsArray;
}

bullet * Director::buildBullet(){
    // return a new bullet based on the given builder
    bullet * b = new bullet();
    b->setPixmap(m_bulletBuilder->getBulletPixmap());
    b->setSound(m_bulletBuilder->getBulletSound());
    b->setSpeed(m_bulletBuilder->getBulletSpeed());
    return b;
}

void Director::deleteBulletsArray(){
    // free all bullets pointer within the array
    if (m_bulletsArray){
        for (int i = 0; i < m_bulletsArraySize; ++i){
            if (m_bulletsArray[i]){
                delete m_bulletsArray[i];
            }
        }
        delete [] m_bulletsArray;
    }
    m_bulletsArray = nullptr;
}
} //end namespace si
