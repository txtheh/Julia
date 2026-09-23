#include "drawingwidget.h"
#include "complex.h"
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QMouseEvent>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void DrawingWidget::reset()
{
    centerRe = 0;
    centerIm = 0;
    scale = 4;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *)
{
    image = QImage(size(), QImage::Format_RGB32);
    Complex c(-0.8, 0.156);

    for (int y = 0; y < height(); y++)
    {
        for (int x = 0; x < width(); x++)
        {
            double re = centerRe
                        + (x - width() / 2.0) * scale / width();

            double im = centerIm
                        + (y - height() / 2.0) * scale / width();

            Complex z(re, im);

            int iteration = 0;

            while (iteration < maxIterations && z.abs() <= 2)
            {
                z = z * z + c;
                iteration++;
            }

            if (iteration == maxIterations)
            {
                image.setPixelColor(x, y, Qt::black);
            }
            else
            {
                QColor colors[] =
                    {
                        QColor(225, 147, 178),   // пудрово-розовый
                        QColor(227, 164, 191),   // светло-розовый
                        QColor(201, 155, 195),   // розово-сиреневый
                        QColor(205, 180, 212),   // сиреневый
                        QColor(204, 174, 212),   // светлая сирень
                        QColor(189, 219, 233),   // голубой
                        QColor(190, 227, 225),   // мятный
                        QColor(204, 228, 222),   // светлая мята
                        QColor(206, 214, 183),   // шалфейный
                        QColor(206, 230, 133),   // светло-зелёный
                        QColor(244, 235, 203),   // кремово-жёлтый
                        QColor(238, 222, 177),   // нежно-жёлтый
                        QColor(226, 161, 189),   // розовый
                        QColor(204, 213, 181),   // серо-зелёный
                        QColor(227, 213, 230),   // очень светлая сирень
                        QColor(202, 227, 221)    // очень светлая мята
                    };

                int colorNumber = iteration % 16;
                image.setPixelColor(x, y, colors[colorNumber]);
            }
        }
    }

    QPainter p(this);
    p.drawImage(0, 0, image);
    if (selecting)
    {
        QRect rect(startPoint, currentPoint);
        p.setPen(QPen(Qt::white, 2));
        p.drawRect(rect.normalized());
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    startPoint = event->pos();
    currentPoint = startPoint;
    selecting = true;
    update();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (selecting)
    {
        currentPoint = event->pos();
        update();
    }
}
void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!selecting)
        return;
    currentPoint = event->pos();
    selecting = false;
    int x1 = qMin(startPoint.x(), currentPoint.x());
    int x2 = qMax(startPoint.x(), currentPoint.x());
    int y1 = qMin(startPoint.y(), currentPoint.y());
    int y2 = qMax(startPoint.y(), currentPoint.y());
    int rectWidth = x2 - x1;
    int rectHeight = y2 - y1;
    if (rectWidth < 10 || rectHeight < 10)
    {
        update();
        return;
    }
    double left = centerRe
                  + (x1 - width() / 2.0) * scale / width();

    double right = centerRe
                   + (x2 - width() / 2.0) * scale / width();

    double top = centerIm
                 + (y1 - height() / 2.0) * scale / width();

    double bottom = centerIm
                    + (y2 - height() / 2.0) * scale / width();

    centerRe = (left + right) / 2;
    centerIm = (top + bottom) / 2;
    double newWidth = right - left;
    double newHeight = bottom - top;
    scale = qMax(newWidth, newHeight * width() / height());
    update();
}