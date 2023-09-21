#include "controller.h"

namespace s21 {

void Controller::LoadFile(std::string path) { model_.LoadFile(path); }

Data& Controller::Data() { return model_.GlobalData(); }

void Controller::SetRenderWindow(Renderer* window) {
  model_.SetRenderWindow(window);
}

void Controller::Draw() { model_.Draw(); }

void Controller::MoveX(float val) { model_.MoveX(val); }

void Controller::MoveY(float val) { model_.MoveY(val); }

void Controller::MoveZ(float val) { model_.MoveZ(val); }

void Controller::RotateX(float val) { model_.RotateX(val); }

void Controller::RotateY(float val) { model_.RotateY(val); }

void Controller::RotateZ(float val) { model_.RotateZ(val); }

void Controller::SetProjection(ProjectionMatrixTypes type) {
  model_.SetProjection(type);
}

void Controller::SetShader(ShaderTypes type) { model_.SetShader(type); }

void Controller::SetBackgroundColor(QColor color) {
  model_.SetBackgroundColor(color);
}

void Controller::SetLinesColor(QColor color) { model_.SetLinesColor(color); }

void Controller::SetDotsColor(QColor color) { model_.SetDotsColor(color); }

void Controller::SetPointSize(float val) { model_.SetPointSize(val); }

void Controller::SetVerticesType(VerticesType type) {
  model_.SetVerticesType(type);
}

void Controller::SetLinesType(LinesType type) { model_.SetLinesType(type); }

void Controller::SetLineSize(float val) { model_.SetLineSize(val); }

void Controller::SetTexturePath(std::string path) {
  model_.SetTexturePath(path);
}

};  // namespace s21
