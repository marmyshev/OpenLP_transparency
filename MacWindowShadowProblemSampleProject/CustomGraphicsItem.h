#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QtGui/QGraphicsItem>

class CustomGraphicsItem : public QGraphicsItem
{
public:
    explicit CustomGraphicsItem(QGraphicsItem *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QRectF boundingRect() const;
//    virtual QPainterPath shape() const;

    void setSize( const QSizeF& size );

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    enum MouseCursorState
    {
        MouseCursorStateAway,
        MouseCursorStateHovering,
        MouseCursorStateMoving
    };

    static QColor color(const MouseCursorState state);

private:
    QSizeF m_size;
    QColor m_color;
};

#endif // CUSTOMGRAPHICSITEM_H
