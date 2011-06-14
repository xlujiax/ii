#include <iostream>

#include "numeric.hpp"
#include "dotproduct.hpp"
#include "vector.hpp"
#include "expression_operators.hpp"

int main(int, char*[])
{
  numeric<int>::reset_report();
  {
    vector<numeric<int>, 1> v;
    v[0] = 5;
    
    vector<numeric<int>, 1> u;
    u[0] = 1;
    
    vector<numeric<int>, 1> w;
    w[0] = 7;
    
    vector<numeric<int>, 1> r;
    r = v + u * w + (v*vector<numeric<int>, 1, scalar<numeric<int> > >(2));
    std::cout << r[0] << std::endl;
  }
  
  numeric<int>::usage_report();
  numeric<int>::reset_report();

  {
    vector<numeric<int>, 3> v;
    v[0] = 1;
    v[1] = 10;
    v[2] = 100;
    
    vector<numeric<int>, 3> w;
    w[0] = 2;
    w[1] = 20;
    w[2] = 200;

    std::cout << dot_product(v, w) << std::endl;
  }
  
  numeric<int>::usage_report();
  numeric<int>::reset_report();

  {
    vector<numeric<int>, 100> v;
    for(int i = 0; i < 100; ++i)
      v[i] = i * 100 + 9;

    vector<numeric<int>, 100> w;
    for(int i = 0; i < 100; ++i)
      w[i] = i * 10 + 9;
    
    vector<numeric<int>, 100> u;
    for(int i = 0; i < 100; ++i)
      u[i] = i + 9;

    vector<numeric<int>, 100> r;
    r = u - v / w + u * v;
    std::cout << (u - v / w + u * v)[3] << std::endl;
    std::cout << (u - v / w + u * v)[4] << std::endl;
  }
  
  numeric<int>::usage_report();
  numeric<int>::reset_report();
  
  {
    vector<numeric<int>, 100> v;
    for(int i = 0; i < 100; ++i)
      v[i] = i * 100 + 9;

    vector<numeric<int>, 100> w;
    for(int i = 0; i < 100; ++i)
      w[i] = i * 10 + 9;
    
    std::cout << (v+w)[3] << std::endl;

    std::cout << v.get_rep().name() << std::endl;
    std::cout << (v+w).get_rep().name() << std::endl;
    std::cout << (v*(w/v)).get_rep().name() << std::endl;
  }

  return 0;
}
