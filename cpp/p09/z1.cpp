#include <iostream>
#include <deque>
#include <algorithm>

template<typename T,
	 template <
	   typename Element,
	   typename = std::allocator<Element>
	   > class Sequence = std::deque,
	 typename Cmp = std::less<T> >
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

  
  return 0;
}
