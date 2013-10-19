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
    
    std::shared_ptr<Species> AddSpecies(const std::string &input_name);
    const std::vector<std::shared_ptr<Species> > & GetSpecies() const { return species;}

    void AddReaction(Reaction & newreaction);
    const std::vector<Reaction* > & GetReactions() const { return reactions;}

  private:
    std::vector<std::shared_ptr<Species> > species;
    std::vector<Reaction* > reactions;
  };

}

#endif 
