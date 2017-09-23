#include <iostream>

template<typename T>
class node
{
public:
  T value;
  node* next;
public:
  node(T);
  ~node();

  void  setValue(T);
  void  setNext(node*);
  T   getValue();
  node* getNext();
};

/*declaration*/
template<typename T>
node<T>::node(T _value = 0): value(_value), next(NULL) {}

template<typename T>
node<T>::~node() {
}

template<typename T>
void node<T>::setValue(T value) {
  this->value = value;
}

template<typename T>
void node<T>::setNext(node* next) {
  this->next = next;
}

template<typename T>
T node<T>::getValue() {
  return this->value;
}

template<typename T>
node<T>* node<T>::getNext() {
  return this->next;
}

// class linkedList {
// private:
//   node* header;
// public:
//   linkedList();
//   ~linkedList();
//
//   bool insert(int);
//   bool update(int, int);
//   bool search(int);
//   bool delete(int);
// }
