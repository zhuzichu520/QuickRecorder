#include "tool.h"

Tool::Tool(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Tool::videoshow);
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

void Tool::start(QString &path,int x,int y,int width,int height){
    if(!path.startsWith("file:///")){
        return;
    }
    g = new Gdigrab(path.replace("file:///",""),x,y,width,height);
    if(g->open()) {
        timer->start(1000 / g->getFPS());
        qDebug() << g->getFPS();
    }else {
        qDebug() << "error";
    }
}

void Tool::stop(){
    g->stop();
    timer->stop();
}

void Tool::videoshow()
{
    if(g->read()) {
        AVFrame *f = g->getFrame();
        if(f) {
            QImage img((uchar*)f->data[0],f->width,f->height,QImage::Format_ARGB32);
            qDebug()<<"fps:"<<g->getFPS();
        }
    }
}
