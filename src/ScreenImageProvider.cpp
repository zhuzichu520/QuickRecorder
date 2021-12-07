#include "ScreenImageProvider.h"

QPixmap ScreenImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    qDebug()<<"requestPixmap-id:"<<id;
    QScreen *screen = QGuiApplication::primaryScreen();
    return screen->grabWindow(0);
}
