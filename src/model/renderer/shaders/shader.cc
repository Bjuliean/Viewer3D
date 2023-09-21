#include "shader.h"

namespace s21 {

int Shader::SetShaderStrategy(ShaderTypes type) {
  shader_program_.removeAllShaders();
  int draw_type = 0;
  if (current_shader_) delete current_shader_;
  switch (type) {
    case SimpleShaderType:
      current_shader_ = new SimpleShader();
      draw_type = GL_LINES;
      break;
    case AdvancedShaderType:
      current_shader_ = new AdvancedShader();
      draw_type = GL_QUADS;
      break;
    default:
      draw_type = 0;
      break;
  }
  current_shader_->InitializeShaders(&shader_program_);
  return draw_type;
}

void Shader::DesignateAttributes() {
  current_shader_->DesignateAttributes(&shader_program_, matrix_data_);
}

void Shader::SetNewData(MatrixData *nwdata) { matrix_data_ = nwdata; }

void AdvancedShader::InitializeShaders(QOpenGLShaderProgram *shader_program) {
  shader_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/vshader.vsh");
  shader_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/fshader.fsh");
  shader_program->link();
}

void AdvancedShader::DesignateAttributes(QOpenGLShaderProgram *shader_program,
                                         MatrixData *matrix_data) {
  matrix_data->texture_->bind(0);

  shader_program->bind();
  shader_program->setUniformValue("u_projectionMatrix",
                                  matrix_data->projection_matrix_);
  shader_program->setUniformValue("u_viewMatrix", matrix_data->view_matrix_);
  shader_program->setUniformValue("u_modelMatrix", matrix_data->model_matrix_);
  shader_program->setUniformValue("u_lightpos", matrix_data->light_pos_);
  shader_program->setUniformValue("u_lightpower", matrix_data->light_power_);

  shader_program->setUniformValue("u_texture", 0);

  matrix_data->vertex_buffer_.bind();
  int vloc = shader_program->attributeLocation("a_position");
  shader_program->enableAttributeArray(vloc);
  shader_program->setAttributeBuffer(vloc, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);

  int tloc = shader_program->attributeLocation("a_textcoord");
  shader_program->enableAttributeArray(tloc);
  shader_program->setAttributeBuffer(
      tloc, GL_FLOAT, matrix_data->step_to_v_textures_, 2, sizeof(GLfloat) * 2);

  int nloc = shader_program->attributeLocation("a_normal");
  shader_program->enableAttributeArray(nloc);
  shader_program->setAttributeBuffer(
      nloc, GL_FLOAT, matrix_data->step_to_v_normals_, 3, sizeof(GLfloat) * 3);
}

void SimpleShader::InitializeShaders(QOpenGLShaderProgram *shader_program) {
  shader_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/simplevshader.vsh");
  shader_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/simplefshader.fsh");
  shader_program->link();
}

void SimpleShader::DesignateAttributes(QOpenGLShaderProgram *shader_program,
                                       MatrixData *matrix_data) {
  matrix_data->texture_->bind(0);
  shader_program->bind();
  shader_program->setUniformValue("u_projectionMatrix",
                                  matrix_data->projection_matrix_);
  shader_program->setUniformValue("u_viewMatrix", matrix_data->view_matrix_);
  shader_program->setUniformValue("u_modelMatrix", matrix_data->model_matrix_);
  shader_program->setUniformValue("u_pointSize", matrix_data->point_size_);
  shader_program->setUniformValue(
      "u_primitive_color", QVector4D(matrix_data->primitive_color_.redF(),
                                     matrix_data->primitive_color_.greenF(),
                                     matrix_data->primitive_color_.blueF(),
                                     matrix_data->primitive_color_.alphaF()));

  matrix_data->vertex_buffer_.bind();
  int vloc = shader_program->attributeLocation("a_position");
  shader_program->enableAttributeArray(vloc);
  shader_program->setAttributeBuffer(vloc, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
}

};  // namespace s21
