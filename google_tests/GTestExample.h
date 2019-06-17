#ifndef CPP_STARTER_PROJECT_GTESTEXAMPLE_H
#define CPP_STARTER_PROJECT_GTESTEXAMPLE_H

#include "gtest/gtest.h"

// Class GTestExample adapted from:
// https://github.com/google/googletest/blob/master/googletest/docs/primer.md
class GTestExample : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  GTestExample() {
    // You can do set-up work for each test here.
  }

  ~GTestExample() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

#endif //CPP_STARTER_PROJECT_GTESTEXAMPLE_H
