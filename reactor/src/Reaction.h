#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Species.h" 

#ifndef ONCE_REACTION_H
#define ONCE_REACTION_H

namespace reactor
{
  typedef double RateConstant;
  typedef double Flux;

  class Reaction 
  {   
  public:
    Reaction(const RateConstant input_rate);
    const RateConstant & GetReactionRate() const {return rate;};
    
    const std::vector<std::shared_ptr<Species> > GetReactants() const {return reactants;};
    const std::vector<std::shared_ptr<Species> > GetProducts() const {return products;};
    
    void AddSpeciesToReactants(std::shared_ptr<Species> reactant){reactants.push_back(reactant);};
    void AddSpeciesToProducts(std::shared_ptr<Species> product){products.push_back(product);};

    void AddSpeciesToReactants(Species &reactant){
      std::shared_ptr<Species> reactant_ptr = std::make_shared<Species>(reactant);
      reactants.push_back(reactant_ptr);
    };
    void AddSpeciesToProducts(Species &product){
      std::shared_ptr<Species> product_ptr = std::make_shared<Species>(product);
      products.push_back(product_ptr);
    };

    void ContributeToRatesOfChange() const ;

    const Flux GetFlux () const;
    

  private:
    RateConstant rate;
    std::vector<std::shared_ptr<Species> > reactants;
    std::vector<std::shared_ptr<Species> > products;
  };

  std::ostream& operator<<(std::ostream &s, const reactor::Reaction& reaction);
}

#endif 
