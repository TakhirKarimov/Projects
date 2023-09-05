#include "qglbegin.h"

#include "../modules/s21_3dviewer.h"

QGLBegin::QGLBegin(QWidget *parent) : QOpenGLWidget(parent) {
  color_back = Qt::black;
  color_line = Qt::white;
  color_vert = Qt::white;
  proection = 0;
  point_type = 0;
  point_size = 1;
  line_size = 1;
  line_type = 0;
}

void QGLBegin::initializeGL() { glEnable(GL_DEPTH_TEST); }

void QGLBegin::paintGL() {
  glClearColor(color_back.redF(), color_back.greenF(), color_back.blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->proection == 0) {
    glOrtho(-1, 1, -1, 1, -1, 2);
  } else {
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnableClientState(GL_VERTEX_ARRAY);
  if (cordination.vertices != 0) {
    glVertexPointer(3, GL_DOUBLE, 0, cordination.vertices);
    if (point_type > 0) {
      if (point_type == 1)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);
      glPointSize(point_size);
      glColor3d(color_vert.redF(), color_vert.greenF(), color_vert.blueF());
      glDrawArrays(GL_POINTS, 0, cordination.count_vertices);
    }
  }
  if (cordination.lines != 0) {
    glColor3d(color_line.redF(), color_line.greenF(), color_line.blueF());
    glLineWidth(line_size);
    glLineStipple(1, 0x00F0);
    if (line_type == 1)
      glEnable(GL_LINE_STIPPLE);
    else
      glDisable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, cordination.count_lines, GL_UNSIGNED_INT,
                   cordination.lines);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void QGLBegin::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}
