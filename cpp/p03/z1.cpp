#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

/*
  pomysly na testy:
  * jako argument funkcji wskaznik na funkcje (+skladowa)
  * przekazuj do callback funkcje skladowe szablonowe
  * przekazuj do callback funkcje skladowe szablonowych klas
  * przekazuj do callback szablonowe skladowe szablonowych klas

  TODO: Zastanow sie nad obsluga bledow. jesli przekazany obiekt do callback jest NULL to zwracamy NULL. Czy po utworzeniu callback adres obiektu moze sie zmienic? Czy wywolanie callback moze zmienic adres obiektu? Jesli tak to mozemy propagowac wartosci NULL.
*/

template<typename T>
  struct type_op
{
  typedef T bare_type;
  typedef T& ref_type;
  typedef T& const_ref_type;
};

template<typename T>
  struct type_op<T&>
{
  typedef typename type_op<T>::bare_type bare_type;
  typedef typename type_op<T>::ref_type ref_type;
  typedef typename type_op<T>::const_ref_type const_ref_type;
};

template<typename T>
  struct type_op<const T>
{
  typedef T bare_type;
  typedef T& ref_type;
  typedef const T& const_ref_type;
};

template<typename T>
  struct type_op<const T&>
{
  typedef typename type_op<T>::bare_type bare_type;
  typedef typename type_op<T>::ref_type ref_type;
  typedef typename type_op<T>::const_ref_type const_ref_type;
};

struct Callback
{
  void call() { do_call(); };
protected:
  virtual void do_call() = 0;
};

class ZeroaryCallback : public Callback
{
  friend Callback* make_callback(void (*f)());

  void (*func)();
  ZeroaryCallback(void (*f)()) : func(f) {}
public:
  virtual void do_call() { func(); }
};

template<typename Arg>
  class UnaryCallback : public Callback
{
  template<typename Arg_>
    friend Callback* make_callback(void (*)(Arg_),
      typename type_op<Arg_>::bare_type);

  typedef typename type_op<Arg>::const_ref_type ArgRef;
  typedef void (*Func)(Arg);
  
  Func func;
  ArgRef arg;
  UnaryCallback(Func f, ArgRef a) : func(f), arg(a) {}
public:
  virtual void do_call() { func(arg); }
  virtual ~UnaryCallback() {}
};

template<typename Arg1, typename Arg2>
  class BinaryCallback : public Callback
{
  template<typename Arg1_, typename Arg2_>
    friend Callback* make_callback(
      void (*)(Arg1_, Arg2_),
      typename type_op<Arg1_>::bare_type,
      typename type_op<Arg2_>::bare_type
				   );

  typedef typename type_op<Arg1>::const_ref_type Arg1Ref;
  typedef typename type_op<Arg2>::const_ref_type Arg2Ref;
  typedef void (*Func)(Arg1, Arg2);
  
  Func func;
  Arg1Ref arg1;
  Arg2Ref arg2;

  BinaryCallback(Func f, Arg1Ref a, Arg2Ref b) : func(f), arg1(a), arg2(b) {}
public:
  virtual void do_call() { func(arg1, arg2); }
  virtual ~BinaryCallback() {}
};

template<typename Obj>
  class ZeroaryMemberCallback : public Callback
{
  template<typename Obj_>
    friend Callback* make_callback(void (Obj_::*)(), Obj_*);

  typedef void (Obj::*Func)();
  
  Func func;
  Obj* obj;

  ZeroaryMemberCallback(Func f, Obj* o) : func(f), obj(o) {}
public:
  virtual void do_call() { (obj->*func)(); }
  virtual ~ZeroaryMemberCallback() {}
};

template<typename Obj, typename Arg>
  class UnaryMemberCallback : public Callback
{
  template<typename Obj_, typename Arg_>
    friend Callback* make_callback(void (Obj_::*)(Arg_),
      Obj_*,
      typename type_op<Arg_>::bare_type);

  typedef typename type_op<Arg>::const_ref_type ArgRef;
  typedef void (Obj::*Func)(Arg);
  
  Func func;
  Obj* obj;
  ArgRef arg;

  UnaryMemberCallback(Func f, Obj* o, ArgRef a) : func(f), obj(o), arg(a) {}
public:
  virtual void do_call() { (obj->*func)(arg); }
  virtual ~UnaryMemberCallback() {}
};

template<typename Func, typename Obj, typename Arg1, typename Arg2>
  class BinaryMemberCallback : public Callback
{
  template<typename Func_, typename Obj_, typename Arg1_, typename Arg2_>
    friend Callback* make_callback(Func_, Obj_*, Arg1_, Arg2_);

  Func func;
  Obj* obj;
  Arg1 arg1;
  Arg2 arg2;

  BinaryMemberCallback(Func f, Obj* o, Arg1 a, Arg2 b) : func(f), obj(o), arg1(a), arg2(b) {}
public:
  virtual void do_call() { (obj->*func)(arg1, arg2); }
  virtual ~BinaryMemberCallback() {}
};

Callback* make_callback(void (*f)())
{
  return new ZeroaryCallback(f);
}

template<typename Arg>
  Callback* make_callback(void (*f)(Arg),
    typename type_op<Arg>::bare_type arg)
{
  return new UnaryCallback<Arg>(f, arg);
}

template<typename Arg1, typename Arg2>
  Callback* make_callback(void (*f)(Arg1, Arg2),
    typename type_op<Arg1>::bare_type arg1,
    typename type_op<Arg2>::bare_type arg2)
{
  return new BinaryCallback<Arg1, Arg2>(f, arg1, arg2);
}

template<typename Obj>
  Callback* make_callback(void (Obj::*f)(), Obj* obj)
{
  return new ZeroaryMemberCallback<Obj>(f, obj);
}

template<typename Obj, typename Arg>
  Callback* make_callback(void (Obj::*f)(Arg),
    Obj* obj,
    typename type_op<Arg>::bare_type arg)
{
  return new UnaryMemberCallback<Obj, Arg>(f, obj, arg);
}

template<typename Func, typename Obj, typename Arg1, typename Arg2>
  Callback* make_callback(Func f, Obj* obj, Arg1 arg1, Arg2 arg2)
{
  return new BinaryMemberCallback<Func, Obj, Arg1, Arg2>(f, obj, arg1, arg2);
}

void test_const(const int x) { std::cout << "test_const(" << x << ")" << std::endl; }
void test_ref(int& x) { std::cout << "test_ref(" << x << ")" << std::endl; }
void test_const_ref(const int& x) { std::cout << "test_const_ref(" << x << ")" << std::endl; }

void test1() { std::cout << "test1()" << std::endl; }
void test2(int x) { std::cout << "test2(" << x << ")" << std::endl; }
void test3(int x, int y) { std::cout << "test3(" << x << "," << y << ")" << std::endl; }

void test_two(int s, int x) { std::cout << "test_two(" << s << "," << x << ")" << std::endl; }

struct TestClass {
  std::string id;
  TestClass(const std::string& s) : id(s) {}

  void test4(const std::string s) { std::cout << id << "::test4(" << s << ")" << std::endl; }
  void test5() { std::cout << id << "::test5()" << std::endl; }
  void test6(int s)  { std::cout << id << "::test6(" << s << ")" << std::endl; }
  void test7(int x, int s)  { std::cout << id << "::test7(" << x << "," << s << ")" << std::endl; }
};

void visit_9(std::vector<int>& v) { v.push_back(9); }
void visit_8(std::vector<int>& v) { v.push_back(8); }

void visit_arg(std::vector<int>& v, int arg) { std::cout << "adres2: " << &v << std::endl; v.push_back(arg); }

template<int Ratio>
  void visit_template(std::vector<int>& v) { v.push_back(Ratio); }

template<typename Obj>
  void test_call_member(Obj o, void (Obj::*f)()) { (o.*f)(); }

struct BaseTest { virtual void greet() { std::cout << "BaseTest::greet()" << std::endl; } };
struct DerivedTest :BaseTest { void greet() { std::cout << "DerivedTest::greet()" << std::endl; } };

template<typename T>
  struct VectorAdapter
{
  std::vector<T> v;
  void push_two(const T& a, const T& b) { v.push_back(a); v.push_back(b); }
  void push_two_weird(const T& a, T b) { v.push_back(a); v.push_back(b); }
};


int main(int, char*[])
{
  {
    TestClass tc("TC1");

    std::vector<Callback*> calls;

    calls.push_back(make_callback(&test_const, 9));
    calls.push_back(make_callback(&test_ref, 9));
    calls.push_back(make_callback(&test_const_ref, 9));

    calls.push_back(make_callback(&test_two, 7, 9));

    calls.push_back(make_callback(&test1));
    calls.push_back(make_callback(&test2, 10));
    calls.push_back(make_callback(&test3, 20, 31));
    calls.push_back(make_callback(&TestClass::test5, &tc));

    calls.push_back(make_callback(&TestClass::test4, &tc, std::string("asdf")));
    calls.push_back(make_callback(&TestClass::test6, &tc, 6));
    calls.push_back(make_callback(&TestClass::test7, &tc, 7, 8));

    for(std::vector<Callback*>::iterator i = calls.begin(); i != calls.end(); ++i)
      (*i)->call();
  }

  {
    std::vector<int> v;

    const int& cri = 7;
    int temp = 6;
    int& ri = temp;
    int i = 732;

    Callback* a = make_callback(&std::vector<int>::push_back, &v, cri);
    Callback* b = make_callback(&std::vector<int>::push_back, &v, ri);
    Callback* c = make_callback(&std::vector<int>::push_back, &v, i);
    Callback* d = make_callback(&std::vector<int>::push_back, &v, 9);
    Callback* e = make_callback(&std::vector<int>::push_back, &v, 13);

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
    VectorAdapter<int> va;

    Callback* c = make_callback(&VectorAdapter<int>::push_two, &va, 8, 9);
    Callback* w = make_callback(&VectorAdapter<int>::push_two_weird, &va, 8, 9);

    c->call();
    w->call();

    std::cout << "VectorAdapter: ";
    std::copy(va.v.begin(), va.v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }

  {
    std::vector<int> vis;

    std::cout << "adres: " << &vis << std::endl;

    Callback* a = make_callback(&visit_arg, vis, 3);
    Callback* c = make_callback(&visit_9, vis);
    Callback* d = make_callback(&visit_8, vis);

    // szablonowa funkcja jako argument
    Callback* e = make_callback(&visit_template<11>, vis);

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

  {
    BaseTest* test = new DerivedTest;
    Callback* c = make_callback(&BaseTest::greet, test);
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
    Callback* sort_vi = make_callback(s, vi.begin(), vi.end());
    
    //Callback* sort_vi2 = make_callback(&std::sort<std::vector<int>::iterator, std::vector<int>::iterator>, vi.begin(), vi.end());
    //sort_vi2->call();

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

    Callback* sort_li = make_callback(&std::list<int>::sort, &li);

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
  return 0;
}
