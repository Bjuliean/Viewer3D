#include "parser.h"

namespace s21 {

bool Parser::ParseFile(std::string path, Data& data) {
  std::ifstream file;
  std::string str, substr;
  bool open_res = false;
  psize_ = vsize_ = 0;
  file.open(path);
  if (file.is_open()) {
    open_res = true;
    while (std::getline(file, str)) {
      if (str[0] == 'v' && str[1] == ' ') {
        PushPoints(str, data);
        vsize_++;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        PushIndicies(str, data);
        psize_++;
      }
      if (str[0] == 'v' && str[1] == 't') PushTextures(str, data);
      if (str[0] == 'v' && str[1] == 'n') PushNormals(str, data);
    }
  }
  return open_res;
}

void Parser::PushPoints(std::string str, Data& data) {
  char* lex = std::strtok(str.data(), " ");
  while (lex != NULL) {
    if (std::isdigit(lex[0]) || lex[0] == '-') {
      data.VertexData().GetPoints().Push(std::strtof(lex, nullptr));
      if (data.MaxPoint() <
          std::fabs(data.VertexData().GetPoints().Vector().back()))
        data.MaxPoint() =
            std::fabs(data.VertexData().GetPoints().Vector().back());
    }
    lex = std::strtok(NULL, " ");
  }
}

void Parser::PushTextures(std::string str, Data& data) {
  char* lex = std::strtok(str.data(), " ");
  while (lex != NULL) {
    if (std::isdigit(lex[0]) || lex[0] == '-')
      data.VertexData().GetTextures().Push(std::strtof(lex, nullptr));
    lex = std::strtok(NULL, " ");
  }
}

void Parser::PushNormals(std::string str, Data& data) {
  char* lex = std::strtok(str.data(), " ");
  while (lex != NULL) {
    if (std::isdigit(lex[0]) || lex[0] == '-')
      data.VertexData().GetNormals().Push(std::strtof(lex, nullptr));
    lex = std::strtok(NULL, " ");
  }
}

void Parser::PushIndicies(std::string str, Data& data) {
  buf_.clear();
  char* lex = std::strtok(str.data(), " ");
  while (lex != NULL) {
    if (std::isdigit(lex[0])) {
      buf_.push_back(lex);
    }
    lex = std::strtok(NULL, " ");
  }
  for (size_t i = 0; i < buf_.size(); ++i) {
    size_t counter = 0;
    lex = std::strtok(buf_[i].data(), "/");
    while (lex != NULL) {
      if (counter == 0) {
        data.IndexData().GetPoints().Push(std::stoi(lex) - 1);
        if (i > 0) data.IndexData().GetPoints().Push(std::stoi(lex) - 1);
      }
      if (counter == 1) data.IndexData().GetTextures().Push(std::stoi(lex));
      if (counter == 2) data.IndexData().GetNormals().Push(std::stoi(lex));
      lex = std::strtok(NULL, "/");
      counter++;
    }
    if (counter == 2) {
      data.IndexData().GetNormals().Push(
          data.IndexData().GetTextures().Vector().back());
      data.IndexData().GetTextures().Pop();
    }
  }
  data.IndexData().GetPoints().Push(std::stoi(buf_[0]) - 1);
}

};  // namespace s21
