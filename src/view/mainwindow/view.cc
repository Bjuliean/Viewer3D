#include "view.h"

#include "ui_view.h"

namespace s21 {

view::view(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::view), cfgs_(nullptr) {
  ui->setupUi(this);
  controller_.SetRenderWindow(ui->widget);
  buttons_ = new ButtonsRegulator(ui);
  buttons_->AddObserver(this);
  this->setWindowTitle("3DViewer_V2.0");

  ui->doubleSpinBox_movex->setMinimum(-100);
  ui->doubleSpinBox_movex->setMaximum(100);
  ui->doubleSpinBox_movey->setMinimum(-100);
  ui->doubleSpinBox_movey->setMaximum(100);
  ui->doubleSpinBox_movez->setMinimum(-100);
  ui->doubleSpinBox_movez->setMaximum(100);

  ui->doubleSpinBox_rotatex->setMinimum(-100);
  ui->doubleSpinBox_rotatex->setMaximum(100);
  ui->doubleSpinBox_rotatey->setMinimum(-100);
  ui->doubleSpinBox_rotatey->setMaximum(100);
  ui->doubleSpinBox_rotatez->setMinimum(-100);
  ui->doubleSpinBox_rotatez->setMaximum(100);

  ui->doubleSpinBox_pointsize->setMinimum(0);
  ui->doubleSpinBox_pointsize->setMaximum(100);

  ui->spinBox_backupindex->setMinimum(0);
  ui->spinBox_backupindex->setMaximum(0);
  ui->spinBox_deleteindex->setMinimum(0);
  ui->spinBox_deleteindex->setMaximum(0);

  this->setFixedHeight(1080);
  this->setFixedWidth(1965);
  cfgs_ = new Memory(&controller_.GetModel());
}

view::~view() {
  SaveSettings();
  delete buttons_;
  delete cfgs_;
  delete ui;
}

void view::Update() {
  controller_.LoadFile(ui->lineEdit_filenametext->text().toStdString());
  ui->lineEdit_totalvertext->setText(
      QString::number(controller_.TotalVertices()));
  ui->lineEdit_totalpoltext->setText(
      QString::number(controller_.TotalPolygons()));
  controller_.SetTexturePath(ui->lineEdit_texturepath->text().toStdString());

  controller_.MoveX(ui->doubleSpinBox_movex->value());
  controller_.MoveY(ui->doubleSpinBox_movey->value());
  controller_.MoveZ(ui->doubleSpinBox_movez->value());
  controller_.RotateX(ui->doubleSpinBox_rotatex->value());
  controller_.RotateY(ui->doubleSpinBox_rotatey->value());
  controller_.RotateZ(ui->doubleSpinBox_rotatez->value());
  controller_.SetPointSize(ui->doubleSpinBox_pointsize->value());
  controller_.SetLineSize(ui->doubleSpinBox_linesize->value());
  switch (ui->comboBox_projection->currentIndex()) {
    case 0:
      controller_.SetProjection(s21::Perspective);
      break;
    case 1:
      controller_.SetProjection(s21::Ortho);
      break;
    default:
      break;
  }

  switch (ui->comboBox_shader->currentIndex()) {
    case 0:
      controller_.SetShader(s21::SimpleShaderType);
      break;
    case 1:
      controller_.SetShader(s21::AdvancedShaderType);
      break;
    default:
      break;
  }

  switch (ui->comboBox_verticestype->currentIndex()) {
    case 0:
      controller_.SetVerticesType(s21::NoVertices);
      break;
    case 1:
      controller_.SetVerticesType(s21::Square);
      break;
    case 2:
      controller_.SetVerticesType(s21::Circle);
      break;
    default:
      break;
  }

  switch (ui->comboBox_linetype->currentIndex()) {
    case 0:
      controller_.SetLinesType(s21::NoLines);
      break;
    case 1:
      controller_.SetLinesType(s21::Dotted);
      break;
    case 2:
      controller_.SetLinesType(s21::Solid);
      break;
    default:
      break;
  }

  int r = 0, g = 0, b = 0;
  std::sscanf(ui->pushButton_backgroundcolor->styleSheet().toStdString().data(),
              "background-color:rgb(%*d, %*d, %*d);\ncolor:rgb(%d, %d, %d);",
              &r, &g, &b);
  QColor bcolor(r, g, b);
  controller_.SetBackgroundColor(bcolor);

  std::sscanf(ui->pushButton_linescolor->styleSheet().toStdString().data(),
              "background-color:rgb(%*d, %*d, %*d);\ncolor:rgb(%d, %d, %d);",
              &r, &g, &b);
  QColor lcolor(r, g, b);
  controller_.SetLinesColor(lcolor);

  std::sscanf(ui->pushButton_verticescolor->styleSheet().toStdString().data(),
              "background-color:rgb(%*d, %*d, %*d);\ncolor:rgb(%d, %d, %d);",
              &r, &g, &b);
  QColor dcolor(r, g, b);
  controller_.SetDotsColor(dcolor);

  controller_.Draw();
}

void view::on_pushButton_savecfg_clicked() {
  ui->spinBox_backupindex->setMaximum(cfgs_->Backup());
  ui->spinBox_deleteindex->setMaximum(ui->spinBox_backupindex->maximum());
}

void view::on_pushButton_undocfg_clicked() {
  if (ui->spinBox_backupindex->value() > 0)
    cfgs_->Undo(ui->spinBox_backupindex->value() - 1);
  ButtonsData buttons_data(*controller_.GetModel().GetButtonsData());
  MatrixData matrix_data(*controller_.GetModel().GetMatrixData());
  ui->doubleSpinBox_movex->setValue(buttons_data.movex_);
  ui->doubleSpinBox_movey->setValue(buttons_data.movey_);
  ui->doubleSpinBox_movez->setValue(buttons_data.movez_);
  ui->doubleSpinBox_linesize->setValue(buttons_data.line_size_);
  ui->doubleSpinBox_pointsize->setValue(matrix_data.point_size_);
  ui->doubleSpinBox_rotatex->setValue(buttons_data.rotatex_);
  ui->doubleSpinBox_rotatey->setValue(buttons_data.rotatey_);
  ui->doubleSpinBox_rotatez->setValue(buttons_data.rotatez_);

  switch (buttons_data.lines_type_) {
    case s21::NoLines:
      ui->comboBox_linetype->setCurrentIndex(0);
      break;
    case s21::Dotted:
      ui->comboBox_linetype->setCurrentIndex(1);
      break;
    case s21::Solid:
      ui->comboBox_linetype->setCurrentIndex(2);
      break;
    default:
      break;
  }

  switch (buttons_data.vertices_type_) {
    case s21::NoVertices:
      ui->comboBox_verticestype->setCurrentIndex(0);
      break;
    case s21::Square:
      ui->comboBox_verticestype->setCurrentIndex(1);
      break;
    case s21::Circle:
      ui->comboBox_verticestype->setCurrentIndex(2);
      break;
    default:
      break;
  }

  ButtonsRegulator::SetButtonColor(ui->pushButton_backgroundcolor,
                                   buttons_data.background_color_);
  ButtonsRegulator::SetButtonColor(ui->pushButton_linescolor,
                                   matrix_data.lines_color_);
  ButtonsRegulator::SetButtonColor(ui->pushButton_verticescolor,
                                   matrix_data.dots_color_);

  Update();
}

void view::on_pushButton_deletecfg_clicked() {
  if (ui->spinBox_deleteindex->value() > 0)
    ui->spinBox_deleteindex->setMaximum(
        cfgs_->Delete(ui->spinBox_deleteindex->value() - 1));
  ui->spinBox_backupindex->setMaximum(ui->spinBox_deleteindex->maximum());
}

void view::on_pushButton_loadsettings_clicked() { LoadSettings(); }

void view::on_pushButton_reset_clicked() {
  ui->doubleSpinBox_movex->setValue(0);
  ui->doubleSpinBox_movey->setValue(0);
  ui->doubleSpinBox_movez->setValue(0);
  ui->doubleSpinBox_rotatex->setValue(0);
  ui->doubleSpinBox_rotatey->setValue(0);
  ui->doubleSpinBox_rotatez->setValue(0);
  ui->doubleSpinBox_linesize->setValue(1);
  ui->doubleSpinBox_pointsize->setValue(10);
  controller_.ResetNonButtonData();
  Update();
}

void view::SaveSettings() {
  settings_.setValue("movex", ui->doubleSpinBox_movex->value());
  settings_.setValue("movey", ui->doubleSpinBox_movey->value());
  settings_.setValue("movez", ui->doubleSpinBox_movez->value());
  settings_.setValue("rotatex", ui->doubleSpinBox_rotatex->value());
  settings_.setValue("rotatey", ui->doubleSpinBox_rotatey->value());
  settings_.setValue("rotatez", ui->doubleSpinBox_rotatez->value());
  settings_.setValue("linesize", ui->doubleSpinBox_linesize->value());
  settings_.setValue("pointsize", ui->doubleSpinBox_pointsize->value());
  settings_.setValue("projection", ui->comboBox_projection->currentIndex());
  settings_.setValue("shader", ui->comboBox_shader->currentIndex());
  settings_.setValue("verticestype", ui->comboBox_verticestype->currentIndex());
  settings_.setValue("linetype", ui->comboBox_linetype->currentIndex());
  settings_.setValue("file", ui->lineEdit_filenametext->text());
  settings_.setValue("verticescolor", ButtonsRegulator::GetButtonColor(
                                          ui->pushButton_verticescolor));
  settings_.setValue("linescolor", ButtonsRegulator::GetButtonColor(
                                       ui->pushButton_linescolor));
  settings_.setValue("backgroundcolor", ButtonsRegulator::GetButtonColor(
                                            ui->pushButton_backgroundcolor));
}

void view::LoadSettings() {
  ui->doubleSpinBox_movex->setValue(settings_.value("movex").toDouble());
  ui->doubleSpinBox_movey->setValue(settings_.value("movey").toDouble());
  ui->doubleSpinBox_movez->setValue(settings_.value("movez").toDouble());
  ui->doubleSpinBox_rotatex->setValue(settings_.value("rotatex").toDouble());
  ui->doubleSpinBox_rotatey->setValue(settings_.value("rotatey").toDouble());
  ui->doubleSpinBox_rotatez->setValue(settings_.value("rotatez").toDouble());
  ui->doubleSpinBox_linesize->setValue(settings_.value("linesize").toDouble());
  ui->doubleSpinBox_pointsize->setValue(
      settings_.value("pointsize").toDouble());
  ui->comboBox_projection->setCurrentIndex(
      settings_.value("projection").toInt());
  ui->comboBox_shader->setCurrentIndex(settings_.value("shader").toInt());
  ui->comboBox_verticestype->setCurrentIndex(
      settings_.value("verticestype").toInt());
  ui->comboBox_linetype->setCurrentIndex(settings_.value("linetype").toInt());
  ui->lineEdit_filenametext->setText(settings_.value("file").toString());
  ButtonsRegulator::SetButtonColor(
      ui->pushButton_backgroundcolor,
      settings_.value("backgroundcolor").value<QColor>());
  ButtonsRegulator::SetButtonColor(
      ui->pushButton_linescolor, settings_.value("linescolor").value<QColor>());
  ButtonsRegulator::SetButtonColor(
      ui->pushButton_verticescolor,
      settings_.value("verticescolor").value<QColor>());
  Update();
}

ButtonsRegulator::ButtonsRegulator(Ui::view *ui)
    : observers_(),
      uiwindow_(ui),
      timer_(),
      gif_(),
      gif_image_(),
      gif_time_(0) {
  connect(ui->pushButton_loadfile, SIGNAL(clicked()), this, SLOT(LoadFile()));
  connect(ui->pushButton_loadtexture, SIGNAL(clicked()), this,
          SLOT(LoadTexture()));
  connect(ui->doubleSpinBox_movex, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_movey, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_movez, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_rotatex, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_rotatey, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_rotatez, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_pointsize, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->doubleSpinBox_linesize, SIGNAL(valueChanged(double)), this,
          SLOT(InitiatorButtons()));
  connect(ui->comboBox_projection, SIGNAL(currentIndexChanged(int)), this,
          SLOT(InitiatorButtons()));
  connect(ui->comboBox_shader, SIGNAL(currentIndexChanged(int)), this,
          SLOT(InitiatorButtons()));
  connect(ui->comboBox_verticestype, SIGNAL(currentIndexChanged(int)), this,
          SLOT(InitiatorButtons()));
  connect(ui->comboBox_linetype, SIGNAL(currentIndexChanged(int)), this,
          SLOT(InitiatorButtons()));
  connect(ui->pushButton_backgroundcolor, SIGNAL(clicked()), this,
          SLOT(ChangeBackgroundColor()));
  connect(ui->pushButton_linescolor, SIGNAL(clicked()), this,
          SLOT(ChangeLinesColor()));
  connect(ui->pushButton_verticescolor, SIGNAL(clicked()), this,
          SLOT(ChangeVerticesColor()));
  connect(ui->pushButton_savescr, SIGNAL(clicked()), this,
          SLOT(SaveScreenshot()));
  connect(ui->pushButton_savegif, SIGNAL(clicked()), this, SLOT(SaveGif()));
}

void ButtonsRegulator::SetButtonColor(QPushButton *button, QColor color) {
  int r = 0, g = 0, b = 0;
  std::sscanf(button->styleSheet().toStdString().data(),
              "background-color:rgb(%d, %d, %d);\ncolor:rgb(%*d, %*d, %*d);",
              &r, &g, &b);
  char style[255];
  std::sprintf(style,
               "background-color:rgb(%d, %d, %d);\ncolor:rgb(%d, %d, %d);", r,
               g, b, color.red(), color.green(), color.blue());
  button->setStyleSheet(QString(style));
}

QColor ButtonsRegulator::GetButtonColor(QPushButton *button) {
  int r = 0, g = 0, b = 0;
  std::sscanf(button->styleSheet().toStdString().data(),
              "background-color:rgb(%*d, %*d, %*d);\ncolor:rgb(%d, %d, %d);",
              &r, &g, &b);
  return QColor(r, g, b);
}

void ButtonsRegulator::SaveScreenshot() {
  QString screen = QFileDialog::getSaveFileName(nullptr, "Save screen as:", "",
                                                "*.jpeg;;*.bmp");
  if (screen != nullptr) {
    QString cur_type = screen.contains(".bmp") ? "BMP" : "JPEG";
    QFile file(screen);
    file.open(QIODevice::WriteOnly);
    QRect rect(0, 0, uiwindow_->widget->width() * 2,
               uiwindow_->widget->height() * 2);
    QPixmap map = uiwindow_->widget->grab(rect);
    map.copy(rect).toImage().save(&file, cur_type.toStdString().c_str());
  }
}

void ButtonsRegulator::SaveGif() {
  uiwindow_->pushButton_savegif->setEnabled(false);
  timer_ = new QTimer;
  connect(timer_, SIGNAL(timeout()), this, SLOT(TimerFlow()));
  gif_image_ = new QImage[50];
  gif_ = new QGifImage;
  SetButtonColor(uiwindow_->pushButton_savegif, QColor(0, 120, 0));
  timer_->start(100);
}

void ButtonsRegulator::TimerFlow() {
  if (gif_time_ < 50) {
    gif_image_[gif_time_] = uiwindow_->widget->grab().toImage();
    ++gif_time_;
  } else {
    for (size_t i = 0; i < gif_time_; ++i) {
      gif_->addFrame(gif_image_[i], 0);
    }
    QString date_time =
        QDateTime::currentDateTime().toString("dd.MM.yy_HH.mm.ss_zzz");
    QString file_name = QFileDialog::getSaveFileName(
        nullptr, "Save GIF", "GIF_" + date_time, "GIF (*.gif)");
    if (!file_name.isEmpty()) gif_->save(file_name);
    timer_->stop();
    delete timer_;
    delete[] gif_image_;
    delete gif_;
    gif_time_ = 0;
    uiwindow_->pushButton_savegif->setEnabled(true);
    SetButtonColor(uiwindow_->pushButton_savegif, QColor(80, 2, 2));
  }
}

void ButtonsRegulator::ChangeBackgroundColor() {
  QColor nw = QColorDialog::getColor(nullptr);
  SetButtonColor(uiwindow_->pushButton_backgroundcolor, nw);
  Notify();
}

void ButtonsRegulator::ChangeLinesColor() {
  QColor nw = QColorDialog::getColor(nullptr);
  SetButtonColor(uiwindow_->pushButton_linescolor, nw);
  Notify();
}

void ButtonsRegulator::ChangeVerticesColor() {
  QColor nw = QColorDialog::getColor(nullptr);
  SetButtonColor(uiwindow_->pushButton_verticescolor, nw);
  Notify();
}

void ButtonsRegulator::InitiatorButtons() { Notify(); }

void ButtonsRegulator::LoadFile() {
  uiwindow_->lineEdit_filenametext->setText(QFileDialog::getOpenFileName());
  Notify();
}

void ButtonsRegulator::LoadTexture() {
  uiwindow_->lineEdit_texturepath->setText(QFileDialog::getOpenFileName());
  Notify();
}

};  // namespace s21
