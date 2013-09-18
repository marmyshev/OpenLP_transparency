#include <QtCore>
#include <QtGui>

class View : public QGraphicsView
{
    public:
        View() : QGraphicsView() {
            setAttribute(Qt::WA_TranslucentBackground);
            setScene(new QGraphicsScene);
            QGraphicsItem* i = scene()->addRect(10, 10, 40, 40, Qt::NoPen,
                                                Qt::red);
            i->setFlag(QGraphicsItem::ItemIsMovable);
        }

    protected:
        void drawBackground(QPainter* p, const QRectF& rect) {
            QPainter::CompositionMode c = p->compositionMode();
            p->setCompositionMode(QPainter::CompositionMode_Source);
            p->fillRect(rect, Qt::transparent);
            p->setCompositionMode(c);

            p->fillRect(rect, QColor(0, 0, 255, 120));
        }
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    View v;
    v.show();
    return app.exec();
}
