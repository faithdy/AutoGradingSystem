#include "bst.h"

template<typename T>
bool isomorphic_binarynode(binary_node<T>* M1, binary_node<T>* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(M1->value != M2->value) return false;

  return isomorphic_binarynode(M1->left,M2->left)
    && isomorphic_binarynode(M1->right,M2->right);
}
