#include "Reaction.h"

reactor::Reaction::Reaction(const RateConstant input_rate):
  rate(input_rate)
{

}

const double reactor::Reaction::CalculateFlux()
{
  Flux flux = rate;
  for (auto element : reactants){
  	flux *= element->GetConcentration();
  }
  return flux;
}
