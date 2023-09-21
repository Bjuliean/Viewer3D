#include <gtest/gtest.h>
#include <vector>
#include "../model/parser/parser.h"
#include "../model/data/data.h"
#include "../model/data/objectdata.h"

TEST(TestV, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, -1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestV, Test2) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1};
  parser.ParseFile("tests/objects/_octahedron.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetPoints().Vector()[i], result[i]);
    
}

TEST(TestV, Test3) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 2, 0, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2};
  parser.ParseFile("tests/objects/_cube 2.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestV, Test4) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {0, 1, 0, -1, 0, -1, 1, 0, -1, 1, 0, 1, -1, 0, 1};
  parser.ParseFile("tests/objects/_pyramid.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestVT, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 0.333333, 1, 0.666667, 0.666667, 0.666667, 0.666667, 0.333333, 0.666667, 0, 0, 0.333333, 0, 0, 0.333333, 0, 0.333333, 1, 0, 1, 0, 0.666667, 0.333333, 0.333333, 0.333333, 0.666667, 1, 0};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetTextures().Vector()[i], result[i]);
}

TEST(TestVN, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {0, -1, 0, 0, 1, 0, 1, 0, 0, -0, 0, 1, -1, -0, -0, 0, 0, -1};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.VertexData().GetNormals().Vector()[i], result[i]);
}

TEST(TestIV, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetPoints().Vector()[i], result[i]);

}

TEST(TestIV, Test2) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 0, 0, 4, 4, 1, 2, 1, 1, 4, 4, 2, 3, 2, 2, 4, 4, 3, 0, 3, 3, 4, 4, 0, 0, 1, 1, 5, 5, 0, 1, 2, 2, 5, 5, 1, 2, 3, 3, 5, 5, 2, 3, 0, 0, 5, 5, 3};
  parser.ParseFile("tests/objects/_octahedron.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestIV, Test3) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0, 0, 1, 1, 3, 3, 0, 2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0};
  parser.ParseFile("tests/objects/_cube 2.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestIV, Test4) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {0, 1, 1, 2, 2, 0, 0, 2, 2, 3, 3, 0, 0, 3, 3, 4, 4, 0, 0, 4, 4, 1, 1, 0, 2, 1, 1, 3, 3, 2, 1, 4, 4, 3, 3, 1};
  parser.ParseFile("tests/objects/_pyramid.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetPoints().Vector()[i], result[i]);
}

TEST(TestIVT, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 2, 3, 1, 4, 5, 6, 7, 8, 8, 5, 4, 9, 10, 11, 12, 13, 11, 4, 1, 3, 14, 1, 5, 12, 6, 8, 12, 8, 4, 13, 9, 11, 6, 12, 11};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetTextures().Vector()[i], result[i]);
}

TEST(TestIVN, Test1) {
  s21::Parser parser;
  s21::Data data;
  std::vector<float> result = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6};
  parser.ParseFile("tests/objects/_cube.obj", data);
  for(size_t i = 0; i < result.size(); ++i)
    EXPECT_FLOAT_EQ(data.IndexData().GetNormals().Vector()[i], result[i]);
}

TEST(TestSupport, Test1) {
    s21::Data data;
    data.GlobalReserve(30);
    EXPECT_EQ(data.VertexData().GetPoints().Vector().capacity(), 30);
    data.VertexData().GetPoints().Push(1);
    data.VertexData().GetTextures().Push(1);
    data.VertexData().GetNormals().Push(1);
    EXPECT_EQ(data.VertexData().GetPoints().Size(), 1);
    EXPECT_EQ(data.VertexData().GetTextures().Size(), 1);
    EXPECT_EQ(data.VertexData().GetNormals().Size(), 1);
    EXPECT_EQ(data.VertexData().GetPoints().MatrixRepresentation(0, 0), 1);
    EXPECT_EQ(data.VertexData().GetTextures().MatrixRepresentation(0, 0), 1);
    EXPECT_EQ(data.VertexData().GetNormals().MatrixRepresentation(0, 0), 1);
    EXPECT_EQ(data.VertexData().GetPoints().RowsSize(), 0);
    EXPECT_EQ(data.VertexData().GetTextures().RowsSize(), 0);
    EXPECT_EQ(data.VertexData().GetNormals().RowsSize(), 0);
    data.VertexData().GetPoints().Pop();
    EXPECT_TRUE(data.VertexData().GetPoints().Vector().empty());
    data.Clear();
    EXPECT_TRUE(data.VertexData().GetTextures().Vector().empty());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}