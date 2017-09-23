#include "gtest/gtest.h"
#include "isomorphicTest"

extern bool array(int*, int *);

TEST(Isomorphic, Array) {
  EXPECT_TRUE(array(NULL, NULL));
}
