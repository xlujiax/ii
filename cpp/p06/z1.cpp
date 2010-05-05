#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>

class external_counter_policy
{
protected:
  int* strong_counter;
  int* weak_counter;
public:
  external_counter_policy()
    : strong_counter(0), weak_counter(0) {}

  external_counter_policy(const external_counter_policy& e)
    : strong_counter(e.strong_counter), weak_counter(e.weak_counter) {}

  template<typename T>
    void init(T*)
  {
    strong_counter = new int;
    *strong_counter = 1;

    weak_counter = new int;
    *weak_counter = 0;
  }

  template<typename T>
    void dispose(T*)
  {
    delete strong_counter;
    delete weak_counter;
  }

  template<typename T> 
    void increment_strong(T*)
  {
    assert(strong_counter != NULL);
    ++*strong_counter;
  }
  template<typename T>
    void decrement_strong(T*)
  {
    assert(strong_counter != NULL);
    --*strong_counter;
  }
  template<typename T>
    bool strong_is_zero(T*)
  {
    assert(strong_counter != NULL);
    return *strong_counter == 0;
  }

  template<typename T> 
    void increment_weak(T*)
  {
    assert(weak_counter != NULL);
    ++*weak_counter;
  }
  template<typename T>
    void decrement_weak(T*)
  {
    assert(weak_counter != NULL);
    --*weak_counter;
  }
  template<typename T>
    bool weak_is_zero(T*)
  {
    assert(weak_counter != NULL);
    return *weak_counter == 0;
  }
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

template<typename T,
	 typename counter_policy,
	 typename object_policy>
  class weak_ptr;

template <typename T,
	  typename counter_policy = external_counter_policy,
	  typename object_policy = standard_object_policy>
  class count_ptr : private object_policy, private counter_policy
{
  T* ptr; // przechowywany obiekt

  friend class weak_ptr<T, counter_policy, object_policy>;
public:
  count_ptr()
    : ptr(0) {}
  
  explicit count_ptr(T* p)
  {
    if(p != ptr)
    {
      ptr = p;
      counter_policy::init(ptr);
    }
  }
  count_ptr(const count_ptr& s)
    : object_policy(s), counter_policy(s)
  {
    counter_policy::strong_counter = s.strong_counter;
    counter_policy::weak_counter = s.weak_counter;
    ptr = s.ptr;
    counter_policy::increment_strong(ptr);
  }
  ~count_ptr()
  {
    detach();
  }
    
  count_ptr& operator=(const count_ptr& s)
  {
    if(s.ptr != ptr)
    {
      detach();

      counter_policy::operator=(s); // przypisanie polis
      object_policy::operator=(s);

      counter_policy::strong_counter = s.strong_counter;
      counter_policy::weak_counter = s.weak_counter;
      ptr = s.ptr;
      counter_policy::increment_strong(ptr);
    }
    return *this;
  }
  
  count_ptr& operator= (T* p)
  {
    if(p != ptr)
    {
      detach();
      
      ptr = p;
      counter_policy::init(ptr);
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

  int get_counter() const { return *counter_policy::strong_counter; }
private:
  void detach()
  {
    if(active())
    {
      counter_policy::decrement_strong(ptr);
      if(counter_policy::strong_is_zero(ptr))
      {
	object_policy::dispose(ptr);
	
	if(counter_policy::weak_is_zero(ptr))
	  counter_policy::dispose(ptr);
      }
    }
  }
};

template<typename T,
  typename counter_policy = external_counter_policy,
  typename object_policy  = standard_object_policy>
class weak_ptr : private counter_policy, private object_policy
{
  T* ptr;
public:
  weak_ptr() : ptr(0) {}
  ~weak_ptr()
  {
    detach();
  }
  
  weak_ptr(const weak_ptr& wp)
    : counter_policy(wp), object_policy(wp)
  {
    detach();
    
    counter_policy::strong_counter = wp.strong_counter;
    counter_policy::weak_counter = wp.weak_counter;
    ptr = wp.ptr;

    counter_policy::increment_weak();
  }
  
  weak_ptr(const count_ptr<T,counter_policy,object_policy>& cp)
    : counter_policy(cp), object_policy(cp)
  {
    detach();
    
    counter_policy::strong_counter = cp.strong_counter;
    counter_policy::weak_counter = cp.weak_counter;
    ptr = cp.ptr;

    counter_policy::increment_weak();
  }
  weak_ptr& operator= (const weak_ptr& wp)
  {
    counter_policy::operator=(wp); // przypisanie polis
    object_policy::operator=(wp);

    detach();
    
    counter_policy::strong_counter = wp.strong_counter;
    counter_policy::weak_counter = wp.weak_counter;
    ptr = wp.ptr;

    counter_policy::increment_weak(ptr);
    return *this;
  }
  weak_ptr& operator= (const count_ptr<T,counter_policy,object_policy>& cp)
  {
    counter_policy::operator=(cp); // przypisanie polis
    object_policy::operator=(cp);

    detach();

    counter_policy::strong_counter = cp.strong_counter;
    counter_policy::weak_counter = cp.weak_counter;
    ptr = cp.ptr;

    counter_policy::increment_weak(ptr);
    return *this;
  }
  count_ptr<T,counter_policy,object_policy> lock() const
  {
    if(expired())
      return count_ptr<T, counter_policy, object_policy>();
    else
    {
      count_ptr<T, counter_policy, object_policy> cp(ptr);
      cp.strong_counter = counter_policy::strong_counter;
      cp.weak_counter = counter_policy::weak_counter;
      return cp;
    }
  }
  bool expired() const
  {
    return *counter_policy::strong_counter == 0;
  }
private:
  void detach()
  {
    if(ptr != 0)
    {
      counter_policy::decrement_weak(ptr);
      if(counter_policy::strong_is_zero(ptr) && counter_policy::weak_is_zero(ptr))
	counter_policy::dispose(ptr);
    }
  }
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

count_ptr<noisy> factory(const std::string& id)
{
  count_ptr<noisy> p(new noisy(id));
  return p;
}

count_ptr<noisy> interface()
{
  return factory("interface");
}

int main(int, char*[])
{
  {
    count_ptr<noisy> np(new noisy("main"));
    np->greet();
    
    count_ptr<noisy> nf(factory("factory"));
    nf->greet();
    
    count_ptr<noisy> ni(interface());
    ni->greet();
    
    count_ptr<noisy, external_counter_policy, standard_array_policy> na(new noisy[2]);
    
    np->unlock_deletion();
    nf->unlock_deletion();
    ni->unlock_deletion();
    na[0].unlock_deletion();
    na[1].unlock_deletion();

    np = new noisy("replaced");

    np->unlock_deletion();
  }
  
  {
    count_ptr<noisy> sn(new noisy("shared"));
    assert(sn.get_counter() == 1);

    sn->greet();
    
    {
      count_ptr<noisy> sn2(sn);
      sn2->greet();
    
      assert(sn.get_counter() == 2);
    }

    assert(sn.get_counter() == 1);
    
    {
      count_ptr<noisy> sn3(sn);
      sn3->greet();

      assert(sn.get_counter() == 2);
    }

    assert(sn.get_counter() == 1);

    {
      count_ptr<noisy> sn4;
      sn4 = sn;

      sn4->greet();
      
      assert(sn.get_counter() == 2);
    }
    
    assert(sn.get_counter() == 1);
    
    sn->greet();

    sn->unlock_deletion();
  }

  {
    weak_ptr<noisy> wp;

    {
      count_ptr<noisy> np(new noisy("expire please"));

      wp = np;

      assert(!wp.expired());
      
      np->unlock_deletion();
    }

    assert(wp.expired());
  }

  {
    weak_ptr<noisy> wp;
    
    count_ptr<noisy> np(new noisy("get strong pointer"));
    
    wp = np;
    
    count_ptr<noisy> w2c = wp.lock();
    w2c->greet();
    
    np->unlock_deletion();
  }

  std::cout << "Pozostało " << noisy::instances_alive << " instancji noisy" << std::endl;
  
  return 0;
}
