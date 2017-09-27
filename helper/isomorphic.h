#include <iostream>
#include <typeinfo>
#include <string>
#include "../assignment/project_1/2000000000/Region.h"
#include "../assignment/project_1/2000000000/Employment.h"
#include "../assignment/project_1/2000000000/BST.h"

using namespace std;

template<typename T>
bool isomorphic_bst(T* M1, T* M2);
template<typename T>
bool isomorphic_cll(T* M1, T* M2);
template<typename T>
bool isomorphic_2dll(T* M1, T* M2);
template<typename T>
bool isomorphic_linkedlist(T* M1, T* M2);
template<typename T>
bool isomorphic_node(T* M1, T* M2);
template<typename T>
bool isomorphic_binarynode(T* M1, T* M2);
template<typename T>
bool isomorphic_node_iterative(T* M1, T* M2);

bool isDataNotEqual(Region* M1, Region* M2);
bool isDataNotEqual(Employment* M1, Employment* M2);

template<typename T>
bool isIsomorphic(T* M1, T* M2) {
	if(typeid(*M1) == typeid(BST))							     return isomorphic_bst(M1, M2);
	else if(typeid(*M1) == typeid(List_Circular))   return isomorphic_cll(M1, M2);
	else if(typeid(*M1) == typeid(List_2D))         return isomorphic_2dll(M1, M2);
	else                               return false;
}

template<typename T>
bool isomorphic_bst(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  return isomorphic_binarynode(M1->root, M2->root);
}

template<typename T>
bool isomorphic_cll(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  return isomorphic_node_iterative(M1->pHead, M2->pHead);
}

template<typename T>
bool isomorphic_2dll(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  return isomorphic_linkedlist(M1->pHead, M2->pHead);
}

template<typename T>
bool isomorphic_linkedlist(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(isDataNotEqual(M1, M2)) return false;

  return isomorphic_node(M1->pDown, M2->pDown)
    && isomorphic_linkedlist(M1->pNext, M2->pNext);
}

template<typename T>
bool isomorphic_node(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  return isomorphic_node(M1->pDown,M2->pDown);
}

template<typename T>
bool isomorphic_binarynode(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(isDataNotEqual(M1, M2)) return false;

  return isomorphic_binarynode(M1->pLeft,M2->pLeft)
    && isomorphic_binarynode(M1->pRight,M2->pRight);
}

template<typename T>
bool isomorphic_node_iterative(T* M1, T* M2) {
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

bool isDataNotEqual(Region* M1, Region* M2) {
  return strcmp(M1->rCodeName.first,M2->rCodeName.first)
    || strcmp(M1->rCodeName.second,M2->rCodeName.second);
}

bool isDataNotEqual(Employment* M1, Employment* M2) {
  return  strcmp(M1->rCodeName.first,M2->rCodeName.first) ||
          strcmp(M1->rCodeName.second,M2->rCodeName.second) ||
          strcmp(M1->company,M2->company) ||
          strcmp(M1->qualification,M2->qualification) ||
          strcmp(M1->working_condition,M2->working_condition) ||
          strcmp(M1->to,M2->to);
}
