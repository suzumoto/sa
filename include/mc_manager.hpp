#pragma once

#include "ising.hpp"
#include "options.hpp"

class mc_manager
{
private:
  const unsigned int FREEZELIM;
  const unsigned int SIZEFACTOR;
  const unsigned int Nbar;
  const double CUTOFF; 
  const double TEMPFACTOR;
  const double MINPERCENT;

  unsigned int trial;
  unsigned int change;
  unsigned int freeze;

  const unsigned int seed;
  boost::mt19937 rng;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<>> random_uniform;
  boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>> random_int;
  
  ising system;
  double temperature;  

  double bound;
  std::vector<bool> argbound;

  unsigned int counter;
  
  double init_temperature(const options& p) const;
  
public:
  mc_manager(const options& p);
  ~mc_manager();

  void update();
  std::pair<double, std::vector<bool>> search();

  unsigned int count() const;
  
  std::pair<double, std::vector<bool>> all_search() const;
  
  friend std::ostream& operator<<(std::ostream& os, const mc_manager& obj);
};
