#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "data/data.h"
#include "parser/parser.h"
#include "renderer/renderer.h"

namespace s21 {

/*!
    \brief An interface that allows you to save current transformations.

    The program has a mechanic for storing the current transformations, 
    of the current session, in the form of a list. For convenient implementation, 
    the "Memento" pattern was used.
*/
class IMemento {
public:
    /*!
        Access transformations entered in the user interface.
    */
    virtual ButtonsData GetButtonsData() = 0;
    /*!
        Matrix data access.
    */
    virtual MatrixData GetMatrixData() = 0;
    /*!
        Matrix transformation data access.
    */
    virtual MatrixTransfromTools GetMatrixTransfromTools() = 0;
    virtual ~IMemento() = default;

}; // IMemento

/*! \brief Class-cell for storing data. */
class ModelMemento : public IMemento {
public:
    ModelMemento(ButtonsData buttons_data, MatrixData matrix_data, MatrixTransfromTools matrix_transform_tools)
        : buttons_data_(buttons_data)
        , matrix_data_(matrix_data)
        , matrix_transform_tools_(matrix_transform_tools)
    {
    }
    ~ModelMemento() = default;

    ButtonsData GetButtonsData() override { return buttons_data_; }
    MatrixData GetMatrixData() override { return matrix_data_; }
    MatrixTransfromTools GetMatrixTransfromTools() override { return matrix_transform_tools_; }

private:
    ButtonsData buttons_data_;
    MatrixData matrix_data_;
    MatrixTransfromTools matrix_transform_tools_;

}; // ModelMemento

/*! \brief Base class of the model. */
class Model {
public:
    Model()
        : global_data_()
        , parser_()
        , renderer_(nullptr)
        , buttons_data_()
        , psize_(0)
        , vsize_(0)
    {
    }
    ~Model() = default;
    /*!
        Access to all data obtained as a result of file parsing.
    */
    Data& GlobalData() { return global_data_; }
    /*!
        Method that initiates file parsing.
    */
    void LoadFile(std::string path);
    /*!
        A method that allows you to link a widget and a renderer_ object.
    */
    void SetRenderWindow(Renderer* window);
    /*!
        Method for out-of-order frame update.
    */
    void Draw();
    /*!
        Movement of the loaded model along the x axis.
    */
    void MoveX(float val);
    /*!
        Movement of the loaded model along the y axis.
    */
    void MoveY(float val);
    /*!
        Movement of the loaded model along the z axis.
    */
    void MoveZ(float val);
    /*!
        Rotation of the loaded model along the x axis.
    */
    void RotateX(float val);
    /*!
        Rotation of the loaded model along the y axis.
    */
    void RotateY(float val);
    /*!
        Rotation of the loaded model along the z axis.
    */
    void RotateZ(float val);
    /*!
        Selecting projection.
    */
    void SetProjection(ProjectionMatrixTypes type);
    /*!
        Selecting shader.
    */
    void SetShader(ShaderTypes type);
    /*!
        Selecting background color.
    */
    void SetBackgroundColor(QColor color);
    /*!
        Selecting lines color.
    */
    void SetLinesColor(QColor color);
    /*!
        Selecting dots color.
    */
    void SetDotsColor(QColor color);
    /*!
        Selecting point size.
    */
    void SetPointSize(float val);
    /*!
        Selecting vertices draw type.
    */
    void SetVerticesType(VerticesType type);
    /*!
        Selecting lines draw type.
    */
    void SetLinesType(LinesType type);
    /*!
        Selecting line size.
    */
    void SetLineSize(float val);
    /*!
        Access to the number of polygons.
    */
    size_t TotalPolygons() { return psize_; }
    /*!
        Access to the number of vertices.
    */
    size_t TotalVertices() { return vsize_; }
    /*!
        Choosing texture path.
    */
    void SetTexturePath(std::string path);
    /*!
        Allows you to save the current transformations.
    */
    ModelMemento* SaveData();
    /*!
        Allows you to restore transformations.
    */
    void RestoreData(IMemento *model_memento);
    /*!
        Access transformations entered through the user interface.
    */
    ButtonsData* GetButtonsData() { return &buttons_data_; }
    /*!
        Access matrix data.
    */
    MatrixData* GetMatrixData() { return &renderer_->GetMatrixData(); }
    /*!
        Reset transformations.
    */
    void Reset() { renderer_->Reset(); }

private:
    /*!
        Data obtained after parsing the file.
    */
    Data global_data_;
    /*!
        Parser object.
    */
    Parser parser_;
    /*!
        Renderer object.
    */
    Renderer *renderer_;
    /*!
        An object containing custom transformation data.
    */
    ButtonsData buttons_data_;
    /*!
        Number of polygons.
    */
    size_t psize_;
    /*!
        Number of vertices.
    */
    size_t vsize_;
    /*!
        Normalization of data obtained after parsing. The coordinates are shifted by values ​​up to one.
    */
    void NormalizePoints();

}; // class Model

/*! \brief A class that acts as a repository for data related to transformations. */
class Memory {
public:
    Memory(Model *model) : model_(model) {}
    ~Memory() = default;
    /*!
        Saves the current transformations.
    */
    size_t Backup() {
        if(history_.size() < 100)
            history_.push_back(model_->SaveData());
        return history_.size();
    }
    /*!
        Restores transformations by index.
    */
    void Undo(size_t index) {
        if(!history_.empty() && index < history_.size()) {
            model_->RestoreData(history_[index]);
        }
    }
    /*!
        Removes transformations by index.
    */
    size_t Delete(size_t index) {
        if(!history_.empty() && index < history_.size())
            history_.erase(history_.begin() + index);
        return history_.size();
    }

private:
    std::vector<IMemento*> history_;
    Model *model_;

}; // Memory

}; // namespace s21

#endif // MODEL_H
