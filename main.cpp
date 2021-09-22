#include "mainwindow.h"
#include "connnect.h"

#include <QApplication>
#include <QProcess>
#include <QStyleFactory>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // a.setStyle(QStyleFactory::create("fusion"));
    // QProcess process;
    // QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    if (!createConnection()) {
        return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
