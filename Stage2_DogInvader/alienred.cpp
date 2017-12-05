#include "alienred.h"

AlienRed::AlienRed(Alien& decorator) : AlienDecorator (decorator)
{}

void AlienRed::draw(QPainter *painter) const{
    if(decorator.isDead())
        return;
    //    QPainter p;
    //    QImage img(decorator.getImage().toImage());
    //    QImage mask(img);
    //    // draw the tinted color
    //    p.begin(&mask);
    //    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    //    p.fillRect(0,0,mask.width(),mask.height(),Qt::red);
    //    p.end();
    //    // draw the original image as overlay
    //    p.begin(&img);
    //    p.setCompositionMode(QPainter::CompositionMode_Overlay);
    //    p.drawImage(0,0,mask);
    //    p.end();
    ////     draw the final image
    painter->drawPixmap(decorator.getX()-decorator.getWidth()/2,
                        decorator.getY()-decorator.getHeight()/2, getImage());
}

QPixmap AlienRed::getImage() const{
    QPainter p;
    QImage img(decorator.getImage().toImage());
    QImage mask(img);
    // draw the tinted color
    p.begin(&mask);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(0,0,mask.width(),mask.height(),Qt::red);
    p.end();
    // draw the original image as overlay
    p.begin(&img);
    p.setCompositionMode(QPainter::CompositionMode_Overlay);
    p.drawImage(0,0,mask);
    p.end();
    //     draw the final image
    //    painter->drawImage(decorator.getX()-decorator.getWidth()/2,
    //                       decorator.getY()-decorator.getHeight()/2, img);
    return QPixmap::fromImage(img);
}
