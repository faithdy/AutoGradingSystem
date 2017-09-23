#include "gtest/gtest.h"

extern bool array(int*, int *);

TEST(Isomorphic, Array) {
  EXPECT_TRUE(!array(NULL, NULL));
}
