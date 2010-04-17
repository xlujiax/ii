#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

/*
 czy to jest rzutowanie:
 
template<typename ArgMod, typename Arg>
  class unary : public callback
{
  template<typename ArgMod_ typename Arg_>
    friend callback* make_callback(void (*)(ArgMod_), Arg_);

  typedef void (*Func)(ArgMod);
  
  Func func;
  Arg arg;
  unary(Func f, Arg a) : func(f), arg(a) {}
public:
  virtual void do_call() { func(static_cast<ArgMod>(arg)); }
  virtual ~unary() {}
};

template<typename Arg>
  callback* make_callback(void (*f)(Arg), Arg)
{ return new unary<Arg>(f, arg); }

 */
   

/*
 * Cecha pozwalająca wyciągnąć referencję do typu:
 * T        -> const T&
 * T&       -> T&
 * const T  -> const T&
 * const T& -> const T&
*/
   template<typename T>
     struct ref_trait
   { typedef const T& type; };

template<typename T>
  struct ref_trait<T&>
{ typedef T& type; };

/*
 * Klasy przechowujące argumenty callback'ów
 */

struct callback
{
  void call() { do_call(); };
protected:
  virtual void do_call() = 0;
};

class zeroary : public callback
{
  friend callback* make_callback(void (*f)());

  void (*func)();
  
  zeroary(void (*f)()) : func(f) {}
public:
  virtual void do_call() { func(); }
};

template<typename Arg>
  class unary : public callback
{
  template<typename Arg_>
    friend callback* make_callback(void (*)(Arg_),
      typename ref_trait<Arg_>::type);

  typedef typename ref_trait<Arg>::type ArgRef;
  typedef void (*Func)(Arg);
  
  Func func;
  ArgRef arg;
  
  unary(Func f, ArgRef a) : func(f), arg(a) {}
public:
  virtual void do_call() { func(arg); }
  virtual ~unary() {}
};

template<typename Arg1, typename Arg2>
  class binary : public callback
{
  template<typename Arg1_, typename Arg2_>
    friend callback* make_callback(
      void (*)(Arg1_, Arg2_),
      typename ref_trait<Arg1_>::type,
      typename ref_trait<Arg2_>::type);

  typedef typename ref_trait<Arg1>::type Arg1Ref;
  typedef typename ref_trait<Arg2>::type Arg2Ref;
  typedef void (*Func)(Arg1, Arg2);
  
  Func func;
  Arg1Ref arg1;
  Arg2Ref arg2;

  binary(Func f, Arg1Ref a, Arg2Ref b) : func(f), arg1(a), arg2(b) {}
public:
  virtual void do_call() { func(arg1, arg2); }
  virtual ~binary() {}
};

template<typename Obj>
  class zeroary_mem : public callback
{
  template<typename Obj_>
    friend callback* make_callback(void (Obj_::*)(), Obj_*);

  typedef void (Obj::*Func)();
  
  Func func;
  Obj* obj;

  zeroary_mem(Func f, Obj* o) : func(f), obj(o) {}
public:
  virtual void do_call() { (obj->*func)(); }
  virtual ~zeroary_mem() {}
};

template<typename Obj, typename Arg>
  class unary_mem : public callback
{
  template<typename Obj_, typename Arg_>
    friend callback* make_callback(void (Obj_::*)(Arg_),
      Obj_*,
      typename ref_trait<Arg_>::type);

  typedef typename ref_trait<Arg>::type ArgRef;
  typedef void (Obj::*Func)(Arg);
  
  Func func;
  Obj* obj;
  ArgRef arg;

  unary_mem(Func f, Obj* o, ArgRef a) : func(f), obj(o), arg(a) {}
public:
  virtual void do_call() { (obj->*func)(arg); }
  virtual ~unary_mem() {}
};

template<typename Obj, typename Arg1, typename Arg2>
  class binary_mem : public callback
{
  template<typename Obj_, typename Arg1_, typename Arg2_>
    friend callback* make_callback(void (Obj_::*)(Arg1_, Arg2_),
      Obj_*,
      typename ref_trait<Arg1_>::type,
      typename ref_trait<Arg2_>::type);

  typedef typename ref_trait<Arg1>::type Arg1Ref;
  typedef typename ref_trait<Arg2>::type Arg2Ref;
  typedef void (Obj::*Func)(Arg1, Arg2);
  
  Func func;
  Obj* obj;
  Arg1Ref arg1;
  Arg2Ref arg2;

  binary_mem(Func f, Obj* o, Arg1Ref a, Arg2Ref b) : func(f), obj(o), arg1(a), arg2(b) {}
public:
  virtual void do_call() { (obj->*func)(arg1, arg2); }
  virtual ~binary_mem() {}
};

/*
 * Przeciążenia make_callback
 */

callback* make_callback(void (*f)())
{ return new zeroary(f); }

template<typename Arg>
  callback* make_callback(void (*f)(Arg),
    typename ref_trait<Arg>::type arg)
{ return new unary<Arg>(f, arg); }

template<typename Arg1, typename Arg2>
  callback* make_callback(void (*f)(Arg1, Arg2),
    typename ref_trait<Arg1>::type arg1,
    typename ref_trait<Arg2>::type arg2)
{ return new binary<Arg1, Arg2>(f, arg1, arg2); }

template<typename Obj>
  callback* make_callback(void (Obj::*f)(), Obj* obj)
{ return new zeroary_mem<Obj>(f, obj); }

template<typename Obj, typename Arg>
  callback* make_callback(void (Obj::*f)(Arg),
    Obj* obj,
    typename ref_trait<Arg>::type arg)
{ return new unary_mem<Obj, Arg>(f, obj, arg); }

template<typename Obj, typename Arg1, typename Arg2>
  callback* make_callback(void (Obj::*f)(Arg1, Arg2),
    Obj* obj,
    typename ref_trait<Arg1>::type arg1,
    typename ref_trait<Arg2>::type arg2)
{ return new binary_mem<Obj, Arg1, Arg2>(f, obj, arg1, arg2); }

/*
 * Funkcje testowe
 */

void test_const(const int x) { std::cout << "test_const(" << x << ")" << std::endl; }
void test_ref(int& x) { std::cout << "test_ref(" << x << ")" << std::endl; }
void test_const_ref(const int& x) { std::cout << "test_const_ref(" << x << ")" << std::endl; }

void test1() { std::cout << "test1()" << std::endl; }
void test2(int x) { std::cout << "test2(" << x << ")" << std::endl; }
void test3(float x) { std::cout << "test3(" << x << ")" << std::endl; }
void test4(float x, int y) { std::cout << "test4(" << x << "," << y << ")" << std::endl; }

struct test_class {
  void test5() { std::cout << "::test5()" << std::endl; }
  void test6(const std::string& s)  { std::cout << "::test6(" << s << ")" << std::endl; }
  void test7(int x, const std::string& s)  { std::cout << "::test7(" << x << "," << s << ")" << std::endl; }
};

template<typename Obj>
  void test_call_member(Obj o, void (Obj::*f)()) { (o.*f)(); }

struct base_test { virtual void greet() { std::cout << "base_test::greet()" << std::endl; } };
struct derived_test : base_test { void greet() { std::cout << "derived_test::greet()" << std::endl; } };

template<typename T>
  struct vector_adapter
{
  std::vector<T> v;
  void push_two(const T& a, const T& b) { v.push_back(a); v.push_back(b); }
  void push_two_weird(const T& a, T b) { v.push_back(a); v.push_back(b); }
};

void call_callback(callback* c) { c->call(); }
void test_callback(int x) { std::cout << "test_callback(" << x << ")" << std::endl; }


void visit_9(std::vector<int>& v) { v.push_back(9); }
void visit_8(std::vector<int>& v) { v.push_back(8); }

void visit_arg(std::vector<int>& v, int arg) { v.push_back(arg); }

template<int Ratio>
  void visit_template(std::vector<int>& v) { v.push_back(Ratio); }



/*
 * Wykonywanie testów
 */

int main(int, char*[])
{
  {
    test_class t;

    std::vector<callback*> calls;

    int a = 9; // dla test_ref

    calls.push_back(make_callback(&test_const, 9));
    calls.push_back(make_callback(&test_ref, a));
    calls.push_back(make_callback(&test_const_ref, 9));

    calls.push_back(make_callback(&test1));
    calls.push_back(make_callback(&test2, 10));
    calls.push_back(make_callback(&test3, 3.1415));
    calls.push_back(make_callback(&test4, 2.81, 6));
    calls.push_back(make_callback(&test_class::test5, &t));

    std::string h = "hello";
    std::string hw = "hello world";
    std::string& rh = h;
    std::string& rhw = hw;
    const std::string& crh = "hello";
    const std::string& crhw = "hello world";
    const std::string ch = "hello";
    const std::string chw = "hello world";
    
    calls.push_back(make_callback(&test_class::test6, &t, h));
    calls.push_back(make_callback(&test_class::test7, &t, 7, hw));
    
    calls.push_back(make_callback(&test_class::test6, &t, rh));
    calls.push_back(make_callback(&test_class::test7, &t, 7, rhw));
    
    calls.push_back(make_callback(&test_class::test6, &t, ch));
    calls.push_back(make_callback(&test_class::test7, &t, 7, chw));
    
    calls.push_back(make_callback(&test_class::test6, &t, crh));
    calls.push_back(make_callback(&test_class::test7, &t, 7, crhw));

    for(std::vector<callback*>::iterator i = calls.begin(); i != calls.end(); ++i)
      (*i)->call();
  }
  
  {
    std::vector<int> v;

    const int& cri = 7;
    int temp = 6;
    int& ri = temp;
    int i = 732;

    callback* a = make_callback(&std::vector<int>::push_back, &v, cri);
    callback* b = make_callback(&std::vector<int>::push_back, &v, ri);
    callback* c = make_callback(&std::vector<int>::push_back, &v, i);
    callback* d = make_callback(&std::vector<int>::push_back, &v, 9);
    callback* e = make_callback(&std::vector<int>::push_back, &v, 13);

    e->call();
    d->call();
    c->call();
    b->call();
    a->call();

    std::cout << "vector<int>: ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }

  {
    vector_adapter<int> va;

    callback* c = make_callback(&vector_adapter<int>::push_two, &va, 8, 9);
    callback* w = make_callback(&vector_adapter<int>::push_two_weird, &va, 8, 9);

    c->call();
    w->call();

    std::cout << "vector_adapter: ";
    std::copy(va.v.begin(), va.v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }

  {
    base_test* test = new derived_test;
    callback* c = make_callback(&base_test::greet, test);
    c->call();
  }

  {
    std::vector<int> vi;
    vi.push_back(10);
    vi.push_back(56);
    vi.push_back(30);
    vi.push_back(120);
    vi.push_back(8);

    std::cout << "Vector generated: ";
    std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Istnieja dwie, przeciazone wersje std::sort, jedna bierze dwa iteratory, a druga bierze dwa iteratory i operator porownania.
    // Nalezy okreslic, ktora wersja bedzie wykorzystana. Jedna mozliwosc to jawne okreslenie parametrow szablonu:
    //Callback* sort_vi = make_callback<void (*)(std::vector<int>::iterator, std::vector<int>::iterator), std::vector<int>::iterator, std::vector<int>::iterator>(&std::sort, vi.begin(), vi.end());

    // druga to okreslenie funkcji przez rzutowanie:
    //Callback* sort_vi = make_callback(static_cast<void (*)(std::vector<int>::iterator, std::vector<int>::iterator)>(&std::sort), vi.begin(), vi.end());

    // trzecia to przekazanie funkcji poprzednio zachowanej w zmiennej odpowiedniego typu
    void (*s)(std::vector<int>::iterator, std::vector<int>::iterator) = &std::sort;
    callback* sort_vi = make_callback(s, vi.begin(), vi.end());
    
    sort_vi->call();

    std::cout << "Vector sorted: ";
    std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
  
  {
    std::list<int> li;
    li.push_back(10);
    li.push_back(56);
    li.push_back(30);
    li.push_back(120);
    li.push_back(8);

    callback* sort_li = make_callback(&std::list<int>::sort, &li);

    std::cout << "List generated: ";
    std::copy(li.begin(), li.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    sort_li->call();

    std::cout << "List sorted: ";
    std::copy(li.begin(), li.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    li.push_back(40);

    std::cout << "List after insertion: ";
    std::copy(li.begin(), li.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    sort_li->call();

    std::cout << "List sorted: ";
    std::copy(li.begin(), li.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }

  {
    callback* a = make_callback(&test_callback, 12345);
    callback* b = make_callback(&call_callback, a);

    b->call();
  }

   {
    std::vector<int> vis;

    callback* a = make_callback(&visit_arg, vis, 3);
    callback* c = make_callback(&visit_9, vis);
    callback* d = make_callback(&visit_8, vis);

    // szablonowa funkcja jako argument
    callback* e = make_callback(&visit_template<11>, vis);

    a->call();
    c->call();
    d->call();

    // drugie wykorzystanie c
    c->call();
    e->call();

    std::cout << "Visitor: ";
    std::copy(vis.begin(), vis.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
  
  return 0;
}
