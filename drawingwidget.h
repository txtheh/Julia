#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H
#include <QWidget>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    void reset();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int maxIterations = 50;
    double centerRe = 0;
    double centerIm = 0;
    double scale = 4;
    QPoint startPoint;
    QPoint currentPoint;
    bool selecting = false;
    QImage image;
    bool needRedraw = true;
};

#endif // DRAWINGWIDGET_H