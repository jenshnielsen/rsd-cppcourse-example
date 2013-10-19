#include <memory>

#include "ReactionSystem.h"

#include <gtest/gtest.h>

using namespace reactor;

class ReactionSystemTest: public ::testing::Test {
protected:
  ReactionSystem myReactionSystem;
  std::shared_ptr<Species> myReactant1 = std::make_shared<Species>("myReactant1");
  std::shared_ptr<Species> myReactant2 = std::make_shared<Species>("myReactant2");  
  std::shared_ptr<Species> myReactant3 = std::make_shared<Species>("myReactant3");  
  std::shared_ptr<Species> myProduct1 = std::make_shared<Species>("myProduct1");
  std::shared_ptr<Species> myProduct2 = std::make_shared<Species>("myProduct2");
  std::shared_ptr<Reaction> myReaction = std::make_shared<Reaction>(5.0);

  ReactionSystemTest():
    myReactionSystem()
  { 
    myReactant1->SetConcentration(1.0);
    myReactant2->SetConcentration(2.0);
    myReactant3->SetConcentration(3.0);
    myProduct1->SetConcentration(5.0);
    myProduct2->SetConcentration(6.0);
    myReaction->AddSpeciesToReactants(myReactant1);
    myReaction->AddSpeciesToReactants(myReactant2);
    myReaction->AddSpeciesToReactants(myReactant3);
    myReaction->AddSpeciesToProducts(myProduct1);
    myReaction->AddSpeciesToProducts(myProduct2);
  };
};

TEST_F(ReactionSystemTest, ReactionSystemCanAddSpecies){
  myReactionSystem.AddSpecies(myReactant1);
  myReactionSystem.AddSpecies(myReactant2);
  ASSERT_EQ(2,myReactionSystem.GetSpecies().size());
  EXPECT_EQ(myReactant1,myReactionSystem.GetSpecies()[0]);
  EXPECT_EQ(myReactant2,myReactionSystem.GetSpecies()[1]);

}

TEST_F(ReactionSystemTest, ReactionSystemSpeciesCanBeModifiedByPointer){
  myReactionSystem.AddSpecies(myReactant1);
  EXPECT_EQ(1.0,myReactionSystem.GetSpecies()[0]->GetConcentration());
  myReactant1->SetConcentration(11.0);
  EXPECT_EQ(11.0,myReactionSystem.GetSpecies()[0]->GetConcentration()); 
}

TEST_F(ReactionSystemTest, ReactionSystemCanAddReaction){
  myReactionSystem.AddReaction(myReaction);
  ASSERT_EQ(1,myReactionSystem.GetReactions().size());
  EXPECT_EQ(myReaction,myReactionSystem.GetReactions()[0]);

}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
