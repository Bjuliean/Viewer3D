#ifndef DATA_H
#define DATA_H

#include "objectdata.h"

namespace s21 {

/*!
    \brief The class is a global storage that provides work with all the output of the parser.
*/
class Data {
public:
    Data() = default;
    ~Data() = default;
    /*!
        Access to data with coordinates.
    */
    ObjectData<float>& VertexData() { return vertex_data_; }
    /*!
        Access to data with indicies.
    */
    ObjectData<unsigned int>& IndexData() { return index_data_; }
    /*!
        Access to the maximum coordinate module.
    */
    float& MaxPoint() { return max_point_; }
    /*!
        Clearing all data.
    */
    void Clear();
    /*!
        Reserves a specified amount of memory for all data.
    */
    void GlobalReserve(size_t val);

private:
    /*!
        Data with coordinates.
    */
    s21::ObjectData<float> vertex_data_;
    /*!
        Data with indicies.
    */
    s21::ObjectData<unsigned int> index_data_;
    /*!
        Stores the maximum value of the modulus of the vertex coordinate, for subsequent calculation of the coefficient for data normalization.
    */
    float max_point_;

}; // class Data

}; // namespace s21

#endif // DATA_H
