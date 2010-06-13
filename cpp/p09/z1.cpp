#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

template<typename T,
	 template <
	   typename Element,
	   typename = std::allocator<Element>
	   > class Sequence = std::deque,
	 class Cmp = std::less<T> >
  class priority_queue
{
private:
  Sequence<T> seq;
public:
  void push(const T& t)
  {
    seq.push_back(t);
    std::push_heap(seq.begin(), seq.end(), Cmp());
  }
  void pop()
  {
    std::pop_heap(seq.begin(), seq.end(), Cmp());
    seq.pop_back();
  }
  T& front()
  {
    return *seq.begin();
  }
  const T& front() const
  {
    return *seq.begin();
  }
  bool empty() const
  {
    return seq.empty();
  }
  void pr()
  {
    for(typename Sequence<T>::iterator i = seq.begin(); i != seq.end(); ++i)
      std::cout << *i << '\n';
  }
};

struct test_t
{
  float f;
  float g;
  test_t(float F, float G) : f(F), g(G) {}
  bool operator<(const test_t& t) const
  {
    return f < t.f || (f == t.f && g < t.g);
  }
  friend std::ostream& operator<<(std::ostream& os, const test_t& t)
  {
    os << '(' << t.f << ' ' << t.g << ')';
    return os;
  }
};

struct higher_g_cmp
{
  bool operator()(const test_t& t, const test_t& u)
  {
    return t.g < u.g || (t.g == u.g && t.f < u.f);
  }
};

int main(int, char*[])
{
  {
    std::cout << "Kolejka liczb\n";
    priority_queue<int> pq;
    pq.push(7);
    pq.push(3);
    pq.push(2);
    pq.push(10);
    pq.push(1);
    
    while(!pq.empty())
    {
      std::cout << pq.front() << ' ';
      pq.pop();
    }
    std::cout << std::endl;
  }

  {
    std::cout << "Kolejka liczb posortowana w odwrotnej kolejnosci\n";
    priority_queue<int, std::deque, std::greater<int> > pq;
    pq.push(7);
    pq.push(3);
    pq.push(2);
    pq.push(10);
    pq.push(1);
    
    while(!pq.empty())
    {
      std::cout << pq.front() << ' ';
      pq.pop();
    }
    std::cout << std::endl;
  }

  {
    std::cout << "Kolejka obiektow test_t\n";
    priority_queue<test_t> pq;
    pq.push(test_t(3.14, 7.0));
    pq.push(test_t(3.14, 7.6));
    pq.push(test_t(3.14, 7.1));
    pq.push(test_t(3.5, 7.0));
    pq.push(test_t(3.5, 2.0));
    
    while(!pq.empty())
    {
      std::cout << pq.front() << ' ';
      pq.pop();
    }
    std::cout << std::endl;
  }


  {
    std::cout << "Kolejka obiektow test_t, inny priorytet\n";
    priority_queue<test_t, std::deque, higher_g_cmp> pq;
    pq.push(test_t(3.14, 7.0));
    pq.push(test_t(3.14, 7.6));
    pq.push(test_t(3.14, 7.1));
    pq.push(test_t(3.5, 7.0));
    pq.push(test_t(3.5, 2.0));
    
    while(!pq.empty())
    {
      std::cout << pq.front() << ' ';
      pq.pop();
    }
    std::cout << std::endl;
  }


  {
    std::cout << "Kolejka obiektow test_t, vector\n";
    priority_queue<test_t, std::vector> pq;
    pq.push(test_t(3.14, 7.0));
    pq.push(test_t(3.14, 7.6));
    pq.push(test_t(3.14, 7.1));
    pq.push(test_t(3.5, 7.0));
    pq.push(test_t(3.5, 2.0));
    
    while(!pq.empty())
    {
      std::cout << pq.front() << ' ';
      pq.pop();
    }
    std::cout << std::endl;
  }


  
  return 0;
}
