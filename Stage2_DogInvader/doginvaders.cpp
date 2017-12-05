#include "doginvaders.h"
#include "ui_doginvaders.h"
#include "alienred.h"
#include "alienhunting.h"
#include "background.h"
#include <QKeyEvent>


#define SCORE_PER_ALIEN 150
//#define DEBUG

#include <iostream>

DogInvaders::DogInvaders(QString fileName, QString filePath, QWidget *parent) :
    QDialog(parent), ui(new Ui::DogInvaders), player(NULL), bg(WIDTH, HEIGHT), fileName(fileName.toStdString()),
    filePath(filePath.toStdString()), paused(false), counter(0), gameScore(0)
{
    ui->setupUi(this);
    this->resize(WIDTH, HEIGHT);
    
    // init score board
    gameScoreWidget = new QLCDNumber(this);
    gameScoreWidget->setGeometry(0, 0, WIDTH, 80); // location at top right
    gameScoreWidget->setPalette(Qt::red); // red outline
    gameScoreWidget->setSegmentStyle(QLCDNumber::Filled);
    gameScoreWidget->setStyleSheet("color:yellow;background:transparent"); // transparent background
    gameScoreWidget->setAttribute(Qt::WA_TranslucentBackground);
    gameScoreWidget->setWindowFlags(Qt::FramelessWindowHint);
    gameScoreWidget->setDigitCount(20);
    
    // build factory
    alienFactory.set(&bulletFactory, player, HEIGHT, WIDTH);
    bulletFactory.set(HEIGHT, WIDTH);
    shipFactory.set(&bulletFactory, HEIGHT, WIDTH);
    
    // background
    setStyleSheet("background-color: #000000;");
    loadTimer();
    loadButtons();
    
    // background music
    bgMusicPlaylist.addMedia(QUrl("qrc:/rsc/data/BackgroundMusic.mp3"));
    bgMusicPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
    
    resetGame();
}

DogInvaders::~DogInvaders() {
    delete button;
    delete color;
    delete sizes;
    delete ui;
    delete player;
    delete gameScoreWidget;
    // remove all remaining aliens
    for(std::tuple<SwarmComponent*, std::string, unsigned> pair : aliens) {
        delete std::get<0>(pair);
    }
    aliens.clear();
}

/**********************************************************************/
/******************** GAME FUNCTIONALITY ******************************/
/**********************************************************************/
void DogInvaders::resetGame(){
    // bg music player
    bgMusicPlayer.setPlaylist(&bgMusicPlaylist);
    bgMusicPlayer.play();
    bgMusicPlayer.setVolume(35);
    // remove all remaining aliens
    for(std::tuple<SwarmComponent*, std::string, unsigned> pair : aliens) {
        delete std::get<0>(pair);
    }
    // remove all remaining bullets
    aliens.clear();
    if(player) // delete player if exists
        delete player;
    
    //Load the file information
    reader.setup(QString::fromStdString(fileName), QString::fromStdString(filePath), aliens, alienFactory);
    player = shipFactory.createShip(reader.getSize(), reader.getColor(), reader.getCoord(), reader.getMove());
    
    // set the ship pointer for every aliens
    for(std::tuple<SwarmComponent*, std::string, unsigned> &a : aliens){
        std::get<0>(a)->setShipPtr(player);
    }
    this->gameScore = 0;
    player->start();
}
void DogInvaders::pause() { //get all the items and pause their timers
    //if currently not paused, the stop the game
    if (!paused) {
        stopItems();
    } else {
        startItems();
    }
    //show the color menu
    color->displayMenu(paused);
    sizes->displayMenu(paused);
}
void DogInvaders::stopItems() {
    player->stop();
    for(auto&& b : bulletFactory.bullets)
        b->stop();
    bgMusicPlayer.stop();
    paused = true;
    button->setText("Start");
}
void DogInvaders::startItems() {
    if(!player->isDead)
        player->start();
    for(auto&& b : bulletFactory.bullets)
        b->start();
    bgMusicPlayer.play();
    paused = false;
    button->setText("Pause");
}
void DogInvaders::keyPressEvent(QKeyEvent * event){
    if(paused) // do nothing
        return;
    switch(event->key()){
    case(Qt::Key_R):
        // Key R is for respawning player
        player->isDead = false;
        player->start();
        break;
    case(Qt::Key_S):
        // Key S is for re-setting the game
        if(player->isDead)
            resetGame();
        break;
    }
}

/**********************************************************************/
/**************** UPDATES MOVEMENT & FRAMES ***************************/
/**********************************************************************/

//actual animations; loads items to redraw
void DogInvaders::nextFrame() {
    if(!paused){
        // update object's movement
        updateMovements();
        for(auto&& a : aliens)
            std::get<0>(a)->nextFrame();
        // next frame for explosions
        for(auto&& e : explosions)
            e.nextFrame();
        // next frame for background
        bg.nextFrame();
    }
    update();
}

void DogInvaders::updateMovements(){
    // update if any bullets will destory any thing
    std::list<Bullet*>::iterator bIt = bulletFactory.bullets.begin();
    while(bIt != bulletFactory.bullets.end()) {
        if((*bIt)->type == "PlainBullet"){
            // check for alien
            if(checkBulletHitAlien(bIt)){
                bIt = bulletFactory.bullets.erase(bIt);
                gameScore += SCORE_PER_ALIEN;
                continue;
            }
            break;
        }
        else if((*bIt)->type == "RainbowBullet"){
            if(!player->isDead){
                // check for player
                if(checkBulletHitShip(bIt)){
                    player->isDead = true; // set the flag of ship had been dead
                    player->stop();
                    bIt = bulletFactory.bullets.erase(bIt);
                    continue;
                }
            }
        }
        ++bIt;
    }
    
    // update aliens' movement
    for(std::tuple<SwarmComponent*, std::string, unsigned> &tuple : aliens) {
        // increment the instruction of the alien swarms if it is next movement
        if(nextMovement()){
            ++std::get<2>(tuple);
        }
        // finished our list of actions, reset to zero idx
        if (std::get<2>(tuple) >= std::get<1>(tuple).length())
            std::get<2>(tuple) = 0;
        
        // do movement based on instruction string
        char m = std::get<1>(tuple).at(std::get<2>(tuple));
        if(m == 'H'){ // extension of hunting
            if(std::get<0>(tuple)->isComposite()){
                SwarmComposite* sc = dynamic_cast<SwarmComposite*>(std::get<0>(tuple));
                for(unsigned i = 0; i < sc->aliens.size(); ++i){
                    // add hunting capability and tint color to red
                    sc->aliens[i] = new AlienRed(*new AlienHunting(*dynamic_cast<Alien*>(sc->aliens[i])));
                }
            }else{ // single component
                std::get<0>(tuple) = new AlienRed(*new AlienHunting(*dynamic_cast<Alien*>(std::get<0>(tuple))));
            }
            // change the instruction to instruction string to zero
            std::get<1>(tuple) = "_"; // place holder
            std::get<2>(tuple) = 0;
        }else{
            std::get<0>(tuple)->move(m);
            if (m == 'S') // special case of shoot, we move immediately
                ++std::get<2>(tuple);
        }
    }
    counter++;
}

/**********************************************************************/
/********************** CHECKER FUNCTION ******************************/
/**********************************************************************/
bool DogInvaders::checkBulletHitShip(std::list<Bullet*>::iterator &bIt){
    // check for if bullet hit dog
    Ship* s = player;
    QRect r(s->getX()-s->getImage().width()/2, s->getY()-s->getImage().height()/2, s->getImage().width(), s->getImage().height());
    bulletWithinImage((*bIt)->getX(), (*bIt)->getY(), (*bIt)->getImage().width(), (*bIt)->getImage().height(), s->getX(), s->getY(), s->getImage().width(), s->getImage().height());
    if(r.contains((*bIt)->getX(), (*bIt)->getY())){
        // bullet hit the dog, create explosion
        explosions.push_back(explosionFactory.createExplosion(s->getX(), s->getY(), static_cast<int>(s->getImage().width() * 3), ShipExplosion));
        return true;
    }
    return false;
}

bool DogInvaders::checkBulletHitAlien(std::list<Bullet*>::iterator &bIt){
    // check for alien
    std::vector<std::tuple<SwarmComponent*, std::string, unsigned>>::iterator tupleIt = aliens.begin();
    while(tupleIt != aliens.end()) {
        int b_x1 = (*bIt)->getX() - (*bIt)->getImage().width()/2;
        int b_y1 = (*bIt)->getY() - (*bIt)->getImage().height()/2;
        int b_x2 = (*bIt)->getX() + (*bIt)->getImage().width()/2;
        int b_y2 = (*bIt)->getY() + (*bIt)->getImage().height()/2;
        
        if(std::get<0>((*tupleIt))->beenShotAt(b_x1, b_y1, b_x2, b_y2, explosions, explosionFactory)){
            // bullet had hit target, return success
            return true;
        }
        ++tupleIt;
    }
    return false;
}

bool DogInvaders::bulletWithinImage(int bx, int by, int bWidth, int bHeight, int imageX, int imageY, int imageWidth, int imageHeight){
    int b_x1 = bx - bWidth/2;
    int b_y1 = by - bHeight/2;
    int b_x2 = bx + bWidth/2;
    int b_y2 = by + bHeight/2;
    int img_x1 = imageX - imageWidth/2;
    int img_y1 = imageY - imageHeight/2;
    int img_x2 = imageX + imageWidth/2;
    int img_y2 = imageY + imageHeight/2;
    
    // Check if two rectagle is overlaping
    if (b_x1 < img_x2 && b_x2 > img_x1
            && b_y1 < img_y2 && b_y2 > img_y1)
        return true;
    return false;
}

// determind if we should increment to next action
bool DogInvaders::nextMovement() {
    if (counter > maxCounter)
        counter = 0;
    if (counter == maxCounter) {
        //reset the counter and move the iterator up
        return true;
    }
    return false;
}

/**********************************************************************/
/**************** PAINTER METHOD FOR ALL OBJECTS **********************/
/**********************************************************************/
void DogInvaders::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event)
    QPainter painter(this);
    // draw background of stars
    bg.draw(&painter);
    
    //draw player ship
    if(!player->isDead){
        painter.drawPixmap(player->getX() - player->getImage().width()/2, player->getY() - player->getImage().height()/2, player->getImage());
    }
    
    //in Stage 2, draw the enemies...
    for(std::tuple<SwarmComponent*, std::string, unsigned> pair : aliens) {
        std::get<0>(pair)->draw(&painter);
    }
    
    //draw each bullet
    std::list<Bullet*> &bullets = bulletFactory.bullets;
    std::list<Bullet*>::iterator bit = bullets.begin();
    QRect frameWindow = QRect(0,0,WIDTH, HEIGHT);
    while (bit != bullets.end()) {
        // if bullet is out of frame, then delete it..
        //        if(!(*bit)->inFrame()) {
        if(!(frameWindow.contains((*bit)->getX() - (*bit)->getImage().width()/2,
                                  (*bit)->getY() - (*bit)->getImage().height()/2)  ||
             frameWindow.contains((*bit)->getX() + (*bit)->getImage().width()/2,
                                  (*bit)->getY() + (*bit)->getImage().height()/2) )){
            bit = bullets.erase(bit);
            continue;
        }
        // else, draw it
        painter.drawPixmap((*bit)->getX() - (*bit)->getImage().width()/2, (*bit)->getY() - (*bit)->getImage().height()/2, (*bit)->getImage());
        bit++;
    }

    // draw explosion
    std::vector<Explosion>::iterator it = explosions.begin();
    while (it != explosions.end()) {
        if((*it).finished) {
            it = explosions.erase(it);
            continue;
        }
        (*it).draw(&painter);
        ++it;
    }

    // display Game Over Text
    if(player->isDead){
        painter.setPen(Qt::red);
        QFont font1;
        font1.setPointSize(60);
        font1.setBold(true);
        font1.setOverline(true);
        font1.setUnderline(true);
        font1.setHintingPreference(QFont::PreferFullHinting);
        painter.setFont(font1);
        painter.drawText(0, 0, WIDTH, HEIGHT, Qt::AlignCenter, "GAME OVER");

        // display hint to restart game
        painter.setPen(Qt::yellow);
        QFont font2;
        font2.setPointSize(20);
        font2.setItalic(true);
        painter.setFont(font2);
        painter.drawText(0, static_cast<int>(HEIGHT * 0.5), WIDTH, static_cast<int>(HEIGHT * 0.25),
                         Qt::AlignCenter|Qt::AlignTop, "Press [R] to respawn\n"
                                                       "Press [S] to start over");
    }
    // display scores on top right
    gameScoreWidget->display(std::to_string(gameScore).c_str());
}

/**********************************************************************/
/********************* LOAD FUNCTIONS *********************************/
/**********************************************************************/
void DogInvaders::loadTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);
}

void DogInvaders::loadButtons() {
    //pause button is init here instead of its own
    //class because it's always visible.
    button = new QPushButton("Pause", this);
    button->setGeometry(QRect(0, 0, 100, 30));
    button->setStyleSheet("background-color: white");
    connect(button, SIGNAL(clicked()), this, SLOT(pause()));
    //color button...
    color = new ColorButton(100, 0, this);
    //size buttons!
    sizes = new SizeButton(200, 0, this);
}

/**********************************************************************/
/**************** BUTTONS / COLOR / SIZE ******************************/
/**********************************************************************/
void DogInvaders::displayColorOptions() {
    color->displayOptions();
}
void DogInvaders::setColor(std::string col) {
    //convert to Qstring
    QString color = QString::fromStdString(col);
    player->setColor(color);
    reader.setColor(col);
}
void DogInvaders::setRed() {
    setColor("Red");
}
void DogInvaders::setOrange() {
    setColor("Orange");
}
void DogInvaders::setYellow() {
    setColor("Yellow");
}
void DogInvaders::setGreen() {
    setColor("Green");
}
void DogInvaders::setBlue() {
    setColor("Blue");
}
void DogInvaders::setSizeShip(std::string size){
    QString fix = QString::fromStdString(size);
    player->setSize(fix);
    reader.setSize(size);
}
void DogInvaders::setTiny() {
    setSizeShip("Tiny");
}
void DogInvaders::setNormal() {
    setSizeShip("Normal");
}
void DogInvaders::setLarge() {
    setSizeShip("Large");
}
void DogInvaders::setGiant() {
    setSizeShip("Giant");
}
