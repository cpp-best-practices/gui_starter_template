#include "GTestExample.h"

TEST_F(GTestExample, AdditiveIdentity) {
  EXPECT_EQ(1 + 0, 1);
}

TEST_F(GTestExample, Inequality) {
  EXPECT_GT(1 + 1, 1);
  EXPECT_LT(1, 1 + 1);
  EXPECT_GE(1 + 1, 1);
  EXPECT_LE(1, 1 + 1);
}

TEST_F(GTestExample, Tautology) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}


