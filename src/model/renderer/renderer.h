#ifndef RENDERER_H
#define RENDERER_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMouseEvent>

#include "../data/data.h"
#include "shaders/shader.h"
#include "matrixevents.h"

namespace s21 {

/*!
    \brief The class responsible for working with rendering.

    It was decided to classify work with rendering, shaders, and transformations as business logic.
*/
class Renderer : public QOpenGLWidget
{
public:
    Renderer(QWidget *parent = nullptr);
    ~Renderer();

    /*!
        Method for linking a class object and a widget.
    */
    void HandleData(Data& data, ButtonsData& buttons_data);
    /*!
        Calling an extraordinary frame update.
    */
    void Draw();
    /*!
        Shader selection.
    */
    void SetShaders(ShaderTypes shadertype);
    /*!
        Projection selection.
    */
    void SetProjectionMatrix(ProjectionMatrixTypes type);
    /*!
        Line color selection.
    */
    void SetLinesColor(QColor color);
    /*!
        Vertex color selection.
    */
    void SetDotsColor(QColor color);
    /*!
        Point size selection.
    */
    void SetPointSize(float val);
    /*!
        Texture path selection.
    */
    void TexturePath(std::string path);
    /*!
        Access to matrix data.
    */
    MatrixData& GetMatrixData() { return matrix_data_; }
    /*!
        Accessing matrix transformation data.
    */
    MatrixTransfromTools& GetMatrixTransformTools() { return matrix_transform_tools_; }
    /*!
        Reset matrix transformations.
    */
    void Reset();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    /*!
        Data in raw form, after parsing.
    */
    Data *data_;
    /*!
        Transformation data entered through the user interface.
    */
    ButtonsData *buttons_data_;
    /*!
        Matrix transformation data.
    */
    MatrixTransfromTools matrix_transform_tools_;
    /*!
        Matrix data.
    */
    MatrixData matrix_data_;
    /*!
        An object that implements a system for working with shaders.
    */
    Shader shader_;
    /*!
        An object that handles mouse clicks.
    */
    MatrixEvents matrix_events_;
    /*!
        Whether the object was loaded after the program started.
    */
    bool is_loaded_;
    /*!
        Shaders draw with different primitives, a variable is needed to store this type.
    */
    int draw_type_;
    /*!
        Widget window width.
    */
    float window_width_;
    /*!
        Widget window height.
    */
    float window_height_;
    /*!
        Path to texture.
    */
    std::string texture_path_;

    /*!
        Loading raw data after parsing into buffers for subsequent more convenient work with them.
    */
    void TransferDataToBuffers();
    /*!
        Loading shader parameters.
    */
    void DesignateAttributes();
    /*!
        Loading texture.
    */
    void LoadTexture();

}; // Renderer

}; // namespace s21

#endif // RENDERER_H
