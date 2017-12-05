/* Used to animate the space ship */

#ifndef ENERGYORB_H
#define ENERGYORB_H

#include <QPainter>
#include "helpers.h"

namespace si {
// A simple class for animating the spaceship
class energyOrb{
public:
    energyOrb(int x_sign, int y_sign, bool onTop);
    void setSize(int spaceShipWidth, int spaceShipHeight);
    void update(int origin_x, int origin_y);
    void draw(QPainter * p) const;
    // this boolean denotes if the orb should draw on top or behind the spaceship
    bool m_drawOnTop;
private:
    QPixmap m_orb;
    int m_origin_x; // where the orb is circling around at
    int m_origin_y; // where the orb is circling around at
    int m_x; // where the orb is based on the origin
    int m_y; // where the orb is based on the origin
    int m_x_sign; // which direction is the orb circling
    int m_y_sign; // which direction is the orb circling
    int m_flightWidth; // the width of the flight path
    const int deltaS = 4; // the speed of orb
    int m_spaceShipWidth;
    int m_spaceShipHeight;
};
}

#endif // ENERGYORB_H
