#include "mainwindow.h"

#include "./ui_mainwindow.h"

extern "C" {
#include "../modules/s21_3dviewer.h"
#include "../modules/s21_transformations.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->action, SIGNAL(triggered()), this, SLOT(open_file()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(open_file()));
  options_file = QApplication::applicationDirPath() + "/conf.ini";
  read_options();
  obj_folder = "./";
}

MainWindow::~MainWindow() {
  save_options();
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  ui->openGLWidget->color_back =
      QColorDialog::getColor(QColor::fromRgbF(1, 1, 1), this);
  ui->openGLWidget->update();
}

void MainWindow::open_file() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open OBJ file"), obj_folder, tr("OBJ Files (*.obj)"));
  std::string filename_std = filename.toStdString();
  const char *filaname_c = filename_std.c_str();
  int res =
      open_and_read_file((char *)filaname_c, &ui->openGLWidget->cordination);
  QFile fn(filename);
  QString path = fn.fileName();
  QString file = path.section("/", -1, -1);
  obj_folder = filename.remove(file);
  if (res == 0) {
    this->setWindowTitle("3DViewer 1.0 (" + filename + ")");
    ui->label->setText("Файл : " + file);
    ui->label_2->setText(
        "Вершин : " +
        QString::number(ui->openGLWidget->cordination.count_vertices));
    ui->label_3->setText(
        "Ребер : " +
        QString::number(ui->openGLWidget->cordination.count_lines));
    s21_center(&ui->openGLWidget->cordination);
    ui->openGLWidget->update();
  } else {
    this->setWindowTitle("3DViewer 1.0");
    ui->label->setText("Ошибка открытия файла " + file);
    ui->label_2->setText("Вершин : -");
    ui->label_3->setText("Ребер : -");
    s21_delete(&ui->openGLWidget->cordination);
  }
}

void MainWindow::read_options() {
  QSettings settings(options_file, QSettings::IniFormat);
  ui->comboBox->setCurrentIndex(settings.value("type_proj", 0).toInt());
  ui->comboBox_2->setCurrentIndex(settings.value("type_line", 0).toInt());
  ui->comboBox_3->setCurrentIndex(settings.value("type_vert", 0).toInt());
  ui->spinBox_8->setValue(settings.value("size_line", 1).toInt());
  ui->spinBox_9->setValue(settings.value("size_vert", 1).toInt());
  ui->openGLWidget->color_back = QColor::fromRgbF(
              settings.value("color_back_r", 0).toFloat(),
              settings.value("color_back_g", 0).toFloat(),
              settings.value("color_back_b", 0).toFloat());
  ui->openGLWidget->color_line = QColor::fromRgbF(
              settings.value("color_line_r", 1).toFloat(),
              settings.value("color_line_g", 1).toFloat(),
              settings.value("color_line_b", 1).toFloat());
  ui->openGLWidget->color_vert = QColor::fromRgbF(
              settings.value("color_vert_r", 1).toFloat(),
              settings.value("color_vert_g", 1).toFloat(),
              settings.value("color_vert_b", 1).toFloat());
}

void MainWindow::save_options() {
  QSettings settings(options_file, QSettings::IniFormat);
  settings.setValue("type_proj", ui->comboBox->currentIndex());
  settings.setValue("type_line", ui->comboBox_2->currentIndex());
  settings.setValue("type_vert", ui->comboBox_3->currentIndex());
  settings.setValue("size_line", ui->spinBox_8->value());
  settings.setValue("size_vert", ui->spinBox_9->value());
  settings.setValue("color_back_r", ui->openGLWidget->color_back.redF());
  settings.setValue("color_back_g", ui->openGLWidget->color_back.greenF());
  settings.setValue("color_back_b", ui->openGLWidget->color_back.blueF());
  settings.setValue("color_line_r", ui->openGLWidget->color_line.redF());
  settings.setValue("color_line_g", ui->openGLWidget->color_line.greenF());
  settings.setValue("color_line_b", ui->openGLWidget->color_line.blueF());
  settings.setValue("color_vert_r", ui->openGLWidget->color_vert.redF());
  settings.setValue("color_vert_g", ui->openGLWidget->color_vert.greenF());
  settings.setValue("color_vert_b", ui->openGLWidget->color_vert.blueF());
}

void MainWindow::on_pushButton_11_clicked() {
  s21_rotation(&ui->openGLWidget->cordination,
               ui->spinBox_5->value() * M_PI / 180, 0, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_12_clicked() {
  s21_rotation(&ui->openGLWidget->cordination,
               -ui->spinBox_5->value() * M_PI / 180, 0, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_13_clicked() {
  s21_rotation(&ui->openGLWidget->cordination, 0,
               ui->spinBox_6->value() * M_PI / 180, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_14_clicked() {
  s21_rotation(&ui->openGLWidget->cordination, 0,
               -ui->spinBox_6->value() * M_PI / 180, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_15_clicked() {
  s21_rotation(&ui->openGLWidget->cordination, 0, 0,
               ui->spinBox_7->value() * M_PI / 180);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_16_clicked() {
  s21_rotation(&ui->openGLWidget->cordination, 0, 0,
               -ui->spinBox_7->value() * M_PI / 180);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_5_clicked() {
  s21_translation(&ui->openGLWidget->cordination,
                  (double)ui->spinBox->value() / 100, 0, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_3_clicked() {
  s21_translation(&ui->openGLWidget->cordination,
                  -(double)ui->spinBox->value() / 100, 0, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_4_clicked() {
  s21_translation(&ui->openGLWidget->cordination, 0,
                  (double)ui->spinBox_2->value() / 100, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_7_clicked() {
  s21_translation(&ui->openGLWidget->cordination, 0,
                  -(double)ui->spinBox_2->value() / 100, 0);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_6_clicked() {
  s21_translation(&ui->openGLWidget->cordination, 0, 0,
                  (double)ui->spinBox_3->value() / 100);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_8_clicked() {
  s21_translation(&ui->openGLWidget->cordination, 0, 0,
                  -(double)ui->spinBox_3->value() / 100);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_9_clicked() {
  s21_scaling(&ui->openGLWidget->cordination,
              1 - (double)ui->spinBox_4->value() / 100);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_10_clicked() {
  s21_scaling(&ui->openGLWidget->cordination,
              1 + (double)ui->spinBox_4->value() / 100);
  ui->openGLWidget->update();
}

void MainWindow::on_horizontalSlider_sliderPressed() {
  slider_position_x1 = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  s21_rotation(
      &ui->openGLWidget->cordination,
      (ui->horizontalSlider->value() - slider_position_x1) * M_PI / 180, 0, 0);
  ui->openGLWidget->update();
  slider_position_x1 = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_2_sliderPressed() {
  slider_position_y1 = ui->horizontalSlider_2->value();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  s21_rotation(
      &ui->openGLWidget->cordination, 0,
      (ui->horizontalSlider_2->value() - slider_position_y1) * M_PI / 180, 0);
  ui->openGLWidget->update();
  slider_position_y1 = ui->horizontalSlider_2->value();
}

void MainWindow::on_horizontalSlider_3_sliderPressed() {
  slider_position_z1 = ui->horizontalSlider_3->value();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value) {
  s21_rotation(
      &ui->openGLWidget->cordination, 0, 0,
      (ui->horizontalSlider_3->value() - slider_position_z1) * M_PI / 180);
  ui->openGLWidget->update();
  slider_position_z1 = ui->horizontalSlider_3->value();
}

void MainWindow::on_horizontalSlider_4_sliderPressed() {
  slider_position_x2 = ui->horizontalSlider_4->value();
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value) {
  s21_translation(
      &ui->openGLWidget->cordination,
      ((double)ui->horizontalSlider_4->value() - slider_position_x2) / 100, 0,
      0);
  ui->openGLWidget->update();
  slider_position_x2 = ui->horizontalSlider_4->value();
}

void MainWindow::on_horizontalSlider_5_sliderPressed() {
  slider_position_y2 = ui->horizontalSlider_5->value();
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value) {
  s21_translation(
      &ui->openGLWidget->cordination, 0,
      ((double)ui->horizontalSlider_5->value() - slider_position_y2) / 100, 0);
  ui->openGLWidget->update();
  slider_position_y2 = ui->horizontalSlider_5->value();
}

void MainWindow::on_horizontalSlider_6_sliderPressed() {
  slider_position_z2 = ui->horizontalSlider_6->value();
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value) {
  s21_translation(
      &ui->openGLWidget->cordination, 0, 0,
      ((double)ui->horizontalSlider_6->value() - slider_position_z2) / 100);
  ui->openGLWidget->update();
  slider_position_z2 = ui->horizontalSlider_6->value();
}

void MainWindow::on_pushButton_21_clicked() {
  s21_center(&ui->openGLWidget->cordination);
  ui->openGLWidget->update();
  ui->horizontalSlider_4->setValue(0);
  ui->horizontalSlider_5->setValue(0);
  ui->horizontalSlider_6->setValue(0);
}

void MainWindow::on_horizontalSlider_7_sliderPressed() {
  slider_position_zoom = ui->horizontalSlider_7->value();
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value) {
  s21_scaling(&ui->openGLWidget->cordination,
              (1 + (double)ui->horizontalSlider_7->value() / 100) /
                  (1 + (double)slider_position_zoom / 100));
  ui->openGLWidget->update();
  slider_position_zoom = ui->horizontalSlider_7->value();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  ui->openGLWidget->proection = index;
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index) {
  ui->openGLWidget->point_type = index;
  ui->openGLWidget->update();
}

void MainWindow::on_spinBox_9_valueChanged(int arg1) {
  ui->openGLWidget->point_size = arg1;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_18_clicked() {
  ui->openGLWidget->color_vert =
      QColorDialog::getColor(QColor::fromRgbF(1, 1, 1), this);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_17_clicked() {
  ui->openGLWidget->color_line =
      QColorDialog::getColor(QColor::fromRgbF(1, 1, 1), this);
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index) {
  ui->openGLWidget->line_type = index;
  ui->openGLWidget->update();
}

void MainWindow::on_spinBox_8_valueChanged(int arg1) {
  ui->openGLWidget->line_size = arg1;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_19_clicked() {
  QString fn = QApplication::applicationDirPath() + "/" +
      QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss.zzz") + "." +
      ui->comboBox_4->currentText();
  const std::string &tmp_1 = ui->comboBox_4->currentText().toStdString();
  const char *format = tmp_1.c_str();
  QImage screenshot = ui->openGLWidget->grabFramebuffer();
  qDebug() << fn;
  screenshot.save(fn, format);
}

void MainWindow::on_pushButton_20_clicked() {
  gif = new QGifImage();
  timer = new QTimer(this);
  gif->setDefaultDelay(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(save_frame()));
  timer->start(100);
  ui->pushButton_20->setEnabled(false);
  count_gif = 0;
}

void MainWindow::save_frame() {
  if (count_gif < 50) {
    QImage img = ui->openGLWidget->grabFramebuffer();
    QImage small = img.scaled(640, 480, Qt::IgnoreAspectRatio);
    gif->addFrame(small, 100);
    count_gif++;
  } else {
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(save_frame()));
    QString fn = QApplication::applicationDirPath() + "/" +
        QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss.zzz") +
        ".gif";
    gif->save(fn);
    delete gif;
    delete timer;
    ui->pushButton_20->setEnabled(true);
  }
}
