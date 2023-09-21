#ifndef UTILS_H
#define UTILS_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include "../data/data.h"

namespace s21 {

#define MINPER 0.0001f /// Responsible for the OpenGL working coordinate space.
#define MAXPER 10000.0f /// Responsible for the OpenGL working coordinate space.
#define ORTHOSCALECOEF 1.25f /// The scaling coefficient of an object during orthographic projection, in case of an attempt to bring the object closer.

enum ShaderTypes {
    SimpleShaderType,
    AdvancedShaderType
};

enum ProjectionMatrixTypes {
    Perspective,
    Ortho
};

enum VerticesType {
    NoVertices,
    Circle,
    Square
};

enum LinesType {
    NoLines,
    Solid,
    Dotted
};

/*! \brief Stores matrix transformation data. */
struct MatrixTransfromTools {
    MatrixTransfromTools()
        : mouse_pos_()
        , rotation_()
        , scale_(-5.0f)
        , scale_step_(1.5f)
        , movex_(0.0f)
        , movey_(0.0f)
    {
    }
    ~MatrixTransfromTools() = default;

    QVector2D mouse_pos_;
    QQuaternion rotation_;
    GLfloat scale_;
    GLfloat scale_step_;
    GLfloat movex_, movey_;

}; // MatrixTransfromTools

/*! \brief Stores matrix data. */
struct MatrixData {
    MatrixData()
        : projection_matrix_()
        , model_matrix_()
        , view_matrix_()
        , light_pos_(QVector4D(0.0, 0.0, 0.0, 1.0))
        , light_power_(2.5f)
        , texture_(nullptr)
        , vertex_buffer_(QOpenGLBuffer::VertexBuffer)
        , index_buffer_(QOpenGLBuffer::IndexBuffer)
        , step_to_v_textures_(0)
        , step_to_v_normals_(0)
        , lines_color_(1, 1, 1, 1)
        , dots_color_(1, 1, 1, 1)
        , primitive_color_(1, 1, 1, 1)
        , point_size_(10.0f)
    {
    }

    MatrixData(const MatrixData &other)
        : projection_matrix_(other.projection_matrix_)
        , model_matrix_(other.model_matrix_)
        , view_matrix_(other.view_matrix_)
        , light_pos_(other.light_pos_)
        , light_power_(other.light_power_)
        , texture_(other.texture_)
        , vertex_buffer_(other.vertex_buffer_)
        , index_buffer_(other.index_buffer_)
        , step_to_v_textures_(other.step_to_v_textures_)
        , step_to_v_normals_(other.step_to_v_normals_)
        , lines_color_(other.lines_color_)
        , dots_color_(other.dots_color_)
        , primitive_color_(other.primitive_color_)
        , point_size_(other.point_size_)
    {
    }

    ~MatrixData() = default;

    void Clear() {
        view_matrix_ = QMatrix4x4();
    }

    QMatrix4x4 projection_matrix_;
    QMatrix4x4 model_matrix_;
    QMatrix4x4 view_matrix_;
    QVector4D light_pos_;
    float light_power_;
    QOpenGLTexture *texture_;
    QOpenGLBuffer vertex_buffer_;
    QOpenGLBuffer index_buffer_;
    size_t step_to_v_textures_;
    size_t step_to_v_normals_;
    QColor lines_color_;
    QColor dots_color_;
    QColor primitive_color_;
    float point_size_;

}; // MatrixData

/*! \brief Stores transformation data received from the user interface. */
struct ButtonsData {
    ButtonsData()
        : path_()
        , movex_(0)
        , movey_(0)
        , movez_(0)
        , rotatex_(0)
        , rotatey_(0)
        , rotatez_(0)
        , background_color_(0, 0, 0, 1)
        , vertices_type_(NoVertices)
        , lines_type_(Solid)
        , line_size_(10.0f)
    {
    }
    ButtonsData(const ButtonsData &other)
        : path_(other.path_)
        , movex_(other.movex_)
        , movey_(other.movey_)
        , movez_(other.movez_)
        , rotatex_(other.rotatex_)
        , rotatey_(other.rotatey_)
        , rotatez_(other.rotatez_)
        , background_color_(other.background_color_)
        , vertices_type_(other.vertices_type_)
        , lines_type_(other.lines_type_)
        , line_size_(other.line_size_)

    {
    }

    ~ButtonsData() = default;

    std::string path_;
    float movex_, movey_, movez_;
    float rotatex_, rotatey_, rotatez_;
    QColor background_color_;
    VerticesType vertices_type_;
    LinesType lines_type_;
    float line_size_;

}; // ButtonsData

}; // namespace s21

#endif // UTILS_H
