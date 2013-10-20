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


const std::vector<double> reactor::ReactionSystem::GetRatesOfChange(){
	std::vector<double> rateofchange;

	for (auto element : species){
		element->ResetRateOfChange();
	}

	for (auto element : reactions){
		element->ContributeToRatesOfChange();
	}

	for (auto element : species){
		rateofchange.push_back(element->GetRateOfChange());
	}

	return rateofchange;
}

const std::vector<double> reactor::ReactionSystem::GetConcentrations(){
	std::vector<double> concentrations;

	for (auto element : species){
		concentrations.push_back(element->GetConcentration());
	}	

	return concentrations;
}

void reactor::ReactionSystem::SetConcentrations(const std::vector<double> concentrations){
	std::vector<double>::const_iterator each_concentration = concentrations.begin();
	for (auto element : species){
		element->SetConcentration(*each_concentration);
		++each_concentration;
	}
}
