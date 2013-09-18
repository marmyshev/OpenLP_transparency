#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w1( QRectF( 50, 50, 300, 100 ) );
    Widget w2( QRectF( 400, 50, 300, 100 ) );
    w1.show();
    w2.show();

    return a.exec();
}
