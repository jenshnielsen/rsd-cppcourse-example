#include <memory>

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
    myReactant1.SetConcentration(1.0);
    Species myReactant2("Reactant2");
    myReactant2.SetConcentration(2.0);
    Species myReactant3("Reactant3");
    myReactant3.SetConcentration(3.0);
    Species myProduct1("Product1");
    Species myProduct2("Product2");
    myReaction.AddSpeciesToReactants(std::make_shared<Species>(myReactant1));
    myReaction.AddSpeciesToReactants(std::make_shared<Species>(myReactant2));
    myReaction.AddSpeciesToReactants(std::make_shared<Species>(myReactant3));
    myReaction.AddSpeciesToProducts(std::make_shared<Species>(myProduct1));
    myReaction.AddSpeciesToProducts(std::make_shared<Species>(myProduct2));
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
  EXPECT_EQ("Reactant1",reactants[0]->GetName());
  EXPECT_EQ("Reactant2",reactants[1]->GetName());
  EXPECT_EQ("Reactant3",reactants[2]->GetName());
}

TEST_F(ReactionTest, ReactionReactantIsPointer){
  Species myNewReactant("NewReactant1");
  auto myNewReactantPtr = std::make_shared<Species>(myNewReactant);
  myReaction.AddSpeciesToReactants(myNewReactantPtr);
  auto reactants = myReaction.GetReactants();
  EXPECT_EQ(myNewReactantPtr.get(),reactants[3].get());
}


TEST_F(ReactionTest, ReactionProductNames){
  auto products = myReaction.GetProducts();
  EXPECT_EQ("Product1",products[0]->GetName());
  EXPECT_EQ("Product2",products[1]->GetName());
}

TEST_F(ReactionTest, ReactionFlux){
  auto flux = myReaction.CalculateFlux();
  EXPECT_EQ(flux,30.0);
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
