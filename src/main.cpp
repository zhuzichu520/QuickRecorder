#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include <QIcon>
#include <QDateTime>
#include "src/tool.h"
#include "src/ScreenImageProvider.h"

extern "C"{
    #include <libavdevice/avdevice.h>
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qint64 startTime = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    qDebug()<<"开始时间："<<startTime;

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/drawable/ic_logo.png"));
    app.setQuitOnLastWindowClosed(false);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QuickRecorder_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("tool",new Tool);
    engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);
    const QUrl url(QStringLiteral("qrc:/layout/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    qint64 endTime = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    qDebug()<<"结束时间："<<endTime;
    qDebug()<<"初始化时间："<<endTime-startTime;

    return app.exec();
}
