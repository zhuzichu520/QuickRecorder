#ifndef SCREENIMAGEPROVIDER_H
#define SCREENIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>
#include <QGuiApplication>
#include <QScreen>

class ScreenImageProvider : public QQuickImageProvider
{
public:

    ScreenImageProvider(): QQuickImageProvider(QQuickImageProvider::Pixmap){};

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

};


#endif // SCREENIMAGEPROVIDER_H

