#pragma once
#include <memory>
#include <iostream>

namespace cc
{

  template <typename K, typename T>
  class RB_tree
  {
  private:
    enum
    {
      RED = 0,
      BLACK = 1
    };

    enum
    {
      LEFT = 0,
      RIGHT = 1
    };
    
    class rb_node
    {
    private:
      K key;
      T value;
      bool color;

      rb_node *p_left_child;
      rb_node *p_right_child;

    public:
      rb_node() = delete;
      rb_node(const rb_node &node) = delete;
      rb_node(K&& _key, T&& _value, bool _color) : key(_key), value(_value), color(_color), p_left_child(nullptr), p_right_child(nullptr) { std::cout << "param\n"; };
      rb_node(rb_node &&rv_node);

      void insert(rb_node&& node, bool side) { (side == LEFT ? p_left_child = new rb_node(node) : p_right_child = new rb_node(node)); };
      T&   get_value() { return value; };
      ~rb_node();
    };

    rb_node* root;
    int count;
  public:
    RB_tree() : root(nullptr), count(0) {};

    void push(K&& _key, T&& _value);
    T&   get_value(const K& key);

    ~RB_tree();
  };

  template <typename K, typename T>
  RB_tree<K,T>::rb_node::rb_node(rb_node &&rv_node) {
    key = std::move(rv_node.key);
    value = std::move(rv_node.value);
    color = rv_node.color;

    p_left_child = rv_node.p_left_child;
    p_right_child = rv_node.p_right_child;

    rv_node.p_left_child = nullptr;
    rv_node.p_right_child = nullptr;

    std::cout << "move-const\n";
  }

  template <typename K, typename T>
  RB_tree<K,T>::rb_node::~rb_node(){
    if(p_left_child != nullptr)
      delete p_left_child;
    if(p_right_child != nullptr)
      delete p_right_child;
  }

  template <typename K, typename T>
  void RB_tree<K,T>::push(K&& _key, T&& _value){
    if(count == 0){
      root = new rb_node(std::forward<K>(_key), std::forward<T>(_value), RED);
      ++count;
    }
  }

  template <typename K, typename T>
  RB_tree<K,T>::~RB_tree(){
    if(root != nullptr)
      delete root;
  }

  template <typename K, typename T>
  T& RB_tree<K,T>::get_value(const K& key){

    return root->get_value();
  }

  // vector


  template <class T>
  class vector
  {
  private:
    T *_data;
    size_t _count;
    size_t _capacity;
    struct iterator
    {
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = T;
      using pointer = T *;
      using reference = T &;

      iterator(pointer ptr) : _ptr(ptr) {}
      reference operator*() const { return *_ptr; }
      pointer operator->() { return _ptr; }
      iterator &operator++()
      {
        ++_ptr;
        return *this;
      }
      iterator operator++(int)
      {
        auto res = *this;
        ++(*this);
        return res;
      }

      friend bool operator==(const iterator &a, const iterator &b) { return a._ptr == b._ptr; };
      friend bool operator!=(const iterator &a, const iterator &b) { return a._ptr != b._ptr; };

    private:
      pointer _ptr;
    };

  public:
    vector();
    vector(size_t size);
    T &operator[](size_t index);
    size_t size();
    size_t capacity();
    void push_back(const T &item);
    iterator begin();
    iterator end();
    ~vector();
  };

  template <class T>
  vector<T>::vector() : _data(nullptr), _count(0), _capacity(0) {}

  template <class T>
  vector<T>::vector(size_t size) : _data(static_cast<T *>(malloc(size * sizeof(T)))), _count(size), _capacity(size)
  {
    for (size_t i = 0; i < size; ++i)
      new (_data + i) T();
  }

  template <class T>
  T &vector<T>::operator[](size_t index)
  {
    if (index < 0 || index >= _count)
      throw 1;

    return _data[index];
  }

  template <class T>
  size_t vector<T>::size()
  {
    return _count;
  }

  template <class T>
  size_t vector<T>::capacity()
  {
    return _capacity;
  }

  template <class T>
  void vector<T>::push_back(const T &item)
  {
    if (_count >= _capacity)
    {
      ++_capacity *= 2;
      T *tmp_p = _data;
      _data = static_cast<T *>(malloc(_capacity * sizeof(T)));
      for (size_t i = 0; i < _count; ++i)
        new (_data + i) T(std::move(tmp_p[i]));
      for (int i = 0; i < _count; ++i)
        (tmp_p + i)->~T();
      if (tmp_p != nullptr)
        free(tmp_p);
    }

    new (_data + _count) T(item);
    ++_count;
  }

  template <class T>
  vector<T>::~vector()
  {
    for (int i = 0; i < _count; ++i)
      (_data + i)->~T();
    if (_data != nullptr)
      free(_data);
  }

  template <class T>
  typename vector<T>::iterator vector<T>::begin()
  {
    return iterator(&(_data[0]));
  }

  template <class T>
  typename vector<T>::iterator vector<T>::end()
  {
    return iterator(&(_data[_count]));
  }

};

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
