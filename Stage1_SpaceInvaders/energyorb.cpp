#include "energyorb.h"

// a simple class for the animation of spaceship
namespace si {

energyOrb::energyOrb(int x_sign, int y_sign, bool onTop){
    // initialise member variables first
    // for the meaning of each variable, check the header file
    m_x_sign = x_sign;
    m_y_sign = y_sign;
    m_drawOnTop = onTop;
    m_x = 0;
    m_y = 0;
    m_spaceShipWidth = 0;
    m_spaceShipHeight = 0;
    m_flightWidth = 0;
    m_origin_x = 0;
    m_origin_y = 0;
    m_orb.load(":/resources/orb.png");
}
// set the size of the orb (based on the dimension of spaceship)
void energyOrb::setSize(int spaceShipWidth, int spaceShipHeight){
    m_orb = m_orb.scaledToWidth(spaceShipWidth * 0.3);
    m_spaceShipWidth = spaceShipWidth;
    m_spaceShipHeight = spaceShipHeight;
    m_flightWidth = spaceShipWidth/2;
}
// update the location of the orb
void energyOrb::update(int origin_x, int origin_y){
    // update the centre the orb
    m_origin_x = origin_x + m_spaceShipWidth/2 - m_orb.width()/2;
    m_origin_y = origin_y + m_spaceShipHeight/2 - m_orb.height()/2;

    // move the orb with a touch of random-ness
    // deltaS is the speed of spaceship, times by rand() to make the orb moving non-uniform-ly
    m_x += m_x_sign * deltaS * (Helpers::rand()/2 + 1);
    m_y += m_y_sign * deltaS * (Helpers::rand()/2 + 1);

    // after x has exceed the width of fligh path (completed half a lap), move it in the other direction
    if ((m_x > m_flightWidth) || (m_x < -m_flightWidth)){
        m_x_sign *= -1; // times by -1 to inverse it
        m_y_sign *= -1; // times by -1 to inverse it
        m_drawOnTop = !m_drawOnTop; // inverse the draw order to make it look like circling around the spaceship
    }
}
// draw the energy orb
void energyOrb::draw(QPainter * p) const{
    p->drawPixmap(m_origin_x + m_x, m_origin_y + m_y, m_orb);
}
}//endnamespace si
