#include "ReactionSystem.h"
#include <memory>

std::shared_ptr<reactor::Species> reactor::ReactionSystem::AddSpecies(const std::string &input_name){
	std::shared_ptr<reactor::Species> newspecies = std::make_shared<reactor::Species>(input_name);
	species.push_back(newspecies);
	return newspecies;
}

std::shared_ptr<reactor::Reaction> reactor::ReactionSystem::AddReaction(const double rate){
	std::shared_ptr<reactor::Reaction> newreaction = std::make_shared<reactor::Reaction>(rate);
	reactions.push_back(newreaction);
	return newreaction;
}