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
  }
  return NULL;
}

template<typename T>
bool linkedList<T>::_delete(T value) {
  node<T> *prev = this->root;
  node<T> *target = search(value);
  node<T> *next = target->next;

  if(target == NULL) return false;

  if(prev == target) root = next;
  else while(prev->next!=target) prev = prev->next;
  prev->next = next;

  delete target;
  return true;
}
