#include "ising.hpp"
#include <cassert>

// constructors
ising::ising(const unsigned int N, boost::mt19937& eng):
  configuration(std::vector<bool>(N,false)),
  connects(std::vector<std::vector<double>>(0))
{
  boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>> random_bit(eng,boost::uniform_smallint<>(0,1));
  boost::variate_generator<boost::mt19937&, boost::uniform_real<>> random_uniform(eng,boost::uniform_real<>(-1.0,1.0));

  // connects construction
  for(unsigned int i = 0; i < N ; ++i){
    std::vector<double> one_another(0);
    for(unsigned int j = 0; j <= i; ++j){
      one_another.push_back(random_uniform());
    }
    connects.push_back(one_another);

    // configuration construction
    configuration[i] = random_bit()?true:false;
  }
}

ising::ising(const unsigned int N, const std::vector<std::vector<double>> Q):
  configuration(std::vector<bool>(N,false)),
  connects(Q)
{
  assert(Q.size() == N);
  for(unsigned int i = 0; i < N; ++i){
    assert(Q[i].size() > i);
  }
}

ising::ising(const std::vector<bool> spins, const std::vector<std::vector<double>> Q):
  configuration(spins),
  connects(Q)
{
  assert(spins.size() == Q.size());
  for(unsigned int i = 0; i < spins.size(); ++i){
    assert(Q[i].size() > i);
  }
}

ising::ising(const std::vector<bool> spins, boost::mt19937& eng):
  configuration(spins),
  connects(std::vector<std::vector<double>>(0))
{
  boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>> random_bit(eng,boost::uniform_smallint<>(0,1));
  boost::variate_generator<boost::mt19937&, boost::uniform_real<>> random_uniform(eng,boost::uniform_real<>(-1.0,1.0));
  
  // connects construction
  for(unsigned int i = 0; i < spins.size() ; ++i){
    std::vector<double> one_another(0);
    for(unsigned int j = 0; j <= i; ++j){
      one_another.push_back(random_uniform());
    }
    connects.push_back(one_another);
  }
}

double ising::cost(const std::vector<bool>& state) const{
  assert(state.size() == configuration.size());
  double value = 0.0;
  for(unsigned int i = 0; i < state.size(); ++i){
    for(unsigned int j = 0; j <= i; ++j){
      if(state[i] && state[j]) value += connects[i][j];
    }
  }
  return value;
}

void ising::incliment(std::vector<bool>& state) const{
  for(unsigned int i = 0; i < state.size(); ++i){
    if(state[i]) state[i] = false;
    else {
      state[i] = true;
      break;
    }
  }
}

// destructor
ising::~ising(){}

// extract inner state/configuration
std::vector<bool> ising::state() const{
  return configuration;
}

// objective/cost function
double ising::cost() const{
  double value = 0.0;
  for(unsigned int i = 0; i < configuration.size(); ++i){
    for(unsigned int j = 0; j <= i; ++j){
      if(configuration[i] && configuration[j]) value += connects[i][j];
    }
  }
  return value;
}

double ising::delta(const unsigned int site) const{
  assert(site <= configuration.size());
  
  double value = 0.0;
  for(unsigned int i = 0; i < configuration.size(); ++i){
    if(configuration[i] || i == site){
      value += (site>i ? connects[site][i] : connects[i][site]);
    }
  }
  return configuration[site] ? -value : value;
}

// flip procedure
void ising::flip(const unsigned int site){
  assert(site <= configuration.size());
  
  configuration[site] = !configuration[site];
}

std::pair<double, std::vector<bool>> ising::all_search() const{
  std::vector<bool> state(configuration.size(),false);
  std::vector<bool> argopt(configuration.size(),false);
  double opt_value = cost(state);
  for(unsigned long long int i = 1; i < (1llu << state.size()); ++i){
    incliment(state);
    double current_cost = cost(state);
    if(current_cost < opt_value){
      opt_value = current_cost;
      argopt = state;
    }
  }
  return std::pair<double, std::vector<bool>>(opt_value, argopt);
}

// output for debug
std::ostream& operator<<(std::ostream& os, const ising& obj){
  os << "====== configuration ======" << std::endl;
  for(unsigned int i = 0; i < obj.configuration.size(); ++i){
    os << (obj.configuration[i] ? "1 " : "0 ");
  }
  os << std::endl << std::endl;
  return os;
}

void ising::show_interaction(std::ostream& os = std::cout) const{
  os << "====== interaction ======" << std::endl;
  for(unsigned int i = 0; i < connects.size(); ++i){
    for(unsigned int j = 0; j < connects[i].size(); ++j){
      os << connects[i][j] << " ";
    }
    os << std::endl;
  }
}
