#include <memory>

#include "ReactionSystem.h"

#include <gtest/gtest.h>

using namespace reactor;

class ReactionSystemTest: public ::testing::Test {
protected:
  ReactionSystem myReactionSystem;

  ReactionSystemTest():
    myReactionSystem()
  {
    auto myReaction = myReactionSystem.AddReaction(5.0);
    auto myReverseReaction = myReactionSystem.AddReaction(2.0);
    auto myReactant1 = myReactionSystem.AddSpecies("myReactant1");
    auto myReactant2 = myReactionSystem.AddSpecies("myReactant2");
    auto myReactant3 = myReactionSystem.AddSpecies("myReactant3");
    auto myProduct1 = myReactionSystem.AddSpecies("myProduct1");
    auto myProduct2 = myReactionSystem.AddSpecies("myProduct2");
    myReactant1->SetConcentration(1.0);
    myReactant2->SetConcentration(2.0);
    myReactant3->SetConcentration(3.0);
    myProduct1->SetConcentration(5.0);
    myProduct2->SetConcentration(6.0);

    myReaction->AddSpeciesToReactants(myReactant1.get());
    myReaction->AddSpeciesToReactants(myReactant2.get());
    myReaction->AddSpeciesToReactants(myReactant3.get());
    myReaction->AddSpeciesToProducts(myProduct1.get());
    myReaction->AddSpeciesToProducts(myProduct2.get());

    
    myReverseReaction->AddSpeciesToProducts(myReactant1.get());
    myReverseReaction->AddSpeciesToProducts(myReactant2.get());
    myReverseReaction->AddSpeciesToProducts(myReactant3.get());
    myReverseReaction->AddSpeciesToReactants(myProduct1.get());
    myReverseReaction->AddSpeciesToReactants(myProduct2.get());

  };
};

TEST_F(ReactionSystemTest, ReactionSystemCanAddSpecies){
  auto myTestSpecies = myReactionSystem.AddSpecies("myTestSpecies");
  ASSERT_EQ(6,myReactionSystem.GetSpecies().size());
  EXPECT_EQ(myTestSpecies,myReactionSystem.GetSpecies()[5]);
}

TEST_F(ReactionSystemTest, ReactionSystemSpeciesCanBeModifiedByPointer){
  auto myNewReactant1 = myReactionSystem.AddSpecies("myNewReactant1");
  myNewReactant1->SetConcentration(1.0);
  EXPECT_EQ(1.0,myReactionSystem.GetSpecies()[5]->GetConcentration());
  myNewReactant1->SetConcentration(11.0);
  EXPECT_EQ(11.0,myReactionSystem.GetSpecies()[5]->GetConcentration()); 
}

TEST_F(ReactionSystemTest, ReactionSystemCanAddReaction){
  auto myReaction = myReactionSystem.AddReaction(7.0);
  ASSERT_EQ(3,myReactionSystem.GetReactions().size());
  EXPECT_EQ(myReaction,myReactionSystem.GetReactions()[2]);
}


TEST_F(ReactionSystemTest, ReactionSystemCanAddMultipleReactions){
  auto myReaction1 = myReactionSystem.AddReaction(2.3);
  auto myReaction2 = myReactionSystem.AddReaction(5.3);
  ASSERT_EQ(4,myReactionSystem.GetReactions().size());
  EXPECT_EQ(myReaction1,myReactionSystem.GetReactions()[2]);
  EXPECT_EQ(myReaction2,myReactionSystem.GetReactions()[3]);
}

TEST_F(ReactionSystemTest, ReactionSystemGetRateOfChange){
  auto rateofchange = myReactionSystem.GetRateOfChange();
  EXPECT_EQ(-5.0*2.0*3.0*1.0+5.0*6.0*2.0,rateofchange[0]);
  EXPECT_EQ(-5.0*2.0*3.0*1.0+5.0*6.0*2.0,rateofchange[1]);
  EXPECT_EQ(-5.0*2.0*3.0*1.0+5.0*6.0*2.0,rateofchange[2]);
  EXPECT_EQ(+5.0*2.0*3.0*1.0-5.0*6.0*2.0,rateofchange[3]);
  EXPECT_EQ(+5.0*2.0*3.0*1.0-5.0*6.0*2.0,rateofchange[4]);
}


int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
