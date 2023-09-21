#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cmath>

#include "../data/data.h"

namespace s21 {

/*!
    \brief The class responsible for parsing the file.
*/
class Parser {
public:
    Parser() : buf_(), vsize_(0), psize_(0) { buf_.reserve(20); }
    ~Parser() = default;

    /*!
        File parsing.
    */
    bool ParseFile(std::string path, Data& data);
    /*!
        Access to the number of polygons.
    */
    size_t TotalPolygons() { return psize_; }
    /*!
        Access to the number of vertices.
    */
    size_t TotalVertices() { return vsize_; }

private:
    /*!
        A buffer for convenient work with splitting a string with indexes. To speed up work, memory is reserved in advance.
    */
    std::vector<std::string> buf_;
    /*!
        Stores a count of vertices.
    */
    size_t vsize_;
    /*!
        Stores a count of the actual polygons of the file, in other words, counts the lines with indices in the file.
    */
    size_t psize_;

    /*!
       A helper method that sends data to the vertex store.
    */
    void PushPoints(std::string str, Data& data);
    /*!
       A helper method that sends data to the texture vertex store.
    */
    void PushTextures(std::string str, Data& data);
    /*!
       A helper method that sends data to the normals store.
    */
    void PushNormals(std::string str, Data& data);
    /*!
       A helper method that sends data to the indices store.
    */
    void PushIndicies(std::string str, Data& data);


}; // class Parser

}; // namespace s21

#endif // PARSER_H
