#include <iostream>

#include "numeric.hpp"
#include "dotproduct.hpp"
#include "vector.hpp"
#include "expression_operators.hpp"

int main(int, char*[])
{
  numeric<int>::reset_report();

  {
    std::cout << "large computation doesn't peek because of lazy temporary value"<< std::endl;
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
  }
  
  numeric<int>::usage_report();

  numeric<int>::reset_report();

  {
    std::cout << "accessing only one cell of vector doesn't create rest of its cells"<< std::endl;
    vector<numeric<int>, 100> v;
    for(int i = 0; i < 100; ++i)
      v[i] = i * 100 + 9;

    vector<numeric<int>, 100> w;
    for(int i = 0; i < 100; ++i)
      w[i] = i * 10 + 9;
    
    vector<numeric<int>, 100> u;
    for(int i = 0; i < 100; ++i)
      u[i] = i + 9;

    std::cout << (u - v / w + u * v)[3] << std::endl;
  }
  
  numeric<int>::usage_report();
  
  numeric<int>::reset_report();
  
  {
    std::cout << "getting names of vector representation"<< std::endl;
    vector<numeric<int>, 100> v;
    for(int i = 0; i < 100; ++i)
      v[i] = i * 100 + 9;

    vector<numeric<int>, 100> w;
    for(int i = 0; i < 100; ++i)
      w[i] = i * 10 + 9;
    
    std::cout << v.get_rep().name() << std::endl;
    std::cout << (v+w).get_rep().name() << std::endl;
    std::cout << (v*(w/v)).get_rep().name() << std::endl;
  }

  numeric<int>::reset_report();
  {
    std::cout << "scalars are ugly" << std::endl;
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

    std::cout << "creating array of size " << dot_product(v, w) << std::endl;

    // below without ugly implicit cast
    int arr[dot_product(v, w).implicit_value()];
  }
  
  numeric<int>::usage_report();

  {
    vector<int, 3> v;
    v[0] = 1;
    v[1] = 10;
    v[2] = 100;
    
    vector<int, 3> w;
    w[0] = 2;
    w[1] = 20;
    w[2] = 200;

    std::cout << "creating array of size " << dot_product(v, w) << std::endl;

    int arr[dot_product(v, w)];
  }
  
  return 0;
}
