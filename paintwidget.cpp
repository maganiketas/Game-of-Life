#include "paintwidget.h"

#include <QPainter>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    life = nullptr;

    painting = false;
    openingFile = false;

    paintTimer = new QTimer(this);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(calcNewState()));
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint currentPos = event->pos();
    currentPos.setX((currentPos.x() - currentPos.x()%10)/10);
    currentPos.setY((currentPos.y() - currentPos.y()%10)/10);

    if(currentPos.x() >= 0 && currentPos.y() >= 0 && currentPos.x() < cellCountHor && currentPos.y() < cellCountVer)
    {
        if(!openingFile)
        {
            life->setCell(currentPos.x(), currentPos.y(), true);

            updateImage(currentPos.x(), currentPos.y());

            painting = true;
        }
        else
            getImageFromFile(currentPos.x(), currentPos.y(), fileName);
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentPos = event->pos();
    currentPos.setX((currentPos.x() - currentPos.x()%10)/10);
    currentPos.setY((currentPos.y() - currentPos.y()%10)/10);

    if(currentPos.x() >= 0 && currentPos.y() >= 0 && currentPos.x() < cellCountHor && currentPos.y() < cellCountVer && painting)
    {
        if(!(*life)(currentPos.x(), currentPos.y()))
            life->setCell(currentPos.x(), currentPos.y(), true);

        updateImage(currentPos.x(), currentPos.y());
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint currentPos = event->pos();
    currentPos.setX((currentPos.x() - currentPos.x()%10)/10);
    currentPos.setY((currentPos.y() - currentPos.y()%10)/10);

    if(currentPos.x() >= 0 && currentPos.y() >= 0 && currentPos.x() < cellCountHor && currentPos.y() < cellCountVer && painting)
    {
        if(!(*life)(currentPos.x(), currentPos.y()))
            life->setCell(currentPos.x(), currentPos.y(), true);

        updateImage(currentPos.x(), currentPos.y());
    }

    painting = false;
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    double newx = double(x() + (width()%10)/2 - 0.5);
    double newy = double(y() + (height()%10)/2 - 0.5);
    int newWidth = width() - width()%10 + 1;
    int newHeight = height() - height()%10 + 1;

    setGeometry(newx, newy, newWidth, newHeight);

    if(!life)
    {
        cellCountHor = (width() - 1)/10;
        cellCountVer = (height() - 1)/10;
        life = new Automaton(cellCountHor, cellCountVer);
    }

    if (width() > image.width() || height() > image.height()) {
        int newImWidth = qMax(width(), image.width());
        int newImHeight = qMax(height(), image.height());
        resizeImage(&image, QSize(newImWidth, newImHeight));
        drawGrid();
        update();
    }

    QWidget::resizeEvent(event);
}

void PaintWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintWidget::updateImage(int x, int y)
{
    QPainter painter(&image);

    painter.setBrush(QBrush(Qt::black));

    painter.drawRect(x*10, y*10, 10, 10);

    update(QRect(x*10, y*10, 10, 10));
}

void PaintWidget::repaintImage()
{
    QPainter painter(&image);

    for(int i = 0; i < cellCountHor; i++)
    {
        for(int j = 0; j < cellCountVer; j++)
        {
            if((*life)(i, j))
            {
                painter.setBrush(QBrush(Qt::black));
                painter.drawRect(i*10, j*10, 10, 10);
            }
            else
            {
                painter.setBrush(QBrush(Qt::white));
                painter.drawRect(i*10, j*10, 10, 10);
            }
        }
    }

    repaint(QRect(0, 0, width(), height()));
}

void PaintWidget::calcNewState()
{
    life->calcNewWorld();

    repaintImage();
}

void PaintWidget::clearAll()
{
    life->clearTable();

    repaintImage();
}

void PaintWidget::getImageFromFile(int x, int y, const QString &fileName)
{
    QFile figure(fileName);

    figure.open(QIODevice::ReadOnly);

    QString line;

    int i = x, j = y;

    while(!figure.atEnd())
    {
        line = figure.readLine();
        i = x;
        for(auto letter = line.begin(); letter < line.end(); letter++)
        {
            if(*letter == '0')
                life->setCell(i, j, false);
            else if(*letter == '1')
                life->setCell(i, j, true);
            i++;
        }
        j++;
    }
    figure.close();

    openingFile = false;

    repaintImage();
}

void PaintWidget::startPainting()
{
    paintTimer->start(1);
}

void PaintWidget::stopPainting()
{
    paintTimer->stop();
}

void PaintWidget::randCells()
{
    life->clearTable();

    int x, y;

    for(int i = 0; i < cellCountHor*cellCountVer/2; i++)
    {
        x = rand()%cellCountHor;
        y = rand()%cellCountVer;

        if((*life)(x, y))
            i--;
        else
            life->setCell(x, y, true);
    }

    repaintImage();
}

void PaintWidget::setFileName(const QString &value)
{
    fileName = value;
    openingFile = true;
}

void PaintWidget::drawGrid()
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

    int i;

    for(i = 0; i <= cellCountHor; i++)
    {
        painter.drawLine(QPoint(i*10, 0), QPoint(i*10, height()));
    }
    for(i = 0; i <= cellCountVer; i++)
    {
        painter.drawLine(QPoint(0, i*10), QPoint(width(), i*10));
    }
    repaint(QRect(0, 0, width(), height()));
}

PaintWidget::~PaintWidget()
{
    delete life;
}

