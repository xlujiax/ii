// kompatybilnosc z stlem: value_type itp
// czy dzialaja stlowe algorytmy?
// comeau
// tworzenie sekwencji z pary iteratorow
// sortowanie podczas copy? - przeciązenei inserter, copy itp?

#include <iostream>
#include <deque>
#include <algorithm>
#include <string>

template<typename Key,
	 typename Value,
	 typename Cmp = std::less<Key> >
  class multimap
{
  std::deque<std::pair<Key, Value> > seq;
  struct key_cmp
  {
    bool operator()(const std::pair<Key, Value>& p,
      const std::pair<Key, Value>& q)
    {
      return Cmp()(p.first, q.first);
    }
  };
  
  struct key_with_pair_cmp_lower
  {
    bool operator()(const std::pair<Key, Value>& q, const Key& k)
    {
      return Cmp()(q.first, k);
    }
  };
  struct key_with_pair_cmp_upper
  {
    bool operator()(const Key& k, const std::pair<Key, Value>& q)
    {
      return Cmp()(k, q.first);
    }
  };
public:
  void insert(std::pair<Key, Value> p)
  {
    seq.insert(std::lower_bound(seq.begin(), seq.end(), p, key_cmp()), p);
  }
  typedef typename std::deque<std::pair<Key, Value> >::iterator iterator;
  iterator begin() { return seq.begin(); }
  iterator end() { return seq.end(); }
  iterator rbegin() { return seq.rbegin(); }
  iterator rend() { return seq.rend(); }

  iterator find(const Key& k)
  {
    return std::lower_bound(seq.begin(), seq.end(), k, key_with_pair_cmp_lower());
  }
  iterator lower_bound(const Key& k)
  {
    return find(k);
  }
  iterator upper_bound(const Key& k)
  {
    return std::upper_bound(seq.begin(), seq.end(), k, key_with_pair_cmp_upper());
  }
  std::pair<iterator, iterator> equal_range(const Key& k)
  {
    return make_pair(lower_bound(k), upper_bound(k));
  }

  bool empty() const { return seq.empty(); }
  void clear() const { seq.clear(); }
};

int main(int, char*[])
{
  std::cout << "wstawianie i iteracja po sekwencji\n";
  multimap<int, std::string> mm;
  mm.insert(std::make_pair(3, "three"));
  mm.insert(std::make_pair(1, "one"));
  mm.insert(std::make_pair(1, "jeden"));
  mm.insert(std::make_pair(1, "uno"));
  mm.insert(std::make_pair(4, "four"));
  mm.insert(std::make_pair(2, "two"));

  for(multimap<int, std::string>::iterator i = mm.begin(); i != mm.end(); ++i)
  {
    std::cout << (*i).first << ' ' << (*i).second << '\n';
  }

  {
    std::cout << "wyszukiwanie 3\n";
    multimap<int, std::string>::iterator three = mm.find(3);
    if(three != mm.end())
      std::cout << (*three).first << ' ' << (*three).second << '\n';
    else
      std::cout << "nie znaleziono\n";
  }  

  {
    std::cout << "wyszukiwanie 1\n";
    multimap<int, std::string>::iterator three = mm.find(1);
    if(three != mm.end())
      std::cout << (*three).first << ' ' << (*three).second << '\n';
    else
      std::cout << "nie znaleziono\n";
  }  

  {
    std::cout << "wyszukiwanie 5\n";
    multimap<int, std::string>::iterator three = mm.find(5);
    if(three != mm.end())
      std::cout << (*three).first << ' ' << (*three).second << '\n';
    else
      std::cout << "nie znaleziono\n";
  }
  
  {
    std::cout << "zakres dla 1:\n";
    multimap<int, std::string>::iterator b = mm.lower_bound(1);
    multimap<int, std::string>::iterator e = mm.upper_bound(1);
    for(multimap<int, std::string>::iterator i = b; i != e; ++i)
      std::cout << (*i).first << ' ' << (*i).second << '\n';
  }  

  return 0;
}
