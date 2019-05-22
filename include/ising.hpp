#include <iostream>
#include <vector>
#include <boost/random.hpp>

class ising
{
private:
  std::vector<bool> configuration;
  std::vector<std::vector<double>> connects;
  
public:
  // constructors
  ising(const unsigned int N, boost::mt19937& eng);
  ising(const unsigned int N, const std::vector<std::vector<double>> Q);
  ising(const std::vector<bool> spins, const std::vector<std::vector<double>> Q);
  ising(const std::vector<bool> spins, boost::mt19937& eng);
  
  // destructor
  ~ising();

  // objective/cost function
  double cost() const;
  double delta(const unsigned int site) const;

  // flip procedure
  void flip(const unsigned int site);
  
  // output for debug
  friend std::ostream& operator<<(std::ostream& os, const ising& obj);
};
