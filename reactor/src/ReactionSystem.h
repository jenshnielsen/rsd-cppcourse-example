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
    ReactionSystem();
    
    void AddSpecies(std::shared_ptr<Species> newspecies);
    const std::vector<std::shared_ptr<Species> > & GetSpecies() const { return species;} 

    void AddReaction(std::shared_ptr<Reaction> newreaction);
    const std::vector<std::shared_ptr<Reaction> > & GetReactions() const { return reactions;} 

  private:
    std::vector<std::shared_ptr<Species> > species;
    std::vector<std::shared_ptr<Reaction> > reactions;
  };

}

#endif 
