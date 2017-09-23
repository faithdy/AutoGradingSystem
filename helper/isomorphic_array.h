#include <iostream>
#define MAXKEY 4000000

//case 1 : array
template<typename T>
bool isomorphic_array(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  /*also, we set MAXKEY as dummy value. assume
    each element has key value less than MAXKEY,
    because we have not input parameter, length */
  if(*(int*)M1 > MAXKEY && *(int*)M2 > MAXKEY) return true;
  if(*(int*)M1 > MAXKEY || *(int*)M2 > MAXKEY) return false;

  if(*M1 != *M2) return false;

  return isomorphic_array(++M1,++M2);
}
