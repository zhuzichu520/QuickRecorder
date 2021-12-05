#include "tool.h"

Tool::Tool(QObject *parent) : QObject(parent)
{

}

void Tool::captureRect(int x,int y,int width,int height){
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap rect = screen->grabWindow(0).copy(x,y,width,height);
    QGuiApplication::clipboard()->setPixmap(rect);
    Q_EMIT captureResult(true);
}

void Tool::captureScreen(){
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("screen.png");
}
