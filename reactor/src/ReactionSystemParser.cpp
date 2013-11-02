#include "ReactionSystemParser.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

std::shared_ptr<reactor::ReactionSystem> reactor::ReactionSystemParser::FromStream(std::istream & source)
{
  std::shared_ptr<ReactionSystem> result= std::make_shared<ReactionSystem>();

  	while (source.good())
  	{
  		std::string line;
  		std::getline(source,line);
 		std::vector<std::string> reactant_names;
 		std::vector<std::string> product_names;
 		double rate(0.0);
 		ParseLine(line, reactant_names, product_names, rate);
 		if (rate!=0.0)
 		{
		  auto reaction = result->AddReaction(rate);
		  for (auto reactant : reactant_names){
		    reaction->AddSpeciesToReactants(NewOrFind(result, reactant));
		  }
		  for (auto product : product_names){
		    reaction->AddSpeciesToProducts(NewOrFind(result, product));
		  }
		}
 	}
  	return result;
}

std::shared_ptr<reactor::Species> reactor::ReactionSystemParser::NewOrFind(
	std::shared_ptr<ReactionSystem> result,
	const std::string &name)
{
  if (species_map.find(name) == species_map.end()){
    auto newspecies = result->AddSpecies(name);
    species_map[name] = newspecies;
    
  }
  return species_map[name];
}

void reactor::ReactionSystemParser::ParseLine(std::string & line, 
	std::vector<std::string>& reactant_names, 
	std::vector<std::string> & product_names, 
	double & rate)
{
  std::vector<std::string> sections;
  boost::split(sections,line,boost::is_any_of(">"));
  if (sections.size()!=3)
    {
      return;
    }
  ParseSpeciesList(sections[0], reactant_names);
  ParseSpeciesList(sections[2], product_names);
  boost::trim(sections[1]);
  rate=boost::lexical_cast<double>(sections[1]);
}

void reactor::ReactionSystemParser::ParseSpeciesList(std::string & source,
    std::vector<std::string> &species_names)
{
  boost::split(species_names,source,boost::is_any_of("+"));
  //for (auto i : species_names){
  for( std::vector<std::string>::iterator species=species_names.begin(); 
       species!=species_names.end(); species++){
    boost::trim(*species);
  }
}
