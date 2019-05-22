#pragma once

#include "ising.hpp"
#include "options.hpp"

class mc_manager
{
private:
  ising system;
  double temperature;

  const unsigned int FREEZELIM;
  const double TEMPFACTOR;
  const unsigned int SIZEFACTOR;
  const double MINPERCENT;
  const unsigned int CUTOFF;
  const unsigned int Nbar;

  unsigned int trial;
  unsigned int change;
  unsigned int freeze;

  double bound;
  std::vector<bool> argbound;

  boost::mt19937 rng;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<>> random_uniform;
  
public:
  mc_manager(options p);
  ~mc_manager();

  void update();
  void search();
  
};
