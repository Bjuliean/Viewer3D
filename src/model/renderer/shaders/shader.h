#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShader>

#include "../utils.h"

namespace s21 {
/*!
    \brief An interface that implements the Shader class.

    The program can work both with a shader that works exclusively with the model’s frame, 
    and with a shader that allows you to apply texture and use lighting. 
    Both shaders use slightly different algorithms, to solve this problem the "Strategy" pattern was applied.
*/
class IShader {
public:
    /*!
        Connecting the files of the selected shader.
    */
    virtual void InitializeShaders(QOpenGLShaderProgram *shader_program) = 0;
    /*!
        Loading parameters into the shader.
    */
    virtual void DesignateAttributes(QOpenGLShaderProgram *shader_program, MatrixData* matrix_data) = 0;
    virtual ~IShader() = default;

}; // IShader

/*!
    \brief Shader that works exclusively with the model's frame.
*/
class SimpleShader : public IShader {
public:
    SimpleShader() = default;
    void InitializeShaders(QOpenGLShaderProgram *shader_program) override;
    void DesignateAttributes(QOpenGLShaderProgram *shader_program, MatrixData* matrix_data) override;
    ~SimpleShader() override = default;

}; // SimpleShader

/*!
    \brief Shader that allows you to apply texture and work with lighting.
*/
class AdvancedShader : public IShader {
public:
    AdvancedShader() = default;
    void InitializeShaders(QOpenGLShaderProgram *shader_program) override;
    void DesignateAttributes(QOpenGLShaderProgram *shader_program, MatrixData* matrix_data) override;
    ~AdvancedShader() override = default;

}; // AdvancedShader

class Shader
{
public:
    Shader(MatrixData *data)
        : current_shader_(nullptr)
        , matrix_data_(data)
        , shader_program_()
    {
    }
    ~Shader() {
        if(current_shader_) delete current_shader_;
    }
    /*!
        Selecting a suitable algorithm.
    */
    int SetShaderStrategy(ShaderTypes type);
    /*!
        Loading parameters for the shader.
    */
    void DesignateAttributes();
    /*!
        Loading parameters for the shader.
    */
    void SetNewData(MatrixData *data);

private:
    /*!
        Stores the selected algorithm.
    */
    IShader* current_shader_;
    /*!
        Since matrix_data_ is just a pointer to data that comes from outside, there was a need to be able to change this data.
    */
    MatrixData *matrix_data_;
    /*!
        QT shader program.
    */
    QOpenGLShaderProgram shader_program_;
}; // Shader

}; // namespace s21

#endif // SHADER_H
