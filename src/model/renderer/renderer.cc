#include "renderer.h"

#include <iostream>
namespace s21 {

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent),
      data_(nullptr),
      matrix_transform_tools_(),
      matrix_data_(),
      shader_(&matrix_data_),
      is_loaded_(false),
      draw_type_(0),
      window_width_(0),
      window_height_(0),
      texture_path_()

{}

Renderer::~Renderer() {}

void Renderer::HandleData(Data &data, ButtonsData &buttons_data) {
  Reset();
  data_ = &data;
  buttons_data_ = &buttons_data;
  TransferDataToBuffers();
  matrix_data_.step_to_v_textures_ =
      sizeof(GLfloat) * data_->VertexData().GetPoints().Size();
  matrix_data_.step_to_v_normals_ =
      sizeof(GLfloat) * data_->VertexData().GetPoints().Size() +
      sizeof(GLfloat) * data_->VertexData().GetTextures().Size();
  is_loaded_ = true;
  matrix_events_.InitMatrixEvents(data_, &matrix_data_,
                                  &matrix_transform_tools_);
}

void Renderer::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  SetShaders(SimpleShaderType);
  SetProjectionMatrix(Perspective);
}

void Renderer::resizeGL(int width, int height) {
  window_width_ = width;
  window_height_ = height;
}

void Renderer::paintGL() {
  if (is_loaded_) {
    glClearColor(buttons_data_->background_color_.redF(),
                 buttons_data_->background_color_.greenF(),
                 buttons_data_->background_color_.blueF(),
                 buttons_data_->background_color_.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (buttons_data_->lines_type_ != NoLines &&
        buttons_data_->line_size_ > 0) {
      glLineWidth(buttons_data_->line_size_);
      if (buttons_data_->lines_type_ == Dotted) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x3333);
      } else
        glDisable(GL_LINE_STIPPLE);
      matrix_data_.primitive_color_ = matrix_data_.lines_color_;
      DesignateAttributes();
      glDrawElements(draw_type_, data_->IndexData().GetPoints().Size(),
                     GL_UNSIGNED_INT, 0);
    }

    if (buttons_data_->vertices_type_ != NoVertices &&
        matrix_data_.point_size_ > 0) {
      glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
      if (buttons_data_->vertices_type_ == Circle)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);
      matrix_data_.primitive_color_ = matrix_data_.dots_color_;
      DesignateAttributes();
      glDrawElements(GL_POINTS, data_->IndexData().GetPoints().Size(),
                     GL_UNSIGNED_INT, 0);
    } else
      glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
  }
}

void Renderer::SetProjectionMatrix(ProjectionMatrixTypes type) {
  float coef = window_width_ / window_height_;
  matrix_data_.projection_matrix_.setToIdentity();
  switch (type) {
    case Perspective:
      matrix_data_.projection_matrix_.perspective(45, coef, MINPER, MAXPER);
      matrix_events_.SetMatrixEventType(type);
      break;
    case Ortho:
      float right = 0, left = 0, top = 0, bottom = 0;
      left = (-coef * 3) * 3;
      right = -left;
      bottom = -coef * 3;
      top = -bottom;
      matrix_data_.projection_matrix_.ortho(
          left / coef, right / coef, bottom / coef, top / coef, MINPER, MAXPER);
      matrix_events_.SetMatrixEventType(type);
      break;
  }
  update();
}

void Renderer::SetShaders(ShaderTypes shadertype) {
  draw_type_ = shader_.SetShaderStrategy(shadertype);
  update();
}

void Renderer::DesignateAttributes() {
  matrix_data_.view_matrix_.setToIdentity();
  matrix_data_.view_matrix_.translate(
      matrix_transform_tools_.movex_ + buttons_data_->movex_,
      matrix_transform_tools_.movey_ + buttons_data_->movey_,
      matrix_transform_tools_.scale_ + buttons_data_->movez_);
  QVector3D axis = QVector3D(buttons_data_->rotatex_, buttons_data_->rotatey_,
                             buttons_data_->rotatez_);
  matrix_data_.view_matrix_.rotate(
      matrix_transform_tools_.rotation_ *
      QQuaternion::fromAxisAndAngle(axis, axis.length()));
  matrix_data_.model_matrix_.setToIdentity();
  shader_.DesignateAttributes();
  matrix_data_.index_buffer_.bind();
}

void Renderer::TransferDataToBuffers() {
  QVector<float> data_interlayer;

  for (size_t i = 0; i < data_->VertexData().GetPoints().Size(); ++i)
    data_interlayer.append(data_->VertexData().GetPoints().Vector()[i]);

  for (size_t i = 0; i < data_->VertexData().GetTextures().Size(); ++i)
    data_interlayer.append(data_->VertexData().GetTextures().Vector()[i]);

  for (size_t i = 0; i < data_->VertexData().GetNormals().Size(); ++i)
    data_interlayer.append(data_->VertexData().GetNormals().Vector()[i]);

  matrix_data_.vertex_buffer_.create();
  matrix_data_.vertex_buffer_.bind();
  matrix_data_.vertex_buffer_.allocate(
      data_interlayer.constData(), data_interlayer.size() * sizeof(GLfloat));
  matrix_data_.vertex_buffer_.release();

  matrix_data_.index_buffer_.create();
  matrix_data_.index_buffer_.bind();
  matrix_data_.index_buffer_.allocate(
      data_->IndexData().GetPoints().Vector().data(),
      data_->IndexData().GetPoints().Size() * sizeof(GLuint));
  matrix_data_.index_buffer_.release();

  LoadTexture();
}

void Renderer::TexturePath(std::string path) {
  texture_path_ = path;
  LoadTexture();
}

void Renderer::LoadTexture() {
  matrix_data_.texture_ = new QOpenGLTexture(
      QImage(QString::fromStdString(texture_path_.empty() ? ":/cube.png"
                                                          : texture_path_))
          .mirrored());
  matrix_data_.texture_->setMagnificationFilter(QOpenGLTexture::Nearest);
  matrix_data_.texture_->setMagnificationFilter(QOpenGLTexture::Linear);
  matrix_data_.texture_->setWrapMode(QOpenGLTexture::Repeat);
}

void Renderer::mousePressEvent(QMouseEvent *event) {
  if ((event->buttons() == Qt::LeftButton ||
       event->buttons() == Qt::RightButton) &&
      is_loaded_)
    matrix_transform_tools_.mouse_pos_ = QVector2D(event->position());
  event->accept();
}

void Renderer::mouseMoveEvent(QMouseEvent *event) {
  if (is_loaded_) {
    if (event->buttons() == Qt::LeftButton) {
      matrix_events_.Rotate(event);
    }
    if (event->buttons() == Qt::RightButton) {
      matrix_events_.Move(event);
    }
  }
  update();
}

void Renderer::wheelEvent(QWheelEvent *event) {
  if (is_loaded_) matrix_events_.Scale(event);
  update();
}

void Renderer::Draw() { update(); }

void Renderer::SetLinesColor(QColor color) {
  matrix_data_.lines_color_ = color;
}

void Renderer::SetDotsColor(QColor color) { matrix_data_.dots_color_ = color; }

void Renderer::SetPointSize(float val) { matrix_data_.point_size_ = val; }

void Renderer::Reset() {
  matrix_data_.view_matrix_.setToIdentity();
  matrix_transform_tools_ = MatrixTransfromTools();
}

};  // namespace s21
