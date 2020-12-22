#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include "mainwindow.h"
#include "automaton.h"

class PaintWidget : public QWidget
{
    Q_OBJECT

    Automaton *life;
    QTimer *paintTimer;
    QImage image;
    int cellCountHor;
    int cellCountVer;
    bool painting;
    QPoint oldPos;
    QString fileName;
    bool openingFile;
    void drawGrid();
protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void startPainting();
    void stopPainting();
    void randCells();
    void resizeImage(QImage *image, const QSize &newSize);
    void updateImage(int x, int y);
    void repaintImage();
    void calcNewState();
    void clearAll();
    void getImageFromFile(int x, int y, const QString &fileName);
public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();
    void setFileName(const QString &value);
};

#endif // PAINTWIDGET_H
