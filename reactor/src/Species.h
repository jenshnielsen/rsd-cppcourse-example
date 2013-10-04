#include <string> // use the string capabilities from the standard library

#ifndef ONCE_SPECIES_H
#define ONCE_SPECIES_H

namespace reactor
{

  class Species // A "class" is a user defined type with built-in functions
  {   
  public:
    Species(const std::string &input_name); // Declare constructor function.
    const std::string & GetName() const;// Declare a get name function.
    const double & GetConcentration() const {return concentration;};
    void SetConcentration(const double &input_concentration){concentration = input_concentration;};
    
    const double & GetRateOfChange() const {return rateofchange;}
    void AddToRateOfChange(const double & flux){rateofchange += flux;};
    void ResetRateOfChange(){rateofchange=0;};

  private:
    std::string name; // A member variable for the class to store the name of the system.
    double concentration;
    double rateofchange;
  };
}

#endif //ONCE_SPECIES_H
