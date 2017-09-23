#include <iostream>
#define MAXKEY 4000000
using namespace std;
//case 1 : array
/*templateation need*/
template<typename T>
bool array(T* M1, T* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  /*also, we set MAXKEY as dummy value. assume
    each element has key value less than MAXKEY,
    because we have not input parameter, length */
  if(*M1 > MAXKEY && *M2 > MAXKEY) return true;
  if(*M1 > MAXKEY || *M2 > MAXKEY) return false;

  if(*M1 != *M2) return false;

  return array(++M1,++M2);
}
