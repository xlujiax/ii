#pragma once

#include <vector>
#include <cstdlib>
#include <cassert>

class loader
{
  std::vector<float> v;
public:
  float* vertexData;
  int triangles;
  void load()
  {
    const int width = 30;
    const int height = 30;

    float m[width][height];
    for(int i = 0; i < width; ++i)
      for(int j = 0; j < height; ++j)
        m[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    v.reserve(3 * 2 * (width - 1) * (height - 1));
    for(int i = 0; i < width - 1; ++i)
      for(int j = 0; j < height - 1; ++j)
      {
        v.push_back(m[i][j]);
        v.push_back(m[i + 1][j]);
        v.push_back(m[i][j + 1]);
        
        v.push_back(m[i + 1][j]);
        v.push_back(m[i + 1][j + 1]);
        v.push_back(m[i][j + 1]);
      }

    vertexData = &v[0];
    triangles = v.size() / 3;
    assert(v.size() == 3 * 2 * (width - 1) * (height - 1));
  }
};

