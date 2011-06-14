template<typename T>
  struct expr
{
  typedef const T& type;
};

template<typename T, typename L, typename R>
  class addition_operator
{
  typename expr<L>::type l;
  typename expr<R>::type r;
public:
  addition_operator(const L& ll, const R& rr) : l(ll), r(rr)  {}
  T operator[](int i) const { return l[i] + r[i]; }
  int size() const { return (l.size() == 0) ? r.size() : l.size(); }
};

template <typename T, int Sz, typename R1, typename R2>
  const vector<T, Sz, addition_operator<T, R1, R2> >
  operator+(const vector<T, Sz, R1>& a, const vector<T, Sz, R2>& b)
{
  return vector<T, Sz, addition_operator<T,R1,R2> >(addition_operator<T,R1,R2>(a.get_rep(), b.get_rep()));
}

template<typename T>
  class scalar
{
  T rep;
public:
  scalar(T const& s) : rep(s) {}
  T operator[] (int) const { return rep; }
  int size() const { return 0; }
};

template<typename T, int Size>
  class vector_data
{
  T data[Size];
public:
  vector_data() {}
  vector_data(const vector_data<T, Size>& v)
  {
    for(int i = 0; i < size(); ++i)
      data[i] = v[i];
  }

  T& operator[](int i) { return data[i]; }
  T operator[](int i) const { return data[i]; }
  static int size() { return Size; }
};

template<typename T, int Size, typename Rep = vector_data<T, Size> >
  class vector
{
  Rep rep;
public:
  vector() {}
  vector(Rep const& r) : rep(r) {}
  template<typename T2, typename Rep2>
    vector& operator= (const vector<T2, Size, Rep2>& b)
  {
    for(int i = 0; i < b.size(); ++i)
      rep[i] = b[i];
    return *this;
  }
  int size() const { return rep.size(); }
  T operator[](int i) const { return rep[i]; }
  T& operator[](int i) { return rep[i]; }
};

template<typename T, int Size>
  class vector<T, Size, scalar<T> >
{
  scalar<T> rep;
public:
  vector(T t) : rep(t) {}
  int size() const { return rep.size(); }
  T operator[](int i) const { return rep[i]; }
};

