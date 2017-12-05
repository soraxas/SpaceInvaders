#include <QApplication>
#include "graphicsrenderer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // qt app
    si::GraphicsRenderer rendener; // in charge of all graphics
    rendener.show();
    return app.exec();
}
