#include "Widget.h"

#include <QtGui/QGridLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

#include "CustomGraphicsItem.h"

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>

#ifdef Q_OS_LINUX
    #include <QtGui/QBitmap>
    #include <QtGui/QX11Info>
    #include <X11/Xlib.h>
    #include <X11/extensions/shape.h>
#endif

Widget::Widget(const QRectF &rect, QWidget *parent)
    : QWidget(parent)
    , m_inputMaskUpdateTimerId(0)
{
    setWidgetTransparentBackground( this );
    CustomGraphicsItem* const item = new CustomGraphicsItem;
    item->setSize( rect.size() );
    item->setPos( rect.topLeft() );

    QGraphicsScene* const scene = new QGraphicsScene( this );
    scene->setSceneRect( QApplication::desktop()->geometry() );
    scene->setBackgroundBrush( Qt::transparent );
    scene->addItem( item );

    QGraphicsView* const view = new QGraphicsView( scene );
    setWidgetTransparentBackground( view );
    QGridLayout* const layout = new QGridLayout( this );
    layout->setMargin( 0 );
    layout->addWidget( view );


}

Widget::~Widget()
{
    if ( m_inputMaskUpdateTimerId != 0 )
    {
        this->killTimer( m_inputMaskUpdateTimerId );
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent( event );

    if ( m_inputMaskUpdateTimerId == 0 )
    {
        m_inputMaskUpdateTimerId = this->startTimer( 300 );
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    if ( event->timerId() == m_inputMaskUpdateTimerId )
    {
        this->updateInputMask();
    }
}

void Widget::setWidgetTransparentBackground(QWidget *const widget)
{
    widget->setStyleSheet( "border: none; background: transparent" );
    // QPalette pal = widget->palette();
    // pal.setColor( QPalette::Base, Qt::transparent );
    // widget->setPalette( pal );
    widget->setGeometry( QApplication::desktop()->geometry() );
    widget->setAttribute( Qt::WA_TranslucentBackground );

    /*
     * Uncomment the line below to remove the static shadow problem.
     * Note that this attribute is available from Qt 4.8 onward.
     * Prior to Qt library version 4.8, one should use Objective-C code
     * to remove the Mac window shadow.
     * widget->setAttribute( Qt::WA_MacNoShadow );
     */

    widget->setWindowFlags( Qt::FramelessWindowHint );
}

void Widget::updateInputMask()
{
#ifdef Q_OS_LINUX
    QImage windowImage( this->size(), QImage::Format_ARGB32_Premultiplied );
    windowImage.fill( 0 );
    QPainter painter( &windowImage );
    this->render( &painter );

    const QBitmap mask = QBitmap::fromImage( windowImage.createMaskFromColor( 0, Qt::MaskInColor ) );
    const QRegion region = QRegion( mask );
    XShapeCombineRegion( QX11Info::display(), this->winId(), ShapeInput, 0, 0, region.handle(), ShapeSet );
#endif
}
