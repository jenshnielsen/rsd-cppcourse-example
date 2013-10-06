#include "Reaction.h" // Include the code that we are testing
#include "Species.h"

#include <gtest/gtest.h>

using namespace reactor;

class ReactionTest: public ::testing::Test {
protected:
  Reaction myReaction;
  ReactionTest():
    myReaction(5.0)
  {
    Species myReactant1("Reactant1");
    Species myReactant2("Reactant2");
    Species myReactant3("Reactant3");
    Species myProduct1("Product1");
    Species myProduct2("Product2");
    myReaction.AddSpeciesToReactants(myReactant1);
    myReaction.AddSpeciesToReactants(myReactant2);
    myReaction.AddSpeciesToReactants(myReactant3);
    myReaction.AddSpeciesToProducts(myProduct1);
    myReaction.AddSpeciesToProducts(myProduct2);
  };
};

TEST_F(ReactionTest, ReactionHasRate){
  EXPECT_EQ(5.0, myReaction.GetReactionRate());
}

TEST_F(ReactionTest, ReactionHasRightNumberOfReactants){
  EXPECT_EQ(3,myReaction.GetReactants().size());
}

TEST_F(ReactionTest, ReactionRigthNumberOfProducts){
  EXPECT_EQ(2,myReaction.GetProducts().size());
}

TEST_F(ReactionTest, ReactionReactantNames){
  auto reactants = myReaction.GetReactants();
  EXPECT_EQ("Reactant1",reactants[0].GetName());
  EXPECT_EQ("Reactant2",reactants[1].GetName());
  EXPECT_EQ("Reactant3",reactants[2].GetName());
}

TEST_F(ReactionTest, ReactionProductNames){
  auto products = myReaction.GetProducts();
  EXPECT_EQ("Product1",products[0].GetName());
  EXPECT_EQ("Product2",products[1].GetName());
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
