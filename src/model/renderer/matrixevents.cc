#include "matrixevents.h"

namespace s21 {

void MatrixEvents::InitMatrixEvents(
    Data *data, MatrixData *matrix_data,
    MatrixTransfromTools *matrix_transform_tools) {
  data_package_ = new DataPackage(data, matrix_data, matrix_transform_tools);
}

void MatrixEvents::SetMatrixEventType(ProjectionMatrixTypes projection_type) {
  switch (projection_type) {
    case Perspective:
      current_event_ = new PerspectiveEvents();
      break;
    case Ortho:
      current_event_ = new OrthoEvents();
    default:
      break;
  }
}

void MatrixEvents::Rotate(QMouseEvent *event) {
  QVector2D delta_pos = QVector2D(event->position()) -
                        data_package_->matrix_transform_tools_->mouse_pos_;
  data_package_->matrix_transform_tools_->mouse_pos_ =
      QVector2D(event->position());
  float angle = delta_pos.length() / 2.0;
  QVector3D axis = QVector3D(delta_pos.y(), delta_pos.x(), 0.0);
  data_package_->matrix_transform_tools_->rotation_ =
      QQuaternion::fromAxisAndAngle(axis, angle) *
      data_package_->matrix_transform_tools_->rotation_;
}

void MatrixEvents::Move(QMouseEvent *event) {
  current_event_->Move(event, data_package_->matrix_transform_tools_);
}

void MatrixEvents::Scale(QWheelEvent *event) {
  current_event_->Scale(event, data_package_);
}

void OrthoEvents::Move(QMouseEvent *event,
                       MatrixTransfromTools *matrix_transform_tools) {
  QVector2D delta_pos =
      QVector2D(event->position()) - matrix_transform_tools->mouse_pos_;
  matrix_transform_tools->movex_ +=
      (delta_pos.x()) / (1000 / -matrix_transform_tools->scale_);
  matrix_transform_tools->movey_ +=
      -((delta_pos.y()) / (1000 / -matrix_transform_tools->scale_));
  matrix_transform_tools->mouse_pos_ = QVector2D(event->position());
}

void OrthoEvents::Scale(QWheelEvent *event, DataPackage *data_package) {
  QVector<float> data_interlayer;
  if (event->angleDelta().y() > 0) {
    for (size_t i = 0; i < data_package->data_->VertexData().GetPoints().Size();
         ++i)
      data_package->data_->VertexData().GetPoints().Vector()[i] *=
          ORTHOSCALECOEF;

    for (size_t i = 0;
         i < data_package->data_->VertexData().GetTextures().Size(); ++i)
      data_package->data_->VertexData().GetTextures().Vector()[i] *=
          ORTHOSCALECOEF;

    for (size_t i = 0;
         i < data_package->data_->VertexData().GetNormals().Size(); ++i)
      data_package->data_->VertexData().GetNormals().Vector()[i] *=
          ORTHOSCALECOEF;
  }
  if (event->angleDelta().y() < 0) {
    for (size_t i = 0; i < data_package->data_->VertexData().GetPoints().Size();
         ++i)
      data_package->data_->VertexData().GetPoints().Vector()[i] /=
          ORTHOSCALECOEF;

    for (size_t i = 0;
         i < data_package->data_->VertexData().GetTextures().Size(); ++i)
      data_package->data_->VertexData().GetTextures().Vector()[i] /=
          ORTHOSCALECOEF;

    for (size_t i = 0;
         i < data_package->data_->VertexData().GetNormals().Size(); ++i)
      data_package->data_->VertexData().GetNormals().Vector()[i] /=
          ORTHOSCALECOEF;
  }

  for (size_t i = 0; i < data_package->data_->VertexData().GetPoints().Size();
       ++i)
    data_interlayer.append(
        data_package->data_->VertexData().GetPoints().Vector()[i]);

  for (size_t i = 0; i < data_package->data_->VertexData().GetTextures().Size();
       ++i)
    data_interlayer.append(
        data_package->data_->VertexData().GetTextures().Vector()[i]);

  for (size_t i = 0; i < data_package->data_->VertexData().GetNormals().Size();
       ++i)
    data_interlayer.append(
        data_package->data_->VertexData().GetNormals().Vector()[i]);

  data_package->matrix_data_->vertex_buffer_.create();
  data_package->matrix_data_->vertex_buffer_.bind();
  data_package->matrix_data_->vertex_buffer_.allocate(
      data_interlayer.constData(), data_interlayer.size() * sizeof(GLfloat));
  data_package->matrix_data_->vertex_buffer_.release();
}

void PerspectiveEvents::Move(QMouseEvent *event,
                             MatrixTransfromTools *matrix_transform_tools) {
  QVector2D delta_pos =
      QVector2D(event->position()) - matrix_transform_tools->mouse_pos_;
  matrix_transform_tools->movex_ +=
      (delta_pos.x()) / (1000 / -matrix_transform_tools->scale_);
  matrix_transform_tools->movey_ +=
      -((delta_pos.y()) / (1000 / -matrix_transform_tools->scale_));
  matrix_transform_tools->mouse_pos_ = QVector2D(event->position());
}

void PerspectiveEvents::Scale(QWheelEvent *event, DataPackage *data_package) {
  if (event->angleDelta().y() > 0) {
    if (std::fabs(data_package->matrix_transform_tools_->scale_) > MINPER * 100)
      data_package->matrix_transform_tools_->scale_ /=
          data_package->matrix_transform_tools_->scale_step_;
  }
  if (event->angleDelta().y() < 0) {
    if (std::fabs(data_package->matrix_transform_tools_->scale_) < MAXPER / 100)
      data_package->matrix_transform_tools_->scale_ *=
          data_package->matrix_transform_tools_->scale_step_;
  }
}

};  // namespace s21
