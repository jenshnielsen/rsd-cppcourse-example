#include <memory>

#include "ReactionSystem.h"
#include "Species.h"
#include "Reaction.h"

#include <gtest/gtest.h>

using namespace reactor;

class ReactionSystemTest: public ::testing::Test {
protected:
  //ReactionSystem myReactionSystem;
  Species myReactant1;
  //std::shared_ptr<Species> myReactant1("myReactant1");
  //std::shared_ptr<Species> myReactant2("myReactant2");
  //std::shared_ptr<Species> myReactant3("myReactant3");
  //std::shared_ptr<Species> myProduct1("myProduct1");
  //std::shared_ptr<Species> myProduct2("myProduct2");
  ReactionSystemTest():
    //myReactionSystem()
    myReactant1("myReactant1")
    //myReactant2("myReactant2"),
    //myReactant3("myReactant3"),
    //myProduct1("myProduct1"),
    //myProduct2("myProduct2")
  { 
    //auto myReactant1 = std::make_shared<Species>("myReactant1");
    myReactant1.SetConcentration(1.0);
    //myReactant2->SetConcentration(2.0);
    //myReactant3->SetConcentration(3.0);
    //myProduct1->SetConcentration(5.0);
    //myProduct2->SetConcentration(6.0);
  };
};

TEST_F(ReactionSystemTest, ReactionSystemInit){

}


int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
