#include <QTimer>
#include <QKeyEvent>
#include "graphicsrenderer.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define NUM_OF_STARS 55 // name of stars on the background
#define STARS_SPEED 5

namespace si {

GraphicsRenderer::GraphicsRenderer(QWidget *parent) : QDialog(parent) {
    // define screen dimension
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;
    this->resize(screenWidth, screenHeight);

    // create background
    setStyleSheet("background-color: #000000;");
    m_stars = new star*[NUM_OF_STARS];
    for (int i = 0; i < NUM_OF_STARS; ++i){
        star * s = new star;
        s->x = screenWidth * Helpers::rand();
        s->y = screenHeight * Helpers::rand();
        m_stars[i] = s;
    }

    // run the main game logic engine and get spaceship / bullets array from it
    m_engine = new logicEngine(screenWidth, screenHeight);
    m_spaceship = m_engine->getSpaceShip();
    m_bullets = m_engine->getBulletsArray();

    // Connect QT timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(30);
}

GraphicsRenderer::~GraphicsRenderer() {
    // delete all stars
    for (int i = 0; i < NUM_OF_STARS; ++i){
        delete m_stars[i];
    }
    delete [] m_stars;
    delete m_engine;
}

void GraphicsRenderer::paintEvent(QPaintEvent *event) {
    QPainter m_mainPainter(this);

    // paint background
    m_mainPainter.setPen(Qt::white);
    m_mainPainter.setBrush(Qt::white);
    for (int i = 0; i < NUM_OF_STARS; ++i){
        int r = 2;
        m_mainPainter.drawEllipse(m_stars[i]->x, m_stars[i]->y, r, r);
    }

    // paint the spaceship
    m_spaceship->draw(&m_mainPainter);

    // paint all bullets within the array
    for (int i = 0; i < m_engine->m_maxNumBullets; ++i){
        // skip null pointer (ie. empty slot)
        if (m_bullets[i]){
            m_bullets[i]->draw(&m_mainPainter);
        }
    }

    // if debug option is enable, print all info
    if (m_engine->m_debug){
        m_engine->printInfo(&m_mainPainter);
    }
}

void GraphicsRenderer::keyPressEvent(QKeyEvent * event){
    // Key P is for pausing/un-pausing the movements
    if (event->key() == Qt::Key_P){
        // inverse it
        m_engine->m_paused = !m_engine->m_paused;
    }
    // Key C is for changing the color
    else if(event->key() == Qt::Key_C){
        m_engine->cycleColor();
    }
    // Key S is for changing the shape
    else if(event->key() == Qt::Key_S){
        m_engine->cycleShape();
    }
    // Key F1 is for showing debug info
    else if(event->key() == Qt::Key_F1){
        m_engine->m_debug = !m_engine->m_debug;
    }
}

void GraphicsRenderer::nextFrame() {
    // update game logics
    m_engine->update();
    updateBackground();

    // update graphics
    update();
}

void GraphicsRenderer::updateBackground(){
    // update the location of all starts
    for (int i = 0; i < NUM_OF_STARS; ++i){
        m_stars[i]->y += STARS_SPEED;
        if (m_stars[i]->y > SCREEN_HEIGHT){
            m_stars[i]->y = 0;
            // randomise the star x location to make to look more realistic
            m_stars[i]->x = SCREEN_WIDTH * Helpers::rand();
        }
    }
}
} // end namespace si
