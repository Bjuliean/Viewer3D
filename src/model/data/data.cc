#include "data.h"

namespace s21 {

void Data::Clear() {
  vertex_data_.Clear();
  index_data_.Clear();
}

void Data::GlobalReserve(size_t val) {
  vertex_data_.GetNormals().Reserve(val);
  vertex_data_.GetPoints().Reserve(val);
  vertex_data_.GetTextures().Reserve(val);

  index_data_.GetNormals().Reserve(val);
  index_data_.GetPoints().Reserve(val);
  index_data_.GetTextures().Reserve(val);
}

};  // namespace s21