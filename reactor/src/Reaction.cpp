#include "Reaction.h"

reactor::Reaction::Reaction(const RateConstant input_rate):
  rate(input_rate), reactants(), products()
{

}

const double reactor::Reaction::GetFlux() const
{
  Flux flux = rate;
  for (auto element : reactants){
  	flux *= element->GetConcentration();
  }
  return flux;
}

void reactor::Reaction::ContributeToRatesOfChange() const
{
	double flux=GetFlux();
	for (auto element : reactants){
  		element->AddToRateOfChange(-1.0*flux);
  	}

	for (auto element : products){
  		element->AddToRateOfChange(1.0*flux);
  	}

}

std::ostream& reactor::operator<<(std::ostream &stream, const reactor::Reaction& reaction)
{
	auto reactants = reaction.GetReactants();
	for ( auto each_species = reactants.begin(); each_species != --reactants.end(); ++each_species)
  	{
		stream << (*each_species)->GetName() << " + ";
	}

	stream << (*--reactants.end())->GetName() << " > " << reaction.GetReactionRate() << " > ";


	auto products = reaction.GetProducts();
	for ( auto each_species = products.begin(); each_species != --products.end(); ++each_species)
  	{
		stream << (*each_species)->GetName() << " + ";
	}
	stream << (*--products.end())->GetName();

	return stream ; 
}
