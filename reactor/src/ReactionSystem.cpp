#include "ReactionSystem.h"

reactor::ReactionSystem::ReactionSystem()
{

}

void reactor::ReactionSystem::AddSpecies(Species& newspecies){
	species.push_back(&newspecies);
}

void reactor::ReactionSystem::AddReaction(Reaction& newreaction){
	reactions.push_back(&newreaction);
}