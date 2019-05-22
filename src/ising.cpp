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

// destructor
ising::~ising(){}

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

// output for debug
std::ostream& operator<<(std::ostream& os, const ising& obj){
  os << "====== configuration ======" << std::endl;
  for(unsigned int i = 0; i < obj.configuration.size(); ++i){
    os << (obj.configuration[i] ? "1 " : "0 ");
  }
  os << std::endl << std::endl;
  os << "====== interaction ======" << std::endl;
  for(unsigned int i = 0; i < obj.connects.size(); ++i){
    for(unsigned int j = 0; j < obj.connects[i].size(); ++j){
      os << obj.connects[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}
