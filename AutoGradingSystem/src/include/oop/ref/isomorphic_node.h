#include "linkedList.h"

template<typename T>
bool isomorphic_node(node<T>* M1, node<T>* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(M1->value != M2->value) return false;

  return isomorphic_node(M1->next,M2->next);
}
