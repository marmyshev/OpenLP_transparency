#include <QtCore>
#include <QtGui>
#include <X11/extensions/Xrender.h>

class View : public QGraphicsView
{
    public:
        View() : QGraphicsView() {
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
    bool argbVisual = false;
        Display *dpy = XOpenDisplay(0); // open default display
    if (!dpy) {
        qWarning("Cannot connect to the X server");
        return 1;
    }

    int screen = DefaultScreen(dpy);
    Colormap colormap = 0;
    Visual *visual = 0;
    int eventBase, errorBase;

    if (XRenderQueryExtension(dpy, &eventBase, &errorBase)) {
        int nvi;
        XVisualInfo templ;
        templ.screen  = screen;
        templ.depth   = 32;
        templ.c_class = TrueColor;
        XVisualInfo *xvi = XGetVisualInfo(dpy, VisualScreenMask |
                                          VisualDepthMask |
                                          VisualClassMask, &templ, &nvi);

        for (int i = 0; i < nvi; ++i) {
            XRenderPictFormat *format = XRenderFindVisualFormat(dpy,
                                                                xvi[i].visual);
            if (format->type == PictTypeDirect && format->direct.alphaMask) {
                visual = xvi[i].visual;
                colormap = XCreateColormap(dpy, RootWindow(dpy, screen),
                                           visual, AllocNone);
                argbVisual=true;
                break;
            }
        }
    }

    if (argbVisual == true) {
        QApplication app(dpy, argc, argv, Qt::HANDLE(visual),
                         Qt::HANDLE(colormap));
        View v;
        v.show();
        return app.exec();
    }
    else  {
        qWarning("Couldn't find ARGB visual... Exiting.");
        return 1;
    }
}
