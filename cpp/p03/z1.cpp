#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

/*
  pomysly na testy:
  * jako argument funkcji wskaznik na funkcje (+skladowa)
  * przekazuj do callback funkcje składowe szablonowe
  * przekazuj do callback funkcje skladowe szablonowych klas
  * przekazuj do callback szablonowe skladowe szablonowych klas

  TODO: binary musza miec zestaw callbackow z niestalymi referencjami
  TODO: usun wszystkie callback
  TODO: Zastanow sie nad obsluga bledow. jesli przekazany obiekt do callback jest NULL to zwracamy NULL. Czy po utworzeniu callback adres obiektu moze sie zmienic? Czy wywolanie callback moze zmienic adres obiektu? Jesli tak to mozemy propagowac wartosci NULL. 
*/

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
    friend Callback* make_callback(void (*)(Arg_), Arg_);

  template<typename Arg_>
    friend Callback* make_callback(void (*)(const Arg_&), const Arg_&);

  template<typename Arg_>
    friend Callback* make_callback(void (*)(Arg_&), Arg_&);

  void (*func)(Arg);
  Arg arg;
  UnaryCallback(void (*f)(Arg), Arg a) : func(f), arg(a) {}
public:
  virtual void do_call() { func(arg); }
};

template<typename Arg1, typename Arg2>
  class BinaryCallback : public Callback
{
  template<typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (*)(Arg1_, Arg2_), Arg1_, Arg2_);
  
  template<typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (*)(const Arg1_&, Arg2_), const Arg1_&, Arg2_);
  
  template<typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (*)(Arg1_, const Arg2_&), Arg1_, const Arg2_&);
  
  template<typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (*)(const Arg1_&, const Arg2_&), const Arg1_&, const Arg2_&);

  void (*func)(Arg1, Arg2);
  Arg1 arg1;
  Arg2 arg2;

  BinaryCallback(void (*f)(Arg1, Arg2), Arg1 a, Arg2 b) : func(f), arg1(a), arg2(b) {}
public:
  virtual void do_call() { func(arg1, arg2); }
};

template<typename Obj>
  class ZeroaryMemberCallback : public Callback
{
  template<typename Obj_>
    friend Callback* make_callback(void (Obj_::*)(), Obj_*);

  void (Obj::*func)();
  Obj* obj;

  ZeroaryMemberCallback(void (Obj::*f)(), Obj* o) : func(f), obj(o) {}
public:
  virtual void do_call() { (obj->*func)(); }
};

template<typename Obj, typename Arg>
  class UnaryMemberCallback : public Callback
{
  template<typename Obj_, typename Arg_>
    friend Callback* make_callback(void (Obj_::*)(Arg_), Obj_*, Arg_);

  template<typename Obj_, typename Arg_>
    friend Callback* make_callback(void (Obj_::*)(const Arg_&), Obj_*, const Arg_&);

  template<typename Obj_, typename Arg_>
    friend Callback* make_callback(void (Obj_::*)(Arg_&), Obj_*, Arg_&);

  void (Obj::*func)(Arg);
  Obj* obj;
  Arg arg;

  UnaryMemberCallback(void (Obj::*f)(Arg), Obj* o, Arg a) : func(f), obj(o), arg(a) {}
public:
  virtual void do_call() { (obj->*func)(arg); }
};

template<typename Obj, typename Arg1, typename Arg2>
  class BinaryMemberCallback : public Callback
{
  template<typename Obj_, typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (Obj_::*)(Arg1_, Arg2_), Obj_*, Arg1_, Arg2_);
  template<typename Obj_, typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (Obj_::*)(const Arg1_&, const Arg2_&), Obj_*, const Arg1_&, const Arg2_&);
  template<typename Obj_, typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (Obj_::*)(Arg1_, const Arg2_&), Obj_*, Arg1_, const Arg2_&);
  template<typename Obj_, typename Arg1_, typename Arg2_>
    friend Callback* make_callback(void (Obj_::*)(const Arg1_&, Arg2_), Obj_*, const Arg1_&, Arg2_);

  void (Obj::*func)(Arg1, Arg2);
  Obj* obj;
  Arg1 arg1;
  Arg2 arg2;

  BinaryMemberCallback(void (Obj::*f)(Arg1, Arg2), Obj* o, Arg1 a, Arg2 b) : func(f), obj(o), arg1(a), arg2(b) {} 
public:
  virtual void do_call() { (obj->*func)(arg1, arg2); }
};

Callback* make_callback(void (*f)())
{
  return new ZeroaryCallback(f);
}

template<typename Arg>
  Callback* make_callback(void (*f)(Arg), Arg arg)
{
  return new UnaryCallback<Arg>(f, arg);
}

template<typename Arg>
  Callback* make_callback(void (*f)(const Arg&), const Arg& arg)
{
  return new UnaryCallback<const Arg&>(f, arg);
}

template<typename Arg>
  Callback* make_callback(void (*f)(Arg&), Arg& arg)
{
  return new UnaryCallback<Arg&>(f, arg);
}

template<typename Arg1, typename Arg2>
  Callback* make_callback(void (*f)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
{
  return new BinaryCallback<Arg1, Arg2>(f, arg1, arg2);
}

template<typename Arg1, typename Arg2>
  Callback* make_callback(void (*f)(const Arg1&, Arg2), const Arg1& arg1, Arg2 arg2)
{
  return new BinaryCallback<const Arg1&, Arg2>(f, arg1, arg2);
}

template<typename Arg1, typename Arg2>
  Callback* make_callback(void (*f)(Arg1, const Arg2&), Arg1 arg1, const Arg2& arg2)
{
  return new BinaryCallback<Arg1, const Arg2&>(f, arg1, arg2);
}

template<typename Arg1, typename Arg2>
  Callback* make_callback(void (*f)(const Arg1&, const Arg2&), const Arg1& arg1, const Arg2& arg2)
{
  return new BinaryCallback<const Arg1&, const Arg2&>(f, arg1, arg2);
}

template<typename Obj>
  Callback* make_callback(void (Obj::*f)(), Obj* obj)
{
  return new ZeroaryMemberCallback<Obj>(f, obj);
}

template<typename Obj, typename Arg>
  Callback* make_callback(void (Obj::*f)(Arg), Obj* obj, Arg arg)
{
  return new UnaryMemberCallback<Obj, Arg>(f, obj, arg);
}

template<typename Obj, typename Arg>
  Callback* make_callback(void (Obj::*f)(const Arg&), Obj* obj, const Arg& arg)
{
  return new UnaryMemberCallback<Obj, const Arg&>(f, obj, arg);
}

template<typename Obj, typename Arg>
  Callback* make_callback(void (Obj::*f)(Arg&), Obj* obj, Arg& arg)
{
  return new UnaryMemberCallback<Obj, Arg&>(f, obj, arg);
}

template<typename Obj, typename Arg1, typename Arg2>
  Callback* make_callback(void (Obj::*f)(Arg1, Arg2), Obj* obj, Arg1 arg1, Arg2 arg2)
{
  return new BinaryMemberCallback<Obj, Arg1, Arg2>(f, obj, arg1, arg2);
}

template<typename Obj, typename Arg1, typename Arg2>
  Callback* make_callback(void (Obj::*f)(const Arg1&, const Arg2&), Obj* obj, const Arg1& arg1, const Arg2& arg2)
{
  return new BinaryMemberCallback<Obj, const Arg1&, const Arg2&>(f, obj, arg1, arg2);
}

template<typename Obj, typename Arg1, typename Arg2>
  Callback* make_callback(void (Obj::*f)(Arg1, const Arg2&), Obj* obj, Arg1 arg1, const Arg2& arg2)
{
  return new BinaryMemberCallback<Obj, Arg1, const Arg2&>(f, obj, arg1, arg2);
}

template<typename Obj, typename Arg1, typename Arg2>
  Callback* make_callback(void (Obj::*f)(const Arg1&, Arg2), Obj* obj, const Arg1& arg1, Arg2 arg2)
{
  return new BinaryMemberCallback<Obj, const Arg1&, Arg2>(f, obj, arg1, arg2);
}

void test_const(const int x) { std::cout << "test_const(" << x << ")" << std::endl; }
void test_ref(const int x) { std::cout << "test_ref(" << x << ")" << std::endl; }
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

template<int Ratio>
  void visit_template(std::vector<int>& v) { v.push_back(Ratio); }

template<typename Obj>
  void test_call_member(Obj& o, void (Obj::*f)()) { (o->*f)(); }

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
    calls.push_back(make_callback(&test3, 20, 30));
    calls.push_back(make_callback(&TestClass::test5, &tc));

    calls.push_back(make_callback(&TestClass::test4, &tc, std::string("asdf")));
    calls.push_back(make_callback(&TestClass::test6, &tc, 6));
    calls.push_back(make_callback(&TestClass::test7, &tc, 7, 8));
    
    for(std::vector<Callback*>::iterator i = calls.begin(); i != calls.end(); ++i)
      (*i)->call();
  }

  {
    std::vector<int> v;

    const int& ri = 7;
    
    Callback* a = make_callback<std::vector<int>, int>(&std::vector<int>::push_back, &v, ri);
    Callback* b = make_callback(&std::vector<int>::push_back, &v, 9);
    Callback* c = make_callback(&std::vector<int>::push_back, &v, 13);

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
    Callback* c = make_callback<std::vector<int> >(&visit_9, vis);
    Callback* d = make_callback<std::vector<int> >(&visit_8, vis);

    // szablonowa funkcja jako argument
    Callback* e = make_callback<std::vector<int> >(&visit_template<11>, vis);
    
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

  /*
    TODO: napraw blad kompilacji
  {
    TestClass tc("tc2");
    Callback* c = make_callback(&test_call_member, &tc, &TestClass::test5);
    c->call();
  }
  */
  
  /*
    TODO: usun blad
  {
    std::list<int> li;
    Callback* c = make_callback(&test_call_member<std::list<int> >, &li);
  }
  */
  /*
    TODO: usun ambigous call
  {
    std::vector<int> vi;
    vi.push_back(10);
    vi.push_back(56);
    vi.push_back(30);
    vi.push_back(120);
    vi.push_back(8);

    Callback* sort_vi = make_callback(&std::sort, vi.begin(), vi.end());
  }
  */

  /*
    TODO: usun blad
  {
    std::list<int> li;
    li.push_back(10);
    li.push_back(56);
    li.push_back(30);
    li.push_back(120);
    li.push_back(8);

    Callback* sort_li = make_callback(&std::list<int>::sort);
  }
  */
  
  return 0;
}

