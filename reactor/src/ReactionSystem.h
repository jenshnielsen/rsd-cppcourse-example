#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Species.h"
#include "Reaction.h"

#ifndef ONCE_REACTIONSYSTEM_H
#define ONCE_REACTIONSYSTEM_H

namespace reactor
{
  
  class ReactionSystem
  {   
  public:
    ReactionSystem(){};

    ~ReactionSystem(){};
    
    std::shared_ptr<Species> AddSpecies(const std::string &input_name);
    const std::vector<std::shared_ptr<Species> > & GetSpecies() const { return species;}

    std::shared_ptr<Reaction> AddReaction(double rate);
    const std::vector<std::shared_ptr<Reaction> > & GetReactions() const { return reactions;}

    const std::vector<double> GetRatesOfChange();

    const std::vector<double> GetConcentrations();
    
    void SetConcentrations(const std::vector<double>);

  private:
    std::vector<std::shared_ptr<Species> > species;
    std::vector<std::shared_ptr<Reaction> > reactions;
  };

}

#endif 
