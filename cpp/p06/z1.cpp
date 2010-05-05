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

template<typename ObjectType,
          typename CountT,
          CountT ObjectType::*CountPtr>
class member_counter_policy
{
public:
  void init(ObjectType* object) { object->*CountPtr = 1; }
  void dispose (ObjectType*) {}
  void increment(ObjectType* object) { ++(object->*CountPtr); }
  void decrement(ObjectType* object) { --(object->*CountPtr); }
  bool is_zero(ObjectType* object) { return (object->*CountPtr) == 0; }
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
  class count_ptr : private object_policy, private counter_policy
{
  T* ptr; // przechowywany obiekt
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
    : object_policy(s), counter_policy(s), ptr(s.ptr)
  {
    counter_policy::increment(ptr);
  }
  ~count_ptr()
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
  }
    
  count_ptr& operator=(const count_ptr& s)
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
    return *this;
  }
  
  count_ptr& operator= (T* p)
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

class noisy_member : public noisy
{
public:
  int ref_count;
  
  typedef count_ptr<
    noisy_member,
    member_counter_policy<
      noisy_member,
      int,
      &noisy_member::ref_count
      >
    > pointer;

  noisy_member(const std::string& s = std::string("array_member")) : noisy(s) {}
};

count_ptr<noisy> factory(const std::string& id)
{
  count_ptr<noisy> p(new noisy(id));
  return p;
}

count_ptr<noisy> interface()
{
  return factory("interface");
}

noisy_member::pointer factory_member(const std::string& id)
{
  noisy_member::pointer p(new noisy_member(id));
  return p;
}

noisy_member::pointer interface_member()
{
  return factory_member("interface");
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
    noisy_member::pointer sn(new noisy_member("shared member"));
    assert(sn->ref_count == 1);

    sn->greet();
    
    {
      noisy_member::pointer sn2(sn);
      sn2->greet();
    
      assert(sn->ref_count == 2);
    }
    
    assert(sn->ref_count == 1);
    
    {
      noisy_member::pointer sn3(sn);
      sn3->greet();

      assert(sn->ref_count == 2);
    }

    assert(sn->ref_count == 1);

    {
      noisy_member::pointer sn4;
      sn4 = sn;

      sn4->greet();
      
      assert(sn->ref_count == 2);
    }
    
    assert(sn->ref_count == 1);
    
    sn->greet();

    sn->unlock_deletion();
  }

  std::cout << "Pozostało " << noisy::instances_alive << " instancji noisy" << std::endl;
  
  return 0;
}
