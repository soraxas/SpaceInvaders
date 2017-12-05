#include "bullet.h"

namespace si {

bullet::bullet(){}
bullet::~bullet(){}

void bullet::setPixmap(QPixmap * pixmap){
    m_bulletPixmap = pixmap;
}

void bullet::setSound(QSound * sound){
    m_bulletSound = sound;
}

void bullet::setSpeed(int speed){
    m_speed = speed;
}

void bullet::draw(QPainter* p){
    p->drawPixmap(m_x, m_y, *m_bulletPixmap);
}

void bullet::playSound(){
    m_bulletSound->play();
}

void bullet::update(){
    m_y -= m_speed;
}

int bullet::getX(){
    return m_x;
}
int bullet::getY(){
    return m_y;
}
void bullet::setX(int x){
    m_x = x;
}
void bullet::setY(int y){
    m_y = y;
}

int bullet::getWidth(){
    return m_bulletPixmap->width();
}

int bullet::getHeight(){
    return m_bulletPixmap->height();
}


}// end namespace si


