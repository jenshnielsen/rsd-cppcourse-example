#include <memory>

#include "Reaction.h" // Include the code that we are testing

#include <gtest/gtest.h>

using namespace reactor;

class ReactionTest: public ::testing::Test {
protected:
  Reaction myReaction;
  ReactionTest():
    myReaction(5.0)
  {
    auto myReactant1 = std::make_shared<Species>("Reactant1");
    myReactant1->SetConcentration(1.0);
    auto myReactant2 = std::make_shared<Species>("Reactant2");
    myReactant2->SetConcentration(2.0);
    auto myReactant3 = std::make_shared<Species>("Reactant3");
    myReactant3->SetConcentration(3.0);
    
    auto myProduct1 = std::make_shared<Species>("Product1");
    myProduct1->SetConcentration(5.0);
    auto myProduct2 = std::make_shared<Species>("Product2");
    myProduct2->SetConcentration(6.0);
    
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
  EXPECT_EQ("Reactant1",reactants[0]->GetName());
  EXPECT_EQ("Reactant2",reactants[1]->GetName());
  EXPECT_EQ("Reactant3",reactants[2]->GetName());
}

TEST_F(ReactionTest, ReactionReactantIsPointer){
  auto myNewReactant = std::make_shared<Species>("NewReactant1");
  myReaction.AddSpeciesToReactants(myNewReactant);
  auto reactants = myReaction.GetReactants();
  // get returns the C pointer. 
  EXPECT_EQ(myNewReactant.get(),reactants[3].get());
}

TEST_F(ReactionTest, ReactionProductNames){
  auto products = myReaction.GetProducts();
  EXPECT_EQ("Product1",products[0]->GetName());
  EXPECT_EQ("Product2",products[1]->GetName());
}

TEST_F(ReactionTest, ReactionFlux){
  auto flux = myReaction.GetFlux();
  EXPECT_EQ(30.0,flux);
}

 
TEST_F(ReactionTest, ReactionCanContributeToRatesOfChange) {
  myReaction.ContributeToRatesOfChange();
  auto reactants = myReaction.GetReactants();
  auto products = myReaction.GetProducts();
  EXPECT_EQ(-1.0*2.0*3.0*5.0, reactants[0]->GetRateOfChange());
  EXPECT_EQ(-1.0*2.0*3.0*5.0, reactants[1]->GetRateOfChange());
  EXPECT_EQ(-1.0*2.0*3.0*5.0, reactants[2]->GetRateOfChange());
  EXPECT_EQ(2.0*3.0*5.0, products[0]->GetRateOfChange());
  EXPECT_EQ(2.0*3.0*5.0, products[1]->GetRateOfChange());
}
 
TEST_F(ReactionTest, ReactionCanOutputToAStream) {
  std::ostringstream output_buffer;
  output_buffer << myReaction;

  EXPECT_EQ("Reactant1 + Reactant2 + Reactant3 > 5 > Product1 + Product2", output_buffer.str());
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
