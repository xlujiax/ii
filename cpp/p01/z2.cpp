#include <cstdlib>
#include <ctime>
#include <complex>

#include <algorithm>
#include <deque>
#include <list>
#include <vector>
#include <iostream>

template <
  typename T,
  template <
    typename Element,
    typename = std::allocator<Element>
  > class Container = std::deque
>
class stack {
  template<
    typename T3,
    template<
      typename E3,
      typename A3
      > class C3
    > friend class stack;
  
  Container<T> cont;
public:
  typedef T value_type;

  void push( const T& );
  T top() const;
  bool empty() const;
  void pop();  

  template <typename T2, template <typename,typename> class Container2 >
    stack<T,Container>& operator= (stack<T2,Container2> const&); 
};

template <typename T,template <typename, typename> class Container>
  void stack<T, Container>::push(const T& el)
{
  cont.push_back(el);
}

template <typename T,template <typename, typename> class Container>
  T stack<T, Container>::top() const
{
  return cont.back();
}

template <typename T,template <typename, typename> class Container>
  bool stack<T, Container>::empty() const
{
  return cont.empty();
}

template <typename T,template <typename, typename> class Container>
  void stack<T, Container>::pop()
{
  cont.pop_back();
}

template <typename T,template <typename, typename> class Container>
template <typename T2, template <typename,typename> class Container2 >
  stack<T,Container>& stack<T,Container>::operator= (stack<T2,Container2> const& param)
{
  copy(param.cont.begin(), param.cont.end(), back_inserter(cont));
  return *this;
}

template <typename T>
  T random_value();

template <>
  int random_value() { return rand() % 100; }

template <>
  float random_value() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }

template <>
  std::complex<float> random_value()
{
  return std::complex<float>(random_value<float>(), random_value<float>());
}

template <typename Stack>
void test_stack()
{
  Stack s;

  for(int i = 0; i < 5; ++i)
  {
    typename Stack::value_type rd = random_value<typename Stack::value_type>();
    std::cout << "Na stos: " << rd << std::endl;
    s.push(rd);
  }

  while(!s.empty())
  {
    std::cout << "Ze stosu: " << s.top() << std::endl;
    s.pop();
  }

  // uzycie operatora =
  
  stack<typename Stack::value_type, std::vector> v;
  stack<typename Stack::value_type, std::deque> d;
  stack<typename Stack::value_type, std::list> l;

  v = s;
  d = s;
  l = s;
}

int main()
{
  srand(time(0));
  
  test_stack<stack<int, std::vector> >();
  test_stack<stack<std::complex<float>, std::vector> >();
  
  return 0;
}
