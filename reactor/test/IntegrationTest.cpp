#include <gtest/gtest.h>
#include <cmath>

#include <boost/numeric/odeint.hpp> 

#include "ReactionSystem.h"


using namespace reactor;

class WrapReactionSystemForODEINT
{
public:
    ReactionSystem &system;
    WrapReactionSystemForODEINT(ReactionSystem & system):
        system(system)
    {
    }
    void operator() ( const std::vector<double> &x , 
                      std::vector<double> &dxdt,
                      const double time)
    {
        system.GetRatesOfChangeGivenConcentrations(x,dxdt);
    }
};

void observe_integration(const std::vector<double> &concentrations , const double time){
  std::cout << time << ": [" << std::flush;
  for (unsigned int i=0; i<concentrations.size();i++){
    std::cout << concentrations[i] <<  ", " << std::flush;
  }
  std::cout << "]" << std::endl;
} 

class IntegrationTest: public ::testing::Test {
protected:
  ReactionSystem simple_decay_system;
  
  IntegrationTest():
  simple_decay_system()
  {
    auto decay = simple_decay_system.AddReaction(2.0);
    auto original = simple_decay_system.AddSpecies("Original");
    auto product = simple_decay_system.AddSpecies("Product");
    decay->AddSpeciesToReactants(original.get());
    decay->AddSpeciesToProducts(product.get());
    original->SetConcentration(100.0);
    product->SetConcentration(0.0); 
  };
};

TEST_F(IntegrationTest, SimpleDecay) {
  std::vector<double> concentrations=simple_decay_system.GetConcentrations();
  WrapReactionSystemForODEINT wrapper(simple_decay_system);
  int step_count=boost::numeric::odeint::integrate(wrapper, concentrations , 0.0, 1.5, 0.1, observe_integration);
  // the concentration of the reactant should be
  // initial* exp(-time*rate)
  // and of the product
  // initial* (1-exp(-time*rate))

  EXPECT_NE(step_count,0);
  EXPECT_NEAR(100*std::exp(-2.0*1.5),concentrations[0],0.001);
  EXPECT_NEAR(100-100*std::exp(-2.0*1.5),concentrations[1],0.001); 
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
