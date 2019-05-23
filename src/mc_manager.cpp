#include "mc_manager.hpp"
#include <cmath>

double mc_manager::init_temperature(const options& p) const{
  double mean_positive_delta = 0.0;
  unsigned int entry = 0;
  for(unsigned int i = 0; i < p.nodes; ++i){
    double local_delta = system.delta(i);
    if(local_delta > 0){
      mean_positive_delta += local_delta;
      ++entry;
    }
  }
  mean_positive_delta /= entry;
  return - mean_positive_delta / log(p.INITPROB);
}

mc_manager::mc_manager(const options& p):
  FREEZELIM(p.FREEZELIM),
  SIZEFACTOR(p.SIZEFACTOR),
  Nbar(p.Nbar),
  CUTOFF(p.CUTOFF),
  TEMPFACTOR(p.TEMPFACTOR),
  MINPERCENT(p.MINPERCENT),

  trial(0),
  change(0),
  freeze(0),

  seed(p.seed),
  rng(boost::mt19937(p.seed)),
  random_uniform(boost::variate_generator<boost::mt19937&, boost::uniform_real<>>(rng, boost::uniform_real<>())),
  random_int(boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>>(rng, boost::uniform_smallint<>(0,p.nodes - 1))),

  system(ising(p.nodes, rng)),
  temperature(init_temperature(p)),

  bound(system.cost()),
  argbound(system.state()),

  counter(0)
{
}

mc_manager::~mc_manager(){
}

void mc_manager::update(){
  ++trial;
  ++counter;
  const unsigned int site = random_int();
  const double current_delta = system.delta(site);
  if(current_delta < 0){ // Accept
    ++change;
    system.flip(site);
    const double current_cost = system.cost();
    if(current_cost < bound){
      bound = current_cost;
      argbound = system.state();
      freeze = 0;
    }
  }
  else {
    const double rand01 = random_uniform();
    if(rand01 < exp(-current_delta/temperature)){ // Accept
      ++change;
      system.flip(site);
    }
  }
}
	     									 
std::pair<double, std::vector<bool>> mc_manager::search(){
  while(freeze < FREEZELIM){
    change = 0;
    trial = 0;
    while(trial < SIZEFACTOR * Nbar && change < CUTOFF * Nbar){
      update();
    }
    temperature *= TEMPFACTOR;
    if(change < MINPERCENT * trial) ++freeze;
  }
  return std::pair<double, std::vector<bool>>(bound, argbound);
}

unsigned int mc_manager::count() const{
  return counter;
}

std::pair<double, std::vector<bool>> mc_manager::all_search() const{
  return system.all_search();
}

std::ostream& operator<<(std::ostream& os, const mc_manager& obj){
  os << "Temperature = " << obj.temperature << std::endl;
  os << obj.system;
}
