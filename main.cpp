#include <iostream>
#include "ising.hpp"

int main(){
  boost::mt19937 rng(2819);
  std::vector<bool> init(5,false);
  ising obj(init, rng);
  std::cout << obj << std::endl;
  std::cout << "COST = " << obj.cost() << ", Delta = " << obj.delta(0) << std::endl;
  obj.flip(0);
  std::cout << obj << std::endl;
  std::cout << "COST = " << obj.cost() << ", Delta = " << obj.delta(2) << std::endl;
  obj.flip(2);
  std::cout << obj << std::endl;
  std::cout << "COST = " << obj.cost() << std::endl;
  return 0;
}
