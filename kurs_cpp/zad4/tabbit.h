#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <stdexcept>

class TabBit
{
  typedef unsigned long long slowo; // komorka w tablicy
  static const int rozmiarSlowa; // rozmiar slowa w bitach
public:
  friend std::istream & operator >> (std::istream &we, TabBit &tb);
  friend std::ostream & operator << (std::ostream &wy, const TabBit &tb);
public:
  friend TabBit operator~(const TabBit&);
  friend TabBit operator&(const TabBit&, const TabBit&);
  friend TabBit operator|(const TabBit&, const TabBit&);
  friend TabBit operator^(const TabBit&, const TabBit&);
  friend TabBit operator&=(TabBit&, const TabBit&);
  friend TabBit operator|=(TabBit&, const TabBit&);
  friend TabBit operator^=(TabBit&, const TabBit&);
public:
  class Ref
  {
    TabBit* tb;
    int i;
  public:
    Ref(TabBit* const tbp, const int ip) : tb(tbp), i(ip) {}
    bool operator = (bool bit) { tb->pisz(i, bit); return bit; }
    bool operator = (const Ref& r)
    {
      const bool src = r.tb->czytaj(r.i);
      tb->pisz(i, src);
      return src;
    }
    operator bool() const { return tb->czytaj(i); }
  };
protected:
  int dl; // liczba bitów
  slowo *tab; // tablica bitów
public:
  explicit TabBit (int rozm);
  TabBit (const TabBit &tb);
  TabBit & operator = (const TabBit &tb);
  ~TabBit ();
public:
  bool czytaj (int i) const;
  bool pisz (int i, bool b);
public:
  bool operator[] (int i) const;
  Ref operator[] (int i);
  inline int rozmiar () const { return dl; }
public:
  struct iterator
  {
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef bool                            value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef bool*                           pointer;
    typedef bool&                           reference;
  private:
    TabBit* tb;
    int index;
  public:
    iterator(TabBit* t, int i) : index(i), tb(t) {}
    iterator(const iterator& iter) : index(iter.index), tb(iter.tb) {}
    void operator=(const iterator& iter)
    {
      tb = iter.tb;
      index = iter.index;
    }
    bool operator==(const iterator& i) const { return tb == i.tb && index == i.index; }
    bool operator!=(const iterator& i) const { return !(*this == i); }

    iterator& operator++()
    {
      ++index;
      return *this;
    }

    iterator operator++(int)
    {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    iterator& operator--()
    {
      --index;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator* () const { return tb->czytaj(index); }
    Ref operator* () { return Ref(tb, index); }
  };

  iterator begin() { return iterator(this, 0); }
  iterator end() { return iterator(this, dl); }

  struct const_iterator
  {
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef const bool                      value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const bool*                     pointer;
    typedef const bool&                     reference;
  private:
    const TabBit* tb;
    int index;
  public:
    const_iterator(const TabBit* t, int i) : index(i), tb(t) {}
    const_iterator(const const_iterator& iter) : index(iter.index), tb(iter.tb) {}
    void operator=(const const_iterator& iter)
    {
      tb = iter.tb;
      index = iter.index;
    }
    bool operator==(const const_iterator& i) const { return tb == i.tb && index == i.index; }
    bool operator!=(const const_iterator& i) const { return !(*this == i); }

    const_iterator& operator++()
    {
      ++index;
      return *this;
    }

    const_iterator operator++(int)
    {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    const_iterator& operator--()
    {
      --index;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator* () const { return tb->czytaj(index); }
  };
  
  const_iterator cbegin() const { return const_iterator(this, 0); }
  const_iterator cend() const { return const_iterator(this, dl); }
};
