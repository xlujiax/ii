#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>

class external_counter_policy
{
  // todo: powinien być prywatny
protected:
  int* counter;
public:
  external_counter_policy()
    : counter(0) {}

  external_counter_policy(const external_counter_policy& e) : counter(e.counter) {}

  template<typename T>
    void init(T*)
  {
    counter = new int;
    *counter = 1;
  }

  template<typename T>
    void dispose(T*)
  {
    delete counter;
  }
  template<typename T> 
    void increment(T*) { assert(counter != NULL); ++*counter; }
  template<typename T>
    void decrement(T*) { assert(counter != NULL); --*counter; }
  template<typename T>
    bool is_zero(T*) { assert(counter != NULL); return *counter == 0; }
};

class standard_object_policy
{
public:
  template<typename T> void dispose(T* object)
  {
    delete object;
  }
};

class standard_array_policy
{
public:
  template<typename T> void dispose(T* array)
  {
    delete[] array;
  }
};


template <typename T,
	  typename counter_policy = external_counter_policy,
	  typename object_policy = standard_object_policy>
  class smart_ptr : private object_policy, private counter_policy
{
  T* ptr; // przechowywany obiekt
public:
  smart_ptr()
    : ptr(0) {}
  
  explicit smart_ptr(T* p)
  {
    std::cout << "explicit" << std::endl;
    if(p != ptr)
      counter_policy::init(ptr);
    ptr = p;
  }
  smart_ptr(const smart_ptr& s)
    : counter_policy(s), object_policy(s)
  {
    counter_policy::increment(ptr);
  }
  ~smart_ptr()
  {
    if(active())
    {
      assert(counter_policy::counter != NULL);

      counter_policy::decrement(ptr);
      if(counter_policy::is_zero(ptr))
      {
	counter_policy::dispose(ptr);
	object_policy::dispose(ptr);
      }
    }
  }
    
  smart_ptr& operator=(const smart_ptr& s)
  {
    counter_policy::operator=(s); // przypisanie polis
    object_policy::operator=(s);

    if(s.ptr != ptr)
    {
      // usuniecie aktualnego
      if(active())
      {
	counter_policy::decrement(ptr);
	if(counter_policy::is_zero(ptr))
	{
	  counter_policy::dispose(ptr);
	  object_policy::dispose(ptr);
	}
      }
      // i przejęcie nowego
      ptr = s.ptr;
      counter_policy::increment(ptr);
    }
  }
  
  smart_ptr& operator= (T* p)
  {
    if(p != ptr)
    {
      if(active())
      {
	counter_policy::decrement(ptr);
	if(counter_policy::is_zero(ptr))
	{
	  counter_policy::dispose(ptr);
	  object_policy::dispose(ptr);
	}
      }
      counter_policy::init(ptr);
      ptr = p;
    }
    return *this;
  }
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }
  T* get() const { return ptr; }
  bool active() { return ptr != 0; }
  void release() { ptr = 0; }

  int get_counter() const { return *counter_policy::counter; }
};

class noisy
{
  std::string id;
public:
  noisy(const std::string& i = std::string("array"))
    : id(i)
  {
    std::cout << "noisy(" << id << ")" << std::endl;
  }
  ~noisy() { std::cout << "~noisy(" << id << ")" << std::endl; }
  void greet() const { std::cout << "greet(" << id << ')' << std::endl; }
};

smart_ptr<noisy> factory(const std::string& id)
{
  smart_ptr<noisy> p(new noisy(id));
  return p;
}

smart_ptr<noisy> interface()
{
  return factory("interface");
}

int main(int, char*[])
{
  smart_ptr<noisy> np(new noisy("main"));
  smart_ptr<noisy> nf(factory("factory"));
  smart_ptr<noisy> ni(interface());

  smart_ptr<noisy, external_counter_policy, standard_array_policy> na(new noisy[2]);

  smart_ptr<noisy> sn(new noisy("shared"));
  assert(sn.get_counter() == 1);
  
  sn->greet();

  {
    smart_ptr<noisy> sn2(sn);
    assert(sn.get_counter() == 2);
    std::cout << "nie usuwaj jeszcze shared " << std::endl;
  }

  assert(sn.get_counter() == 1);

  std::cout << "in between " << sn.get_counter() << std::endl;

  {
    assert(sn.get_counter() == 1);
    smart_ptr<noisy> sn3(sn);
    assert(sn.get_counter() == 2);
    std::cout << "nie usuwaj jeszcze shared" << std::endl;
  }

  std::cout << "mozna usunac shared" << std::endl;

  sn->greet();

  //smart_ptr<noisy> sn3;
  //sn3 = sn;
  
  return 0;
}
