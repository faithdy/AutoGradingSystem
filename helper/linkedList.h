#include <iostream>
#pragma once

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

template<typename T>
class linkedList {
public:
  node<T>* root;
  linkedList();
  ~linkedList();

  bool insert(T);
  bool update(T, T);
  node<T>* search(T);
  bool _delete(T);
};

template<typename T>
linkedList<T>::linkedList() {
  this->root = NULL;
}

template<typename T>
linkedList<T>::~linkedList() {
  /*must filled*/
}

template<typename T>
bool linkedList<T>::insert(T value) {
  node<T> *horse = this->root;

  if(horse==NULL) this->root = new node<T>(value);
  else {
    while(horse->next) horse = horse->next;
    horse->next = new node<T>(value);
  } return true;
}

template<typename T>
bool linkedList<T>::update(T oldValue, T newValue) {
  node<T> *target = search(oldValue);
  if(target == NULL) return false;

  target->value = newValue;
  return true;
}

template<typename T>
node<T>* linkedList<T>::search(T value) {
  node<T> *horse = this->root;
  while(horse) {
    if(horse->value == value) return horse;
    else horse = horse->next;
  } return NULL;
}

template<typename T>
bool linkedList<T>::_delete(T value) {
  node<T> *prev = this->root;
  node<T> *target = search(value);
  if(target == NULL) return false;

  if(root == target) root = target->next;
  else {
    while(prev->next!=target) prev = prev->next;
    prev->next = target->next;
  }

  delete target;
  return true;
}

template<typename T>
class circularlinkedList {
public:
  node<T>* root;
  circularlinkedList();
  ~circularlinkedList();

  bool insert(T);
  bool update(T, T);
  node<T>* search(T);
  bool _delete(T);
};

template<typename T>
circularlinkedList<T>::circularlinkedList() {
  this->root = NULL;
}

template<typename T>
circularlinkedList<T>::~circularlinkedList() {}

template<typename T>
bool circularlinkedList<T>::insert(T value) {
  node<T> *horse = this->root;

  if(horse==NULL) {
    this->root = new node<T>(value);
    this->root->next = this->root;
  }
  else {
    while(horse->next!=root) horse = horse->next;
    horse->next = new node<T>(value);
    horse->next->next = root;
  } return true;
}

template<typename T>
bool circularlinkedList<T>::update(T oldValue, T newValue) {
  node<T> *target = search(oldValue);
  if(target == NULL) return false;

  target->value = newValue;
  return true;
}

template<typename T>
node<T>* circularlinkedList<T>::search(T value) {
  node<T> *horse = this->root;
  while(horse) {
    if(horse->value == value) return horse;
    if (horse->next == root) return NULL;
    else horse = horse->next;
  } return NULL;
}

template<typename T>
bool circularlinkedList<T>::_delete(T value) {
  node<T> *prev = this->root;
  node<T> *target = search(value);
  if(target == NULL) return false;

  if(root == target) {
    if(root == root->next) root = NULL;
    else {
      node<T> *tail = this->root;
      while(tail->next != root) tail = tail->next;
      tail->next = root->next;
      root = root->next;
    }
  }

  else {
    while(prev->next!=target) prev = prev->next;
    prev->next = target->next;
  }

  delete target;
  return true;
}
