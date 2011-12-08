#pragma once

#include <vector>
#include <cstdlib>
#include <cassert>
#include <iostream>

class loader
{
  std::vector<float> v;
  static const int width = 1;
  static const int height = 1;

  float m[width][height];

  void gen_random_map()
  {
    for(int i = 0; i < width; ++i)
      for(int j = 0; j < height; ++j)
        m[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.1;
  }

  void push_vertex(int i, int j)
  {
    assert(i < width);
    assert(j < height);
    const float i_scaled = static_cast<float>(i) / static_cast<float>(width);
    const float j_scaled = static_cast<float>(j) / static_cast<float>(height);
    std::cout << i_scaled << ' ' << j_scaled << ' ' << m[i][j] << std::endl;
    v.push_back(i_scaled);
    v.push_back(j_scaled);
    v.push_back(m[i][j]);
  }
public:
  float* vertexData;
  int vertices;
  void load()
  {
    gen_random_map();
    // 3 wps * 3 wierzch * 2 trójkąty * liczba kwadratów na siatce
    v.reserve(3 * 3 * 2 * (width - 1) * (height - 1));
    for(int i = 0; i < width - 1; ++i)
      for(int j = 0; j < height - 1; ++j)
      {
        push_vertex(i,j);
        push_vertex(i + 1,j);
        push_vertex(i,j + 1);

        push_vertex(i + 1,j);
        push_vertex(i + 1,j + 1);
        push_vertex(i,j + 1);
      }

    vertexData = &v[0];
    vertices = v.size() / 3;
    //assert(v.size() == 3 * 3 * 2 * (width - 1) * (height - 1));
  }
};
