#include "bulletbuilderdefault.h"

namespace si {

BulletBuilderDefault::BulletBuilderDefault(){
    // load the default laser pixmap and sound
    m_bulletSound = new QSound(":/resources/laser_sound.wav");
    m_bulletPixmap = new QPixmap();
    m_bulletPixmap->load(":/resources/laser.png");
}

BulletBuilderDefault::~BulletBuilderDefault(){
    delete m_bulletPixmap;
    delete m_bulletSound;
}

QPixmap * BulletBuilderDefault::getBulletPixmap() const{
    return m_bulletPixmap;
}

QSound * BulletBuilderDefault::getBulletSound() const{
    return m_bulletSound;
}

int BulletBuilderDefault::getBulletSpeed() const{
    return 10; // default speed
}

}//end namespace si
