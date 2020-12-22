#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <gl/GLU.h>
#include <gl/GL.h>

class oglwidget : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    oglwidget(QWidget *parent = 0):QOpenGLWidget(parent){}
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
};

#endif // OGLWIDGET_H
