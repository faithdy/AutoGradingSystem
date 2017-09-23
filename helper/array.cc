#include <iostream>
//case 1 : array
/*templateation need*/
bool array(int* M1, int* M2) {
  if(M1 == NULL || M2 == NULL) return false;

  if(*M1 != *M2) return false;

  return array(++M1,++M2);
}
