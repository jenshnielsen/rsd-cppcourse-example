#include "ReactionSystem.h"
#include <memory>

reactor::ReactionSystem::ReactionSystem()
{

}

std::shared_ptr<reactor::Species> reactor::ReactionSystem::AddSpecies(const std::string &input_name){
	std::shared_ptr<reactor::Species> newspecies = std::make_shared<reactor::Species>(input_name);
	species.push_back(newspecies);
	return newspecies;
}

void reactor::ReactionSystem::AddReaction(Reaction& newreaction){
	reactions.push_back(&newreaction);
}