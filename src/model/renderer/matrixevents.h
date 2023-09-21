#ifndef MATRIXEVENTS_H
#define MATRIXEVENTS_H

#include <QMouseEvent>

#include "utils.h"

namespace s21 {
/*!
    \brief In order not to violate the structure of the pattern, it was decided to transmit some data as a whole pool.
*/
struct DataPackage {
    DataPackage(Data* data, MatrixData* matrix_data, MatrixTransfromTools* matrix_transform_tools)
        : data_(data)
        , matrix_data_(matrix_data)
        , matrix_transform_tools_(matrix_transform_tools)
    {
    }
    ~DataPackage() = default;

    Data* data_;
    MatrixData* matrix_data_;
    MatrixTransfromTools* matrix_transform_tools_;

}; // DataPackage

/*!
    \brief A class that processes mouse signals.

    The program allows you to display the model in the form of perspective and orthogonal projections. 
    Both require slightly different algorithms. To solve this problem, the “Strategy” pattern was chosen.
*/
class IMatrixEvents {
public:
    virtual void Move(QMouseEvent *event, MatrixTransfromTools* matrix_transform_tools) = 0;
    virtual void Scale(QWheelEvent *event, DataPackage *data_package) = 0;
    virtual ~IMatrixEvents() = default;

}; // IMatrixEvents

/*!
    \brief Orthogonal projection algorithms.
*/
class OrthoEvents : public IMatrixEvents {
public:
    OrthoEvents() = default;
    ~OrthoEvents() = default;
    void Move(QMouseEvent *event, MatrixTransfromTools* matrix_transform_tools) override;
    void Scale(QWheelEvent *event, DataPackage *data_package) override;

}; // OrthoEvents

/*!
    \brief Perspective projection algorithms.
*/
class PerspectiveEvents : public IMatrixEvents {
public:
    PerspectiveEvents() = default;
    ~PerspectiveEvents() = default;
    void Move(QMouseEvent *event, MatrixTransfromTools* matrix_transform_tools) override;
    void Scale(QWheelEvent *event, DataPackage *data_package) override;

}; // PerspectiveEvents

/*!
    \brief A class that processes mouse input.
*/
class MatrixEvents
{
public:
    MatrixEvents()
        : data_package_(nullptr)
        , current_event_(nullptr)
    {
    }
    ~MatrixEvents() {
        if(data_package_) delete data_package_;
        if(current_event_) delete current_event_;
    }
    /*!
        Connecting data from outside, through pointers.
    */
    void InitMatrixEvents(Data* data, MatrixData* matrix_data, MatrixTransfromTools* matrix_transform_tools);
    /*!
        Algorithm selection.
    */
    void SetMatrixEventType(ProjectionMatrixTypes projection_type);
    /*!
        Rotate an object
    */
    void Rotate(QMouseEvent *event);
    /*!
        Move an object
    */
    void Move(QMouseEvent *event);
    /*!
        Scale an object
    */
    void Scale(QWheelEvent *event);

private:
    DataPackage* data_package_;
    IMatrixEvents* current_event_;

}; // MatrixEvents

} // namespace s21

#endif // MATRIXEVENTS_H
