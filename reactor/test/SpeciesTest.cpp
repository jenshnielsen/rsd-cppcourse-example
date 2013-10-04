#include "Species.h" // Include the code that we are testing
#include <gtest/gtest.h> // Include the google test framework

using namespace reactor;

// Test that the system has a name as expected.
TEST(SpeciesTest, SpeciesHasAName) { // First argument is test group, second is test name
  Species mySpecies("SomeName"); // Create a species with a specified name
  EXPECT_EQ("SomeName", mySpecies.GetName()); // Assert that the name should be as expected
}

TEST(SpeciesTest, SpeciesDefaultConcentration) { // First argument is test group, second is test name
  Species mySpecies("SomeName"); // Create a species with a specified name
  EXPECT_EQ(0, mySpecies.GetConcentration()); // Assert that the name should be as expected
}

TEST(SpeciesTest, SpeciesSetConcentration) { // First argument is test group, second is test name
  Species mySpecies("SomeName"); // Create a species with a specified name
  const double & my_concentration = 1.0;
  mySpecies.SetConcentration(my_concentration);
  EXPECT_EQ(1.0, mySpecies.GetConcentration()); // Assert that the name should be as expected
}

int main(int argc, char **argv) { // A main function scaffold to call the tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
