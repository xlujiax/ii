#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

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
  int count;

  static inline int pre_inc(int& v);
  static inline int post_inc(int& v);
  static inline int next(const int& v);
public:
  ring_buffer();
  void push( const T& );
  bool empty() const;
  T pull();

  void debug()
  {
    std::cout << begin << ":" << end << "(" << count << ") [ ";
    for(int i = 0; i < Size; ++i)
      std::cout << arr[i] << " ";
    std::cout << "]";

    std::cout << " { ";
    if(begin == end && count != 0)
    {
      std::cout << arr[begin] << ' ';

      for(int i = next(begin); i != end; pre_inc(i))
	std::cout << arr[i] << " ";
    }
    else
    {
      for(int i = begin; i != end; pre_inc(i))
	std::cout << arr[i] << " ";
    }
    std::cout << "}" << std::endl;
  }
};

template <
  typename T,
  int Size,
  bool Overwrite
  >
  ring_buffer<T, Size, Overwrite>::ring_buffer() : begin(0), end(0), count(0)
{

}

template <typename T, int Size, bool Overwrite>
  inline int ring_buffer<T, Size, Overwrite>::next(const int& v)
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
  if(end == begin && count != 0)
  {
    if(!Overwrite)
      throw std::runtime_error("Attempt to push element to full ring buffer.");
    else
    {
      --count;
      pre_inc(begin);
    }
  }

  ++count;
  arr[post_inc(end)] = el;
}
  
template <typename T, int Size, bool Overwrite>
  T ring_buffer<T, Size, Overwrite>::pull()
{
  --count;
  return arr[post_inc(begin)];
}

template <typename T, int Size, bool Overwrite>
  bool ring_buffer<T, Size, Overwrite>::empty() const
{
  return begin == end && count == 0;;
}

class Big
{
private:
  int arr[100];
public:
  Big() { for(int i = 0; i < 100; ++i) arr[i] = rand() % 10; }
  friend bool operator==(const Big& a, const Big& b)
  {
    for(int i = 0; i < 100; ++i)
      if(a.arr[i] != b.arr[i])
	return false;
    return true;
  }
  friend bool operator!=(const Big& a, const Big& b)
  {
    return !(a == b);
  }
};

bool push_pull_test()
{
  try
  {
    ring_buffer<int, 5, false> ri;

    // dla wielu wartości początkowych
    for(int i = 0; i < 100; ++i)
    {
      int a = rand();
      int b = rand();
      int c = rand();
      
      ri.push(a);
      ri.push(b);
      ri.push(c);

      if(ri.empty()) return false;
      if(ri.pull() != a) return false;

      if(ri.empty()) return false;
      if(ri.pull() != b) return false;

      if(ri.empty()) return false;
      if(ri.pull() != c) return false;

      if(!ri.empty()) return false;
    }
  }
  catch(std::exception& e)
  {
    return false;
  }

  return true;
}

bool push_pull_big_test()
{
  try
  {
    ring_buffer<Big, 5, false> ri;

    // dla wielu wartości początkowych
    for(int i = 0; i < 100; ++i)
    {
      Big a;
      Big b;
      Big c;
      
      ri.push(a);
      ri.push(b);
      ri.push(c);

      if(ri.pull() != a) return false;
      if(ri.pull() != b) return false;
      if(ri.pull() != c) return false;

      if(!ri.empty()) return false;
    }
  }
  catch(std::exception& e)
  {
    return false;
  }

  return true;
}

bool push_full_overwrite_test()
{
  try
  {
    ring_buffer<int, 3, true> ri;

    ri.push(0);
    ri.push(1);
    ri.push(2);
    ri.push(3);
    ri.push(4);
    ri.push(5);

    if(ri.pull() != 3) return false;
    if(ri.pull() != 4) return false;
    if(ri.pull() != 5) return false;
    
    if(!ri.empty()) return false;
  }
  catch(std::exception e)
  {
    return false;
  }
  
  return true;
}
  
bool push_full_exception_test()
{
  try
  {
    ring_buffer<int, 5, false> ri;

    for(int i = 0; i < 6; ++i)
      ri.push(rand());
  }
  catch(std::exception e)
  {
    return true;
  }
  
  return false;
}

bool test()
{
  return push_pull_test() &&
    push_pull_big_test() &&
    push_full_overwrite_test() &&
    push_full_exception_test();
}

int main()
{
  srand(time(0));
  
  if(test())
    std::cout << "Test passed" << std::endl;
  else
    std::cout << "Test failed" << std::endl;
  
  return 0;
}
