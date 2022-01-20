#pragma once
#include <memory>
#include <iostream>

class tp{
private:
  int* p;
  int* meta;
public:
  tp(){
    std::cout << "def constructor\n";
    p = new int[10];
    meta = new int[5];
  };

  tp(const tp& item){
    std::cout << "copy constructor\n";
    p = new int[10];
    meta = new int[5];
    for(int i =0; i < 10; ++i)
      p[i] = item.p[i];
  }

  tp(tp&& item){
    std::cout << "move constructor\n";
    p = item.p;
    item.p = nullptr;
  }

  ~tp(){
    std::cout << "destructor\n";
    if(p != nullptr){
      std::cout << "data deleted\n";
      delete[] p;
    }
    if(meta != nullptr){
      std::cout << "meta deleted\n";
      delete[] meta;
    }
  };
};


template<class T>
class vector{
private:
  T*     _data;
  size_t _count;
  size_t _capacity;
  struct iterator{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    
    iterator(pointer ptr) : _ptr(ptr) {}
    reference operator*() const {return *_ptr;}
    pointer operator->() {return _ptr; }
    iterator& operator++() {++_ptr; return *this;}
    iterator operator++(int) {auto res = *this; ++(*this); return res;}

    friend bool operator== (const iterator& a, const iterator& b) { return a._ptr == b._ptr; };
    friend bool operator!= (const iterator& a, const iterator& b) { return a._ptr != b._ptr; };

  private:
    pointer _ptr;
  };
public:
  vector();
  vector(size_t size);
  T& operator[](size_t index);
  size_t size();
  size_t capacity();
  void push_back(const T& item);
  iterator begin();
  iterator end();
  ~vector();
};

template<class T>
vector<T>::vector() : _data(nullptr), _count(0), _capacity(0){}

template<class T>
vector<T>::vector(size_t size) : _data(static_cast<T*>(malloc(size * sizeof(T)))), _count(size), _capacity(size){
  for(size_t i = 0; i < size; ++i)
    new(_data + i) T();
}

template<class T>
T& vector<T>::operator[](size_t index){
  if(index < 0 || index >= _count)
    throw 1;

  return _data[index];
}

template<class T>
size_t vector<T>::size(){
  return _count;
}

template<class T>
size_t vector<T>::capacity(){
  return _capacity;
}

template<class T>
void vector<T>::push_back(const T& item){
  if(_count >= _capacity){
   ++_capacity *= 2;
    T* tmp_p = _data;
    _data = static_cast<T*>(malloc(_capacity * sizeof(T)));
    for(size_t i = 0; i < _count; ++i)
      new (_data + i) T(std::move(tmp_p[i]));
    for(int i = 0; i < _count; ++i)
      (tmp_p + i)->~T();
    if(tmp_p != nullptr)
      free(tmp_p);
  }
  
  new(_data + _count) T(item);
  ++_count;
}

template<class T>
vector<T>::~vector(){
  for(int i = 0; i < _count; ++i)
    (_data + i)->~T();
  if(_data != nullptr)
    free(_data);

}

template<class T>
typename vector<T>::iterator vector<T>::begin(){
  return iterator(&(_data[0]));
}

template<class T>
typename vector<T>::iterator vector<T>::end(){
  return iterator(&(_data[_count]));
}



