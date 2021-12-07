#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QClipboard>
#include <QTimer>
#include "src/gdigrab.h"

class Tool : public QObject
{
    Q_OBJECT
public:
    explicit Tool(QObject *parent = nullptr);
    Q_INVOKABLE void start(QString &path,int x,int y,int width,int height);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void captureScreen();
    Q_INVOKABLE void captureRect(int x,int y,int width,int height);
    Q_SIGNAL void captureResult(bool isSuccess);
    Q_SLOT void videoshow();
private:
    Gdigrab *g;
    QTimer *timer;
};

#endif // TOOL_H
