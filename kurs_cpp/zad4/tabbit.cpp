#include "tabbit.h"

/*
  Przykład rozmiarów tablicy dla rozmiarSlowa=32:

  rozmiar | il. słów
  ------------------
      0   |    0
      1   |    1
      2   |    1
      3   |    1
     ...  |   ...
      31  |    1
      32  |    2
      33  |    2
     ...  |   ...
 */

TabBit::TabBit(int rozm) : dl(rozm)
{
  const unsigned int dlugoscWSlowach = (rozmiarSlowa - 1 + rozm) / rozmiarSlowa;
  tab = new slowo[dlugoscWSlowach];
  assert(dlugoscWSlowach * rozmiarSlowa >= rozm);
}

TabBit::TabBit(const TabBit &tb) : dl(tb.dl)
{
  const unsigned int dlugoscWSlowach = (rozmiarSlowa - 1 + dl) / rozmiarSlowa;
  tab = new slowo[dlugoscWSlowach];
  std::copy(tb.tab, tb.tab + dlugoscWSlowach, tab);
}

TabBit & TabBit::operator = (const TabBit &tb)
{
  if(this != &tb)
  {
    dl = tb.dl;
    const unsigned int dlugoscWSlowach = (rozmiarSlowa - 1 + dl) / rozmiarSlowa;
    tab = new slowo[dlugoscWSlowach];
    std::copy(tb.tab, tb.tab + dlugoscWSlowach, tab);
  }
}

TabBit::~TabBit ()
{
  delete []tab;
}

bool TabBit::czytaj (int i) const
{
  slowo maska = 1L;
  int pozycja = i % rozmiarSlowa;
  maska <<= pozycja;
  slowo otoczenie = tab[i / rozmiarSlowa];
  return static_cast<bool>((otoczenie & maska) >> pozycja);
}

bool TabBit::pisz (int i, bool b)
{
  int pozycja = i % rozmiarSlowa;
  slowo& otoczenie = tab[i / rozmiarSlowa];
  
  if(b)
  {
    slowo maska = 1L;
    maska <<= pozycja;
    otoczenie |= maska;
  }
  else
  {
    
    slowo maska = 1L;
    maska <<= pozycja;
    maska = ~maska;
    otoczenie &= maska;
  }
}

bool TabBit::operator[] (int i) const
{
  if(i < 0 || i > dl)
    throw std::out_of_range("Out of range of tabbit.");
  return czytaj(i);
}
 
TabBit::Ref TabBit::operator[] (int i)
{
  if(i < 0 || i > dl)
    throw std::out_of_range("Out of range of tabbit.");
  return Ref(this, i);
}

const int TabBit::rozmiarSlowa = sizeof(slowo);
/*
std::istream & operator >> (std::istream &we, TabBit &tb)
{
  for(int i = 0; i < tb.dl; ++i)
    we >> tb[i];
  return we;
}
*/
std::ostream & operator << (std::ostream &wy, const TabBit &t)
{
  std::copy(t.cbegin(), t.cend(), std::ostream_iterator<bool>(wy, ""));
  return wy;
}

bool negate(bool b) { return !b; }
bool and_f(bool a, bool b) { return a && b; }
bool or_f(bool a, bool b) { return a || b; }
bool xor_f(bool a, bool b) { return a ^ b; }

TabBit operator~(const TabBit& src)
{
  TabBit t(src.rozmiar());
  std::transform(src.cbegin(), src.cend(), t.begin(), negate);
  return t;
}
TabBit operator&(const TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  TabBit t(a.rozmiar());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), t.begin(), and_f);
  return t;
}
TabBit operator|(const TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  TabBit t(a.rozmiar());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), t.begin(), or_f);
  return t;
}
TabBit operator^(const TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  TabBit t(a.rozmiar());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), t.begin(), xor_f);
  return t;
}
TabBit& operator&=(TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  std::transform(b.cbegin(), b.cend(), a.cbegin(), a.begin(), and_f);
  return a;
}
TabBit& operator|=(TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  std::transform(b.cbegin(), b.cend(), a.cbegin(), a.begin(), or_f);
  return a;
}
TabBit& operator^=(TabBit& a, const TabBit& b)
{
  assert(a.rozmiar() == b.rozmiar());
  std::transform(b.cbegin(), b.cend(), a.cbegin(), a.begin(), xor_f);
  return a;
}
