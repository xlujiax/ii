#include <iostream>

template<typename R, typename T, typename U>
struct binary_function_wrapper {
private:
    typedef R (*Func)(T,U);
    Func func;
public:
    binary_function_wrapper(Func f) : func(f) {}
     R operator()(const T& t, const U& u) const {
        return func(t, u);
    }
 public:
     static const int args = 2;
     typedef R return_type;
     typedef T param1;
     typedef U param2;
};

template<typename R, typename T>
struct unary_function_wrapper {
private:
    typedef R (*Func)(T);
    Func func;
public:
    unary_function_wrapper(Func f) : func(f) {}
     R operator()(const T& t) const {
        return func(t);
    }
 public:
     static const int args = 1;
     typedef R return_type;
     typedef T param1;
};

template<typename Functor, int Args>
class binder1st;

template<typename Functor>
class binder1st<Functor, 2>
{
private:
    Functor f;
    const typename Functor::param1& t;
public:
    binder1st(const Functor& f_, const typename Functor::param1& t_) : f(f_), t(t_) {}
    typename Functor::return_type
            operator()(const typename Functor::param2& u) const { return f(t, u); }

public:
    static const int args = 1;
    typedef typename Functor::return_type return_type;
    typedef typename Functor::param2 param1;
    typedef void param2;
};

template<typename Functor>
class binder1st<Functor, 1>
{
private:
    Functor f;
    const typename Functor::param1& t;
public:
    binder1st(const Functor& f_, const typename Functor::param1& t_) : f(f_), t(t_) {}
    typename Functor::return_type
            operator()() const { return f(t); }

public:
    static const int args = 0;
    typedef typename Functor::return_type return_type;
    typedef void param1;
    typedef void param2;
};

template<typename Functor>
binder1st<Functor, Functor::args> bind1st(const Functor& f, const typename Functor::param1& t)
{
    return binder1st<Functor, Functor::args>(f, t);
}

template<typename R, typename T, typename U>
binder1st<binary_function_wrapper<R, T, U>, 2> bind1st(R (*f)(T,U), const T& t)
{
    return binder1st<binary_function_wrapper<R, T, U>, 2>(binary_function_wrapper<R, T, U>(f), t);
}

template<typename R, typename T>
binder1st<unary_function_wrapper<R, T>, 1> bind1st(R (*f)(T), const T& t)
{
    return binder1st<unary_function_wrapper<R, T>, 1>(unary_function_wrapper<R, T>(f), t);
}


template<typename Functor>
class binder2nd
{
private:
    Functor f;
    const typename Functor::param2& t;
public:
    binder2nd(const Functor& f_, const typename Functor::param2& t_) : f(f_), t(t_) {}
    typename Functor::return_type
            operator()(const typename Functor::param1& u) const { return f(u, t); }

public:
    static const int args = 1;
    typedef typename Functor::return_type return_type;
    typedef typename Functor::param1 param1;
    typedef void param2;
};

template<typename Functor>
binder2nd<Functor> bind2nd(const Functor& f, const typename Functor::param2& t)
{
    return binder2nd<Functor>(f, t);
}

template<typename R, typename T, typename U>
binder2nd<binary_function_wrapper<R, T, U> > bind2nd(R (*f)(T,U), const T& t)
{
    return binder2nd<binary_function_wrapper<R, T, U> >(binary_function_wrapper<R, T, U>(f), t);
}

template<typename R, typename T>
binder2nd<unary_function_wrapper<R, T> > bind2nd(R (*f)(T), const T& t)
{
    return binder2nd<unary_function_wrapper<R, T> >(unary_function_wrapper<R, T>(f), t);
}

template<typename OutsideFunctor, typename InsideFunctor, int InsideArgs>
struct composer;

template<typename OutsideFunctor, typename InsideFunctor>
struct composer<OutsideFunctor, InsideFunctor, 2>
{
private:
    OutsideFunctor out_f;
    InsideFunctor in_f;
public:
    static const int args = 2;
    typedef typename OutsideFunctor::return_type return_type;
    typedef typename InsideFunctor::param1 param1;
    typedef typename InsideFunctor::param2 param2;
public:
    composer(const OutsideFunctor& out_f_, const InsideFunctor& in_f_)
        : out_f(out_f_), in_f(in_f_) {}
    return_type operator()(const param1& p1, const param2& p2) const
    {
        return out_f(in_f(p1, p2));
    }
};

template<typename OutsideFunctor, typename InsideFunctor>
struct composer<OutsideFunctor, InsideFunctor, 1>
{
private:
    OutsideFunctor out_f;
    InsideFunctor in_f;
public:
    static const int args = 1;
    typedef typename OutsideFunctor::return_type return_type;
    typedef typename InsideFunctor::param1 param1;
public:
    composer(const OutsideFunctor& out_f_, const InsideFunctor& in_f_)
        : out_f(out_f_), in_f(in_f_) {}
    return_type operator()(const param1& p1) const
    {
      return out_f(in_f(p1));
    }
};

template<typename OutsideFunctor, typename InsideFunctor>
composer<OutsideFunctor, InsideFunctor, InsideFunctor::args>
        compose(const OutsideFunctor& out_f, const InsideFunctor& in_f)
{
    return composer<OutsideFunctor, InsideFunctor, InsideFunctor::args>(out_f, in_f);
}

template<typename OutsideFunctor, typename R, typename T>
composer<OutsideFunctor, unary_function_wrapper<R, T>, 1>
        compose(const OutsideFunctor& out_f, R (*in_f)(T))
{
    return composer<OutsideFunctor, unary_function_wrapper<R, T>, 1>(out_f, in_f);
}

template<typename OutsideFunctor, typename R, typename T, typename U>
composer<OutsideFunctor, binary_function_wrapper<R, T, U>, 2>
        compose(const OutsideFunctor& out_f, R (*in_f)(T, U))
{
    return composer<OutsideFunctor, binary_function_wrapper<R, T, U>, 2>(out_f, in_f);
}

template<typename R1, typename T1, typename InsideFunctor>
  composer<unary_function_wrapper<R1, T1>, InsideFunctor, InsideFunctor::args>
        compose(R1 (*out_f)(T1), const InsideFunctor& in_f)
{
  return composer<unary_function_wrapper<R1, T1>, InsideFunctor, InsideFunctor::args>(out_f, in_f);
}

template<typename R1, typename T1, typename R2, typename T2>
composer<unary_function_wrapper<R1, T1>, unary_function_wrapper<R2, T2>, 1>
  compose(R1 (*out_f)(T1), R2 (*in_f)(T2))
{
    return composer<unary_function_wrapper<R1, T1>, unary_function_wrapper<R2, T2>, 1>(out_f, in_f);
}

template<typename R1, typename T1, typename R2, typename T2, typename U2>
  composer<unary_function_wrapper<R1, T1>, binary_function_wrapper<R2, T2, U2>, 2>
        compose(R1 (*out_f)(T1), R2 (*in_f)(T2, U2))
{
  return composer<unary_function_wrapper<R1, T1>, binary_function_wrapper<R2, T2, U2>, 2>(out_f, in_f);
}

template<typename R1, typename T1, typename U1, typename InsideFunctor>
  composer<binary_function_wrapper<R1, T1, U1>, InsideFunctor, InsideFunctor::args>
        compose(R1 (*out_f)(T1, U1), const InsideFunctor& in_f)
{
  return composer<binary_function_wrapper<R1, T1, U1>, InsideFunctor, InsideFunctor::args>(out_f, in_f);
}

template<typename R1, typename T1, typename U1, typename R2, typename T2>
composer<binary_function_wrapper<R1, T1, U1>, unary_function_wrapper<R2, T2>, 1>
  compose(R1 (*out_f)(T1, U1), R2 (*in_f)(T2))
{
    return composer<binary_function_wrapper<R1, T1, U1>, unary_function_wrapper<R2, T2>, 1>(out_f, in_f);
}

template<typename R1, typename T1, typename U1, typename R2, typename T2, typename U2>
  composer<binary_function_wrapper<R1, T1, U1>, binary_function_wrapper<R2, T2, U2>, 2>
        compose(R1 (*out_f)(T1, U1), R2 (*in_f)(T2, U2))
{
  return composer<binary_function_wrapper<R1, T1, U1>, binary_function_wrapper<R2, T2, U2>, 2>(out_f, in_f);
}

template<typename T>
bool greater_function(T a, T b) { return a > b; }

template<typename T>
struct greater_functor
{
    bool operator()(T a, T b) const { return a > b; }

    static const int args = 2;
    typedef bool return_type;
    typedef T param1;
    typedef T param2;
};

template<typename T>
T div_function(T a, T b) { return a / b; }

template<typename T>
struct div_functor
{
    T operator()(T a, T b) const { return a / b; }

    static const int args = 2;
    typedef T return_type;
    typedef T param1;
    typedef T param2;
};

float add_5_function(float a) { return a + 5.0f; }
struct add_n_functor
{
    float n;

    add_n_functor(float n_) : n(n_) {}
    float operator()(float a) const { return a + n; }

    static const int args = 1;
    typedef float return_type;
    typedef float param1;
};

struct add_5_functor
{
    float operator()(float a) const { return a + 5.0f; }

    static const int args = 1;
    typedef float return_type;
    typedef float param1;
};

#define TEST(a) std::cout << #a << " = " << (a) << std::endl
#define CAPTION(a) std::cout << std::endl << (a) << std::endl

int main(int, char*[])
{
  CAPTION("Porownanie, wiazanie pierwszego argumentu");

    TEST(bind1st(greater_function<int>, 4)(7));
    TEST(bind1st(greater_function<int>, 7)(4));

    CAPTION("Porownanie, wiazanie drugiego argumentu");
    TEST(bind2nd(greater_function<int>, 4)(7));
    TEST(bind2nd(greater_function<int>, 7)(4));

    CAPTION("Porownanie za pomoca funktora");
    TEST(bind1st(greater_functor<int>(), 4)(7));
    TEST(bind1st(greater_functor<int>(), 7)(4));

    TEST(bind2nd(greater_functor<int>(), 4)(7));
    TEST(bind2nd(greater_functor<int>(), 7)(4));

    CAPTION("Wiazanie obu argumentow");
    TEST(bind1st(bind1st(greater_function<int>, 4), 7)());
    TEST(bind1st(bind2nd(greater_function<int>, 4), 7)());

    CAPTION("Operacje arytmetyczne");
    TEST(bind1st(div_function<float>, 2.0f)(3.0f));
    TEST(bind2nd(div_function<float>, 2.0f)(3.0f));

    CAPTION("Operacje arytmetyczne, funktory");
    TEST(bind1st(div_functor<float>(), 2.0f)(3.0f));
    TEST(bind2nd(div_functor<float>(), 2.0f)(3.0f));

    CAPTION("Wiazanie funkcji i funktorow jednoargumentowych");
    TEST(bind1st(add_5_function, 1.0f)());
    TEST(bind1st(add_5_functor(), 1.0f)());
    
    CAPTION("Kompozycja przyjmuje funkcje i funktory");
    TEST(compose(add_n_functor(3.0f), add_5_functor())(1.0f));
    TEST(compose(add_n_functor(3.0f), add_5_function)(1.0f));
  TEST(compose(add_5_function, add_5_function)(1.0f));
  TEST(compose(add_5_function, add_n_functor(3.0f))(1.0f));


  CAPTION("Zlozenie kompozycji");
  TEST(compose(add_5_function, compose(add_5_function, add_5_function))(7.0f));
  TEST(compose(add_n_functor(8.0f), compose(bind2nd(div_function<float>, 7.0f), add_5_function))(7.0f));

  CAPTION("Compose zwracajacy funktor dwuargumentowy");
  TEST(compose(add_5_function, div_function<float>)(1.0f, 3.0f));
  TEST(compose(add_n_functor(5.0f), div_functor<float>())(1.0f, 3.0f));
    return 0;
}
