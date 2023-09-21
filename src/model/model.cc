#include "model.h"

namespace s21 {

ModelMemento* Model::SaveData() {
  return new ModelMemento(buttons_data_, renderer_->GetMatrixData(),
                          renderer_->GetMatrixTransformTools());
}

void Model::RestoreData(IMemento* model_memento) {
  buttons_data_ = model_memento->GetButtonsData();
  renderer_->GetMatrixData() = model_memento->GetMatrixData();
  renderer_->GetMatrixTransformTools() =
      model_memento->GetMatrixTransfromTools();
}

void Model::LoadFile(std::string path) {
  if (path != buttons_data_.path_) {
    global_data_.Clear();
    global_data_.GlobalReserve(30000);
    if (!parser_.ParseFile(path, global_data_)) return;
    NormalizePoints();
    renderer_->HandleData(global_data_, buttons_data_);
    buttons_data_.path_ = path;
    vsize_ = parser_.TotalVertices();
    psize_ = parser_.TotalPolygons();
  }
}

void Model::NormalizePoints() {
  size_t coef = 0;
  while (global_data_.MaxPoint() > 10) {
    global_data_.MaxPoint() /= 10;
    coef++;
  }
  coef = std::pow(10, coef);
  for (size_t i = 0; i < global_data_.VertexData().GetPoints().Size(); ++i)
    global_data_.VertexData().GetPoints().Vector()[i] /= coef;

  for (size_t i = 0; i < global_data_.VertexData().GetTextures().Size(); ++i)
    global_data_.VertexData().GetTextures().Vector()[i] /= coef;

  for (size_t i = 0; i < global_data_.VertexData().GetNormals().Size(); ++i)
    global_data_.VertexData().GetNormals().Vector()[i] /= coef;
}

void Model::SetRenderWindow(Renderer* window) { renderer_ = window; }

void Model::Draw() { renderer_->Draw(); }

void Model::MoveX(float val) { buttons_data_.movex_ = val; }

void Model::MoveY(float val) { buttons_data_.movey_ = val; }

void Model::MoveZ(float val) { buttons_data_.movez_ = val; }

void Model::RotateX(float val) { buttons_data_.rotatex_ = val; }

void Model::RotateY(float val) { buttons_data_.rotatey_ = val; }

void Model::RotateZ(float val) { buttons_data_.rotatez_ = val; }

void Model::SetProjection(ProjectionMatrixTypes type) {
  renderer_->SetProjectionMatrix(type);
}

void Model::SetShader(ShaderTypes type) { renderer_->SetShaders(type); }

void Model::SetBackgroundColor(QColor color) {
  buttons_data_.background_color_ = color;
  Draw();
}

void Model::SetLinesColor(QColor color) {
  renderer_->SetLinesColor(color);
  Draw();
}

void Model::SetDotsColor(QColor color) {
  renderer_->SetDotsColor(color);
  Draw();
}

void Model::SetPointSize(float val) {
  renderer_->SetPointSize(val);
  Draw();
}

void Model::SetVerticesType(VerticesType type) {
  buttons_data_.vertices_type_ = type;
}

void Model::SetLinesType(LinesType type) { buttons_data_.lines_type_ = type; }

void Model::SetLineSize(float val) { buttons_data_.line_size_ = val; }

void Model::SetTexturePath(std::string path) { renderer_->TexturePath(path); }

};  // namespace s21
