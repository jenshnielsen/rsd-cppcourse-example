#include <vector>
#include <string>

#include "Species.h" 

#ifndef ONCE_REACTION_H
#define ONCE_REACTION_H

namespace reactor
{

  class Reaction 
  {   
  public:
    Reaction(const double & input_rate);
    const double & GetReactionRate() {return rate;};
    
    const std::vector<Species> & GetReactants(){return reactants;};
    const std::vector<Species> & GetProducts(){return products;};
    
    void AddSpeciesToReactants(const Species & reactant){reactants.push_back(reactant);};
    void AddSpeciesToProducts(const Species & product){products.push_back(product);};
    
  private:
    double rate;
    std::vector<Species> reactants;
    std::vector<Species> products;
  };
}

#endif 
