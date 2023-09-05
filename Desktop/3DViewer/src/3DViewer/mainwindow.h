#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QTimer>

#include "../3dparty/QtGifImage-master/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QColor color;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void open_file();
  void save_options();
  void read_options();
  void on_pushButton_clicked();
  void on_pushButton_11_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_pushButton_15_clicked();
  void on_pushButton_16_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_10_clicked();
  void on_horizontalSlider_sliderPressed();
  void on_horizontalSlider_valueChanged(int value);
  void on_horizontalSlider_2_sliderPressed();
  void on_horizontalSlider_2_valueChanged(int value);
  void on_horizontalSlider_3_sliderPressed();
  void on_horizontalSlider_3_valueChanged(int value);
  void on_horizontalSlider_4_sliderPressed();
  void on_horizontalSlider_4_valueChanged(int value);
  void on_horizontalSlider_5_sliderPressed();
  void on_horizontalSlider_5_valueChanged(int value);
  void on_horizontalSlider_6_sliderPressed();
  void on_horizontalSlider_6_valueChanged(int value);
  void on_pushButton_21_clicked();
  void on_horizontalSlider_7_sliderPressed();
  void on_horizontalSlider_7_valueChanged(int value);
  void on_comboBox_currentIndexChanged(int index);
  void on_comboBox_3_currentIndexChanged(int index);
  void on_spinBox_9_valueChanged(int arg1);
  void on_pushButton_18_clicked();
  void on_pushButton_17_clicked();
  void on_comboBox_2_currentIndexChanged(int index);
  void on_spinBox_8_valueChanged(int arg1);
  void on_pushButton_19_clicked();
  void on_pushButton_20_clicked();
  void save_frame();

 private:
  Ui::MainWindow *ui;
  QString options_file;
  QString obj_folder;
  int slider_position_x1 = 0, slider_position_x2 = 0, slider_position_y1 = 0,
      slider_position_y2 = 0, slider_position_z1 = 0, slider_position_z2 = 0,
      slider_position_zoom = 0;
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  int count_gif;
};
#endif  // MAINWINDOW_H
