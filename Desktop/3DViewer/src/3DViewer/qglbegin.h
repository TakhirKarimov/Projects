#ifndef QGLBEGIN_H
#define QGLBEGIN_H

#include <QtWidgets>

#include "QtOpenGLWidgets/qopenglwidget.h"

extern "C" {
#include "../modules/s21_3dviewer.h"
#include "../modules/s21_transformations.h"
}

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class QGLBegin : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit QGLBegin(QWidget *parent = 0);
  QColor color_back, color_line, color_vert;
  parametrs cordination = {0};
  int proection, point_type, point_size, line_size, line_type;

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

 signals:

 public slots:

 private:
};

#endif  // QGLBEGIN_H
