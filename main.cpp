#include <iostream>
#include "mc_manager.hpp"

int main(int argc, char* argv[]){
  options p(argc, argv, true);
  mc_manager obj(p);
  
  std::pair<double,std::vector<bool>> opt_sa = obj.search();
  std::cout << "===== SA SEARCH ===== # of searched state: " << obj.count() << std::endl;
  std::cout << "cost = " << opt_sa.first << std::endl;
  std::cout << "state = ";
  for(unsigned int i = 0; i < opt_sa.second.size(); ++i){
    std::cout << opt_sa.second[i] << " ";
  }
  std::cout << std::endl;
  
  std::pair<double, std::vector<bool>> opt = obj.all_search();
  std::cout << "===== ALL SEARCH ===== # of searched state: " << (1llu << p.nodes) << std::endl;
  std::cout << "cost = " << opt.first << std::endl;
  std::cout << "state = ";
  for(unsigned int i = 0; i < opt.second.size(); ++i){
    std::cout << opt.second[i] << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
