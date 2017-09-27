#include "linkedList.h"

template<typename T>
bool isomorphic_node_iterative(T *M1, T* M2);

template<typename T>
bool isomorphic_circularlinkedList(circularlinkedList<T>* M1, circularlinkedList<T> *M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;
  return isomorphic_node_iterative(M1->root, M2->root);
}

template<typename T>
bool isomorphic_node_iterative(T *M1, T* M2) {
  T* Root1 = M1;
  T* Root2 = M2;

  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(M1->value != M2->value) return false;
  while(true) {
    if((M1 = M1->next)==NULL) return false;
    if((M2 = M2->next)==NULL) return false;

    if(M1->value != M2->value) return false;

    if(M1 == Root1 && M2 == Root2) return true;
    if(M1 == Root1 || M2 == Root2) return false;
  };
}
