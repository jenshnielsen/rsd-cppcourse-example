#include "Reaction.h" // Include the code that we are testing
#include <gtest/gtest.h> // Include the google test framework

using namespace reactor;


TEST(ReactionTest, ReactionCanBeInitiated) { // First argument is test group, second is test name
  Reaction myReaction(); 
}

int main(int argc, char **argv) { // A main function scaffold to call the tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
