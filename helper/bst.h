#include <iostream>
#pragma once

template<typename T>
class binary_node
{
public:
  T value;
  binary_node* left;
  binary_node* right;
public:
  binary_node(T);
  ~binary_node();

  void  setValue(T);
  void  setLeft(binary_node*);
  void  setRight(binary_node*);

  T   getValue();
  binary_node* getLeft();
  binary_node* getRight();
};

/*declaration*/
template<typename T>
binary_node<T>::binary_node(T _value = 0): value(_value), left(NULL), right(NULL) {}

template<typename T>
binary_node<T>::~binary_node() {
  delete left;
  delete right;
  left=NULL;
  right=NULL;
}

template<typename T>
void binary_node<T>::setValue(T value) {
  this->value = value;
}

template<typename T>
void binary_node<T>::setLeft(binary_node* left) {
  this->left = left;
}

template<typename T>
void binary_node<T>::setRight(binary_node* right) {
  this->right = right;
}

template<typename T>
T binary_node<T>::getValue() {
  return this->value;
}

template<typename T>
binary_node<T>* binary_node<T>::getLeft() {
  return this->left;
}

template<typename T>
binary_node<T>* binary_node<T>::getRight() {
  return this->next;
}
