#include <algorithm>
#include <deque>
#include <list>
#include <vector>

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


int main()
{
  stack<int, std::deque> a;

  a.push(5);
  a.push(4);
  a.push(3);
  
  stack<int, std::list> b;
  stack<int, std::vector> c;

  b = a;
  
  return 0;
}
