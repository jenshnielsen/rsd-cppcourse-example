#include <memory>

#include "ReactionSystem.h"

#include <gtest/gtest.h>

using namespace reactor;

class ReactionSystemTest: public ::testing::Test {
protected:
  ReactionSystem myReactionSystem;
  Species myReactant1 = Species("myReactant1");
  Species myReactant2 = Species("myReactant2");
  Species myReactant3 = Species("myReactant3");
  Species myProduct1 = Species("myProduct1");
  Species myProduct2 = Species("myProduct2");
  Reaction myReaction = Reaction(5.0);
  Reaction myReverseReaction = Reaction(2.0);


  ReactionSystemTest():
    myReactionSystem()
  { 
    myReactant1.SetConcentration(1.0);
    myReactant2.SetConcentration(2.0);
    myReactant3.SetConcentration(3.0);
    myProduct1.SetConcentration(5.0);
    myProduct2.SetConcentration(6.0);
    myReaction.AddSpeciesToReactants(myReactant1);
    myReaction.AddSpeciesToReactants(myReactant2);
    myReaction.AddSpeciesToReactants(myReactant3);
    myReaction.AddSpeciesToProducts(myProduct1);
    myReaction.AddSpeciesToProducts(myProduct2);
    myReverseReaction.AddSpeciesToProducts(myReactant1);
    myReverseReaction.AddSpeciesToProducts(myReactant2);
    myReverseReaction.AddSpeciesToProducts(myReactant3);
    myReverseReaction.AddSpeciesToReactants(myProduct1);
    myReverseReaction.AddSpeciesToReactants(myProduct2);

  };
};

TEST_F(ReactionSystemTest, ReactionSystemCanAddSpecies){
  myReactionSystem.AddSpecies(myReactant1);
  myReactionSystem.AddSpecies(myReactant2);
  ASSERT_EQ(2,myReactionSystem.GetSpecies().size());
  EXPECT_EQ(&myReactant1,myReactionSystem.GetSpecies()[0]);
  EXPECT_EQ(&myReactant2,myReactionSystem.GetSpecies()[1]);

}

TEST_F(ReactionSystemTest, ReactionSystemSpeciesCanBeModifiedByPointer){
  myReactionSystem.AddSpecies(myReactant1);
  EXPECT_EQ(1.0,myReactionSystem.GetSpecies()[0]->GetConcentration());
  myReactant1.SetConcentration(11.0);
  EXPECT_EQ(11.0,myReactionSystem.GetSpecies()[0]->GetConcentration()); 
}

TEST_F(ReactionSystemTest, ReactionSystemCanAddReaction){
  myReactionSystem.AddReaction(myReaction);
  ASSERT_EQ(1,myReactionSystem.GetReactions().size());
  EXPECT_EQ(&myReaction,myReactionSystem.GetReactions()[0]);
}


TEST_F(ReactionSystemTest, ReactionSystemCanAddMultipleReactions){
  myReactionSystem.AddReaction(myReaction);
  myReactionSystem.AddReaction(myReverseReaction);
  ASSERT_EQ(2,myReactionSystem.GetReactions().size());
  EXPECT_EQ(&myReaction,myReactionSystem.GetReactions()[0]);
  EXPECT_EQ(&myReverseReaction,myReactionSystem.GetReactions()[1]);
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
