#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QClipboard>

class Tool : public QObject
{
    Q_OBJECT
public:
    explicit Tool(QObject *parent = nullptr);
    Q_INVOKABLE void captureScreen();
    Q_INVOKABLE void captureRect(int x,int y,int width,int height);
    Q_SIGNAL void captureResult(bool isSuccess);
};

#endif // TOOL_H
