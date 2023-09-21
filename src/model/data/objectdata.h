#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <vector>
#include <cstddef>

namespace s21 {

/*!
    \brief An abstract class that allows you to eliminate code duplication between the storage with coordinates of points and the storage with indexes.
*/
template <typename T>
class Information {
public:
    /*!
        Allows to use vector reserve.
    */
    void Reserve(size_t val) { data_.reserve(val); }
    /*!
        Allows to use vector push.
    */
    void Push(T val) { data_.push_back(val); }
    /*!
        Allows to use vector pop.
    */
    void Pop() { data_.pop_back(); }
    /*!
        Allows to use vector clear.
    */
    void Clear() { data_.clear(); }
    /*!
        Gives direct access to the vector.
    */
    std::vector<T>& Vector() { return data_; }
    /*!
        Allows to use vector size.
    */
    size_t Size() { return data_.size(); }
    /*!
        Allows you to determine the conditional number of rows.
    */
    virtual size_t RowsSize() = 0;
    /*!
        Allows you to access data as if it were in a matrix, using two indexes.
    */
    virtual T& MatrixRepresentation(size_t i, size_t z) = 0;

protected:
    std::vector<T> data_;

}; // Information

template <typename T>
class Points : public Information<T> {
public:
    Points() = default;
    ~Points() = default;

    size_t RowsSize() override { return this->Size() / 3; }
    T& MatrixRepresentation(size_t i, size_t z) override {
        size_t pos = (i * 3) + (z % 3);
        return pos <= this->data_.size() ? this->data_[pos] : this->data_[0];
    }

}; // Points

template <typename T>
class Textures : public Information<T> {
public:
    Textures() = default;
    ~Textures() = default;

    size_t RowsSize() override { return this->Size() / 2; }
    T& MatrixRepresentation(size_t i, size_t z) override {
        size_t pos = (i * 2) + (z % 2);
        return pos <= this->data_.size() ? this->data_[pos] : this->data_[0];
    }

}; // Textures

template <typename T>
class Normals : public Information<T> {
public:
    Normals() = default;
    ~Normals() = default;

    size_t RowsSize() override { return this->Size() / 3; }
    T& MatrixRepresentation(size_t i, size_t z) override {
        size_t pos = (i * 3) + (z % 3);
        return pos <= this->data_.size() ? this->data_[pos] : this->data_[0];
    }

}; // Normals

template <typename T>
class ObjectData {
public:
    ObjectData() = default;
    ~ObjectData() = default;
    /*!
        Gives access to vertex coordinates in the case of a vertex store, or access to vertex indices in the case of an index store.
    */
    Information<T>& GetPoints() { return points_coord_; }
    /*!
        Gives access to texture vertex coordinates in the case of a vertex store, or access to texture vertex indices in the case of an index store.
    */
    Information<T>& GetTextures() { return texture_coord_; }
    /*!
        Gives access to normals coordinates in the case of a vertex store, or access to normals indices in the case of an index store.
    */
    Information<T>& GetNormals() { return normal_; }
    /*!
        Performs clearing of the entire data group.
    */
    void Clear() {
        points_coord_.Clear();
        texture_coord_.Clear();
        normal_.Clear();
    }

private:
    /*!
        Vertex coordinates or indices.
    */
    Points<T> points_coord_;
    /*!
        Texture vertex coordinates or indices.
    */
    Textures<T> texture_coord_;
    /*!
        Normals coordinates or indices.
    */
    Normals<T> normal_;

}; // class ObjectData

}; // namespace s21

#endif // OBJECTDATA_H
