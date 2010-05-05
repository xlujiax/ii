#include <algorithm>
#include <iostream>
#include <string>

class external_counter_policy
{
  int* counter;
public:
  external_counter_policy()
    : counter(0) {}

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
    void increment(T*) { ++*counter; }
  template<typename T>
    void decrement(T*) { --*counter; }
  template<typename T>
    bool is_zero(T*) { return *counter == 0; }
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
  class transporter;

template <typename T,
	  typename counter_policy = external_counter_policy,
	  typename object_policy = standard_object_policy>
  class smart_ptr : private object_policy, private counter_policy
{
  T* ptr; // przechowywany obiekt
public:
  smart_ptr()
    : ptr(0) {}

  smart_ptr(const transporter<T, counter_policy, object_policy>& t)
  {
    ptr = t.ptr;
    const_cast<transporter<T, counter_policy, object_policy>&>(t).ptr = 0; // zło
  }
  
  smart_ptr<T>& operator=(const transporter<T, counter_policy, object_policy>& t)
  {
    counter_policy::decrement(ptr);
    if(counter_policy::is_zero(ptr))
    {
      counter_policy::dispose(ptr);
      object_policy::dispose(ptr);
    }
    ptr = t.ptr;
    const_cast<transporter<T, counter_policy, object_policy>&>(t).ptr = 0; // zło
    return *this;
  }

  explicit smart_ptr(T* p)
    : ptr(p) {}
  ~smart_ptr()
  {
    counter_policy::decrement(ptr);
    if(counter_policy::is_zero(ptr))
    {
      counter_policy::dispose(ptr);
      object_policy::dispose(ptr);
    }
  }
  smart_ptr& operator= (T* p)
  {
    counter_policy::decrement(ptr);
    if(counter_policy::is_zero(ptr))
    {
      counter_policy::dispose(ptr);
      object_policy::dispose(ptr);
    }
    ptr = p;
    return *this;
  }
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }
  T* get() const { return ptr; }
  void release() { ptr = 0; }
  void swap(smart_ptr& h) { std::swap(ptr,h.ptr); }
  void swap(T*& p) { std::swap(ptr,p); }
private:
  smart_ptr(const smart_ptr&);               // blok
  smart_ptr& operator= (const smart_ptr&); // blok
};

template <typename T,
	  typename counter_policy = external_counter_policy,
	  typename object_policy = standard_object_policy>
  class transporter : private object_policy, private counter_policy
{
  T* ptr;
public:
  transporter(smart_ptr<T>& h )
  {
    ptr = h.get();
    h.release();
  }
  transporter(const transporter<T>& t)
  {
    ptr = t.ptr;
    const_cast<transporter<T>&>(t).ptr = 0; // zło
  }
  ~transporter()
  {
    counter_policy::decrement(ptr);
    if(counter_policy::is_zero(ptr))
    {
      counter_policy::dispose(ptr);
      object_policy::dispose(ptr);
    }
  }
private:
  transporter(transporter<T>&); // blok
  transporter<T>& operator= (transporter<T>&); // blok
  friend class smart_ptr<T>;
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
};

transporter<noisy> factory(const std::string& id)
{
  smart_ptr<noisy> p(new noisy(id));
  return p;
}

transporter<noisy> interface()
{
  return factory("interface");
}

int main(int, char*[])
{
  smart_ptr<noisy> np(new noisy("main"));
  smart_ptr<noisy> nf(factory("factory"));
  smart_ptr<noisy> ni(interface());

  noisy* arr = new noisy[2];
  smart_ptr<noisy, external_counter_policy, standard_array_policy> na(arr);
  
  return 0;
}
