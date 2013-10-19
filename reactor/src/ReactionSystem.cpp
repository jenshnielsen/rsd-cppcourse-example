#include "ReactionSystem.h"

reactor::ReactionSystem::ReactionSystem()
{

}

void reactor::ReactionSystem::AddSpecies(std::shared_ptr<Species> newspecies){
	species.push_back(newspecies);
}

void reactor::ReactionSystem::AddReaction(std::shared_ptr<Reaction> newreaction){
	reactions.push_back(newreaction);
}