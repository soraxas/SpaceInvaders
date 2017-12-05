#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include "logicEngine.h"
#include "spaceship.h"
#include "bullet.h"
#include "energyorb.h"

namespace si {

struct star{ // for the stars at the background
    int x, y;
};
class GraphicsRenderer : public QDialog
{
    Q_OBJECT
    int timer = 0;
public:
    GraphicsRenderer(QWidget *parent = nullptr);
    virtual ~GraphicsRenderer();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void nextFrame();
private:
    si::logicEngine * m_engine;
    si::SpaceShip * m_spaceship;
    si::bullet ** m_bullets;
    si::star ** m_stars;

    QPainter m_mainPainter;
    QPainter m_starPainter;

    void updateBackground();
};

} // end namespace si

#endif // GRAPHICSRENDERER_H
