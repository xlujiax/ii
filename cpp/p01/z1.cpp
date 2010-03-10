#include <iostream>
#include <stdexcept>

template <
  typename T,
  int Size,
  bool Overwrite = false
  >
  class ring_buffer
{
  T arr[Size];
  int begin;
  int end;

  inline int pre_inc(int& v);
  inline int post_inc(int& v);
  inline int next(const int& v) const;
public:
  ring_buffer();
  void push( const T& );
  bool empty() const;
  T pull();
};

template <
  typename T,
  int Size,
  bool Overwrite
  >
  ring_buffer<T, Size, Overwrite>::ring_buffer() : begin(0), end(0)
{

}

template <typename T, int Size, bool Overwrite>
  inline int ring_buffer<T, Size, Overwrite>::next(const int& v) const
{
  if(v == Size - 1)
    return 0;
  return v + 1;
}

template <typename T, int Size, bool Overwrite>
  inline int ring_buffer<T, Size, Overwrite>::pre_inc(int& v)
{
  v = next(v);
  return v;
}

template <typename T, int Size, bool Overwrite>
  inline int ring_buffer<T, Size, Overwrite>::post_inc(int& v)
{
  int temp = v;
  v = next(v);
  return temp;
}

template <typename T, int Size, bool Overwrite>
  void ring_buffer<T, Size, Overwrite>::push( const T& el )
{
  std::cout << begin << ' ' << end << std::endl;
  

  if(next(end) == begin)
  {
    if(!Overwrite)
      throw std::runtime_error("Attempt to push element to full ring buffer.");
    else
      pre_inc(begin);
  }
  
  arr[post_inc(end)] = el;
}
  
template <typename T, int Size, bool Overwrite>
  T ring_buffer<T, Size, Overwrite>::pull()
{
  return arr[post_inc(begin)];
}

template <typename T, int Size, bool Overwrite>
  bool ring_buffer<T, Size, Overwrite>::empty() const
{
  return begin == end;
}

int main()
{
  ring_buffer<int, 10, true> ri;

  //for(int i = 0; i < 20; ++i)
  {
    for(int j = 0; j < 10; ++j)
      ri.push(j);
    
    while(!ri.empty())
      std::cout << ri.pull() << std::endl;
    std::cout << std::endl;
  }
  return 0;
}
