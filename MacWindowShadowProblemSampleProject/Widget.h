#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(const QRectF &rect, QWidget *parent = 0);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);

private:
    static void setWidgetTransparentBackground( QWidget* const widget );

    void updateInputMask();

private:
    int m_inputMaskUpdateTimerId;
};

#endif // WIDGET_H
