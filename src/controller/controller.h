#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

/*! \brief Base class of the controller. */
class Controller {
public:
    Controller() = default;
    ~Controller() = default;

    /*! Parse the file. */
    void LoadFile(std::string path);
    /*! Access to data obtained as a result of parsing. */
    Data& Data();
    /*! Passing a widget to bind to a renderer_ object. */
    void SetRenderWindow(Renderer* window);
    /*! Extraordinary frame rendering. */
    void Draw();

    /*! Movement along the x axis. */
    void MoveX(float val);
    /*! Movement along the y axis. */
    void MoveY(float val);
    /*! Movement along the z axis. */
    void MoveZ(float val);

    /*! Rotation along the x axis. */
    void RotateX(float val);
    /*! Rotation along the y axis. */
    void RotateY(float val);
    /*! Rotation along the z axis. */
    void RotateZ(float val);

    /*! Selecting projection. */
    void SetProjection(ProjectionMatrixTypes type);
    /*! Selecting shader. */
    void SetShader(ShaderTypes type);

    /*! Selecting widget background color. */
    void SetBackgroundColor(QColor color);
    /*! Selecting lines color. */
    void SetLinesColor(QColor color);
    /*! Selecting vertex color. */
    void SetDotsColor(QColor color);

    /*! Selecting vertex size. */
    void SetPointSize(float val);
    /*! Selecting vertices draw type. */
    void SetVerticesType(VerticesType type);
    /*! Selecting lines draw type. */
    void SetLinesType(LinesType type);
    /*! Selecting line size. */
    void SetLineSize(float val);

    /*! Number of polygons. */
    size_t TotalPolygons() { return model_.TotalPolygons(); }
    /*! Number of vertices. */
    size_t TotalVertices() { return model_.TotalVertices(); }

    /*! Selecting texture path. */
    void SetTexturePath(std::string path);
    /*! Access to model data. */
    Model& GetModel() { return model_; }
    /*! Reset transformations received from the user interface. */
    void ResetNonButtonData() { model_.Reset(); }

private:
    Model model_;

}; // Controller

}; // namespace s21

#endif // CONTROLLER_H
