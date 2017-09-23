#include "gtest/gtest.h"

extern bool array(int*, int *);

TEST(Array,Root_has_null) {
  int validArray[6] = {0,};

  EXPECT_TRUE(array(NULL, NULL));
  EXPECT_FALSE(array(NULL, validArray));
  EXPECT_FALSE(array(validArray, NULL));
}

TEST(Array,has_different_size) {
  int Array_size_of_6[6] = {1,2,3,4,5,6};
  int Array_size_of_7[7] = {1,2,3,4,5,6,7};

  EXPECT_FALSE(array(Array_size_of_6, Array_size_of_7));
}

TEST(Array,has_different_value) {
  int Array_1to6[6] = {1,2,3,4,5,6};
  int Array_multiples_of_2_from_1[6] = {1,2,4,8,16,32};
  int Array_divisors_of_12[6] = {1,2,3,4,6,12};


  EXPECT_FALSE(array(Array_1to6, Array_multiples_of_2_from_1));
  EXPECT_FALSE(array(Array_multiples_of_2_from_1,Array_divisors_of_12));
  EXPECT_FALSE(array(Array_divisors_of_12,Array_1to6));
}

TEST(Array,is_isomorphic) {
  int Array[6] = {1,2,3,4,5,6};
  int Array2[6] = {1,2,3,4,5,6};

  EXPECT_TRUE(array(Array, Array2));
}
