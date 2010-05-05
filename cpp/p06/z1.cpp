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
    if(p != ptr)
      counter_policy::init(ptr);
    ptr = p;
  }
  smart_ptr(const smart_ptr& s)
    : counter_policy(s), object_policy(s), ptr(s.ptr)
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
  T& operator[](int i) { return ptr[i]; }
  const T& operator[](int i) const { return ptr[i]; }
  T* get() const { return ptr; }
  bool active() { return ptr != 0; }
  void release() { ptr = 0; }

  int get_counter() const { return *counter_policy::counter; }
};

class noisy
{
  std::string id;
  bool safe_to_delete;
public:
  static int instances_alive;
public:
  noisy(const std::string& i = std::string("array"))
    : id(i), safe_to_delete(false)
  {
    for(int i = 0; i < instances_alive; ++i) std::cout << '.';
    ++instances_alive;
    std::cout << "noisy(" << id << ")" << std::endl;
  }
  ~noisy()
  {
    --instances_alive;

    for(int i = 0; i < instances_alive; ++i) std::cout << '.';

    if(!safe_to_delete)
    {
      std::cout << "~noisy(" << id << ") - unsafe deletion" << std::endl;
      exit(0);
    }
    std::cout << "~noisy(" << id << ")" << std::endl;
  }
  void greet() const
  {
    for(int i = 0; i < instances_alive; ++i) std::cout << '.';

    std::cout << "greet(" << id << ')' << std::endl;
  }
  void unlock_deletion() { safe_to_delete = true; }
};

int noisy::instances_alive = 0;

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
  {
    smart_ptr<noisy> np(new noisy("main"));
    np->greet();
    
    smart_ptr<noisy> nf(factory("factory"));
    nf->greet();
    
    smart_ptr<noisy> ni(interface());
    ni->greet();
    
    smart_ptr<noisy, external_counter_policy, standard_array_policy> na(new noisy[2]);
    
    smart_ptr<noisy> sn(new noisy("shared"));
    assert(sn.get_counter() == 1);

    sn->greet();
    
    {
      smart_ptr<noisy> sn2(sn);
      sn2->greet();
    
      assert(sn.get_counter() == 2);
    }
    
    assert(sn.get_counter() == 1);
    
    {
      smart_ptr<noisy> sn3(sn);
      sn3->greet();

      assert(sn.get_counter() == 2);
    }

    assert(sn.get_counter() == 1);

    {
      smart_ptr<noisy> sn4;
      sn4 = sn;

      sn4->greet();
      
      assert(sn.get_counter() == 2);
    }
    
    assert(sn.get_counter() == 1);
    
    sn->greet();

    np->unlock_deletion();
    nf->unlock_deletion();
    ni->unlock_deletion();
    sn->unlock_deletion();
    na[0].unlock_deletion();
    na[1].unlock_deletion();
  }

  std::cout << "Pozostało " << noisy::instances_alive << " instancji noisy" << std::endl;
  
  return 0;
}
