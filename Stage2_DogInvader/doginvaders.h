#ifndef DOGINVADERS_H
#define DOGINVADERS_H

#include "bulletfactory.h"
#include "colorbutton.h"
#include "configreader.h"
#include "shipfactory.h"
#include "sizebutton.h"
#include "explosionfactory.h"
#include "alienfactory.h"
#include "swarmcomponent.h"
#include "explosion.h"
#include "background.h"

#include <QDialog>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <vector>
#include <string>
#include <QLCDNumber>

//MAGIC NUMBERS
const int HEIGHT = 600;
const int WIDTH = 800;

namespace Ui {
  class DogInvaders;
}

class DogInvaders : public QDialog
{
    Q_OBJECT

public:
    explicit DogInvaders(QString fileName, QString filePath, QWidget *parent = 0);
    ~DogInvaders();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void nextFrame();
    void pause();

    void displayColorOptions();

    //in future maybe just use a setColor(color) func

    void setRed();
    void setOrange();
    void setYellow();
    void setGreen();
    void setBlue();

    void setTiny();
    void setNormal();
    void setLarge();
    void setGiant();
    void keyPressEvent(QKeyEvent * event);

private:
    void resetGame();
    void loadTimer();
    void loadButtons();
    
    void updateMovements();
    void setColor(std::string color);
    void setSizeShip(std::string size);
    /**************** HELPER *************************/
    bool nextMovement();
    void resetIterator();
    void stopItems();
    void startItems();
    bool bulletWithinImage(int bx, int by, int bWidth, int bHeight, int imageX, int imageY, int imageWidth, int imageHeight);
    bool checkBulletHitAlien(std::list<Bullet*>::iterator &bIt) ;
    bool checkBulletHitShip(std::list<Bullet*>::iterator &bIt);
    /**************** VARIABLES *************************/
    Ui::DogInvaders *ui;

    Ship* player;
    BulletFactory bulletFactory;
    ShipFactory shipFactory;
    AlienFactory alienFactory;
    ExplosionFactory explosionFactory;
    ConfigReader reader;
    QPushButton *button;
    bool paused;

    ColorButton *color;
    SizeButton *sizes;
    std::vector<std::tuple<SwarmComponent*, std::string, unsigned>> aliens;
    std::vector<Explosion> explosions;
    Background bg;
    QMediaPlaylist bgMusicPlaylist;
    QMediaPlayer bgMusicPlayer;
    QLCDNumber* gameScoreWidget;
    std::string fileName;
    std::string filePath;
    int counter;
    int maxCounter = 25; //magic number.
    long gameScore;
};

#endif // DOGINVADERS_H
