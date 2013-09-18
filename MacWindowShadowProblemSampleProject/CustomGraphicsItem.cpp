#include "CustomGraphicsItem.h"

#include <QtGui/QPainter>
#include <QtGui/QGraphicsSceneHoverEvent>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QGraphicsSceneMouseEvent>

#include <QtCore/QDebug>

CustomGraphicsItem::CustomGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_color( color( MouseCursorStateAway ) )
{
    this->setAcceptHoverEvents( true );
    this->setFlags( QGraphicsItem::ItemIsMovable );
}

void CustomGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( m_size.isValid() )
    {
        Q_UNUSED(widget)
        static const qreal strokeWidth = 5.0;
        painter->setBrush( QBrush( m_color ) );
        painter->setPen( QPen( QBrush( Qt::black ), strokeWidth ) );
        painter->drawEllipse( option->exposedRect.adjusted( strokeWidth / 2.0,
                                                             strokeWidth / 2.0,
                                                             - strokeWidth / 2.0,
                                                             - strokeWidth / 2.0) );
    }
}

QRectF CustomGraphicsItem::boundingRect() const
{
    return QRectF( 0.0, 0.0, m_size.width(), m_size.height() );
}

//QPainterPath CustomGraphicsItem::shape() const
//{
//    QPainterPath path;
//    path.addEllipse( this->boundingRect() );
//    return path;
//}

void CustomGraphicsItem::setSize(const QSizeF &size)
{
    if ( size.isValid()
         && m_size != size )
    {
        this->prepareGeometryChange();
        m_size = size;
    }
}

void CustomGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent( event );

    m_color = color( MouseCursorStateHovering );
    this->update();
}

void CustomGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent( event );

    m_color = color( MouseCursorStateAway );
    this->update();
}

void CustomGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent( event );

    if ( event->button() == Qt::LeftButton )
    {
        m_color = color( MouseCursorStateMoving );
        this->update();
    }
}

void CustomGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent( event );

    if ( event->button() == Qt::LeftButton )
    {
        m_color = color( MouseCursorStateHovering );
        this->update();
    }
}

QColor CustomGraphicsItem::color(const CustomGraphicsItem::MouseCursorState state)
{
    QColor color;
    if ( state == MouseCursorStateAway )
    {
        color = Qt::darkRed;
    }
    else if ( state == MouseCursorStateHovering )
    {
        color = Qt::red;
    }
    else if ( state == MouseCursorStateMoving )
    {
        color.setRgb( 255, 0, 0, 128 );
    }

    return color;
}
