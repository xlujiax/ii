#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>

class TabBit
{
  typedef unsigned long long slowo; // komorka w tablicy
  static const int rozmiarSlowa; // rozmiar slowa w bitach
  friend std::istream & operator >> (std::istream &we, TabBit &tb);
  friend std::ostream & operator << (std::ostream &wy, const TabBit &tb);
 public:
  class Ref
  {
    TabBit* tb;
    int i;
  public:
  Ref(TabBit* const tbp, const int ip) : tb(tbp), i(ip) {}
    bool operator = (bool bit) { tb->pisz(i, bit); return bit; }
    bool operator = (const Ref& r) { tb->pisz(i, r.tb->czytaj(r.i)); return r.tb->czytaj(r.i); }
    operator bool() const { return tb->czytaj(i); }
  };
  class Zakres {}; // klasa wyjatku

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
  public:
  bool pisz (int i, bool b);
 public:
  bool operator[] (int i) const;
  Ref operator[] (int i);
  inline int rozmiar () const { return dl; }
};
