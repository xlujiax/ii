#include <algorithm>
#include <iostream>
#include <string>

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


template<typename T, typename object_policy>
  class transporter;

template <typename T,
	  typename object_policy = standard_object_policy>
class smart_ptr : private object_policy
{
  T* ptr; // przechowywany obiekt
public:
  smart_ptr()
    : ptr(0) {}

  smart_ptr(const transporter<T, object_policy>& t)
  {
    ptr = t.ptr;
    const_cast<transporter<T, object_policy>&>(t).ptr = 0; // zło
  }
  
  smart_ptr<T>& operator=(const transporter<T, object_policy>& t)
  {
    dispose(ptr);
    ptr = t.ptr;
    const_cast<transporter<T, object_policy>&>(t).ptr = 0; // zło
    return *this;
  }

  explicit smart_ptr(T* p)
    : ptr(p) {}
  ~smart_ptr() { dispose(ptr); }
  smart_ptr<T>& operator= (T* p)
  {
    dispose(ptr);
    ptr = p;
    return *this;
  }
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }
  T* get() const { return ptr; }
  void release() { ptr = 0; }
  void swap(smart_ptr<T>& h) { std::swap(ptr,h.ptr); }
  void swap(T*& p) { std::swap(ptr,p); }
private:
  smart_ptr (const smart_ptr<T>&);               // blok
  smart_ptr<T>& operator= (const smart_ptr<T>&); // blok
};

template <typename T,
	  typename object_policy = standard_object_policy>
  class transporter : private object_policy
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
  ~transporter() { delete ptr; }
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
  smart_ptr<noisy, standard_array_policy> na(arr);
  
  return 0;
}
