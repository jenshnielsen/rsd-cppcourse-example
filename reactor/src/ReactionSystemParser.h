#include <string> // use the string capabilities from the standard library
#include <vector>
#include <unordered_map>
#include <exception>
#include <iostream>
#include <memory>

#include "ReactionSystem.h"


#ifndef ONCE_REACTIONSYSTEMPARSER_H
#define ONCE_REACTIONSYSTEMPARSER_H

namespace reactor {

  class ReactionSystemParser
  {   
  public:
    ReactionSystemParser(){};
    std::shared_ptr<ReactionSystem> FromStream(std::istream & source);
    void ParseLine(std::string & source, 
		   std::vector<std::string>& reactant_names, 
		   std::vector<std::string> & product_names, 
		   double & rate);
    std::shared_ptr<reactor::Species> NewOrFind(std::shared_ptr<ReactionSystem> result, 
						const std::string &name);
    
  private:
    std::unordered_map<std::string, std::shared_ptr<Species> > species_map;
    void ParseSpeciesList(std::string & source, std::vector<std::string> &species_names);
  };
}

#endif //ONCE_REACTIONSYSTEMPARSER_H
