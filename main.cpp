#include <QApplication>
#include "myjson.h"
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    MyJson w;
    w.show();
    return app.exec();
}
