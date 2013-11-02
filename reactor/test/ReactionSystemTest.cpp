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

    myReaction->AddSpeciesToReactants(myReactant1);
    myReaction->AddSpeciesToReactants(myReactant2);
    myReaction->AddSpeciesToReactants(myReactant3);
    myReaction->AddSpeciesToProducts(myProduct1);
    myReaction->AddSpeciesToProducts(myProduct2);

    
    myReverseReaction->AddSpeciesToProducts(myReactant1);
    myReverseReaction->AddSpeciesToProducts(myReactant2);
    myReverseReaction->AddSpeciesToProducts(myReactant3);
    myReverseReaction->AddSpeciesToReactants(myProduct1);
    myReverseReaction->AddSpeciesToReactants(myProduct2);

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

TEST_F(ReactionSystemTest, ReactionSystemGetRatesOfChange){
  auto rateofchange = myReactionSystem.GetRatesOfChange();
  double forwardrateofchange = -5.0*1.0*2.0*3.0+2.0*5.0*6.0;
  // -fluxforward*myReactant1*myReactant2*myReactant3+fluxreverse*myproduct1*myproduct2
  double reverserateofchange = -forwardrateofchange;
  std::vector<double> expectedrateofchange = {forwardrateofchange,
  forwardrateofchange,forwardrateofchange,reverserateofchange,
  reverserateofchange};
  EXPECT_EQ(expectedrateofchange,rateofchange);
}

TEST_F(ReactionSystemTest, GetConcentrations){
  auto concentrations = myReactionSystem.GetConcentrations();
  std::vector<double> expectedconcentrations = {1.0,2.0,3.0,5.0,6.0};
  EXPECT_EQ(expectedconcentrations,concentrations);
}

TEST_F(ReactionSystemTest, SetConcentrations){
  auto concentrations = myReactionSystem.GetConcentrations();
  std::vector<double> expectedconcentrations = {1.0,2.0,3.0,5.0,6.0};
  EXPECT_EQ(expectedconcentrations,concentrations);
  std::vector<double> newexpectedconcentrations = {7.0,4.0,3.0,9.0,11.0};
  myReactionSystem.SetConcentrations(newexpectedconcentrations);
  auto newconcentrations = myReactionSystem.GetConcentrations();
  EXPECT_EQ(newexpectedconcentrations,newconcentrations);
}


TEST_F(ReactionSystemTest, SettingConcentrationsChangesRates){
  auto rateofchange = myReactionSystem.GetRatesOfChange();
  double forwardrateofchange = -5.0*1.0*2.0*3.0+2.0*5.0*6.0;
  double reverserateofchange = -forwardrateofchange;
  std::vector<double> expectedrateofchange = {forwardrateofchange,
  forwardrateofchange,forwardrateofchange,reverserateofchange,
  reverserateofchange};
  EXPECT_EQ(expectedrateofchange,rateofchange);

  std::vector<double> newexpectedconcentrations = {7.0,4.0,3.0,9.0,11.0};
  myReactionSystem.SetConcentrations(newexpectedconcentrations);

  auto newrateofchange = myReactionSystem.GetRatesOfChange();
  double newforwardrateofchange = -5.0*7.0*4.0*3.0+2.0*9.0*11.0;
  double newreverserateofchange = -newforwardrateofchange;
  std::vector<double> newexpectedrateofchange = {newforwardrateofchange,
  newforwardrateofchange,newforwardrateofchange,newreverserateofchange,
  newreverserateofchange};
  EXPECT_EQ(newexpectedrateofchange,newrateofchange);
  
}


TEST_F(ReactionSystemTest, SetConcentrationsAndGetRatesOfChange){
  std::vector<double> newconcentrations = {3.0,9.0,1.0,5.0,19.0};
  std::vector<double> newrates;
  myReactionSystem.GetRatesOfChangeGivenConcentrations(newconcentrations,newrates);
  double newforwardrateofchange = -5.0*3.0*9.0*1.0+2.0*5.0*19.0;
  double newreverserateofchange = -newforwardrateofchange;
  std::vector<double> newexpectedrateofchange = {newforwardrateofchange,
  newforwardrateofchange,newforwardrateofchange,newreverserateofchange,
  newreverserateofchange};
  EXPECT_EQ(newexpectedrateofchange,newrates);
  
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
