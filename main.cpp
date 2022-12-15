#include "mainwidget.h"
#include <QApplication>
#include <QFile>

static void setStyle(const QString &styleName)
{
    QFile file(QString("%1").arg(styleName));
    file.open(QFile::ReadOnly);
    QString css = QLatin1String(file.readAll());
    qApp->setStyleSheet(css);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setStyle(":/css/css/mycss.css");
    MainWidget w;
    w.show();
    return a.exec();
}
