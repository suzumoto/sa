#pragma once

#include <boost/lexical_cast.hpp>
#include <iostream>

struct options{
  unsigned int nodes;

  bool valid;

  options(unsigned int argc, char *argv[], bool print = true) :
    // default parameters
    nodes(10),
    valid(true)
  {
    for(unsigned int i = 0; i < argc; ++i){
      switch (argv[i][0]){
      case '-' :
	switch (argv[i][1]) {
	case 'n' :
	  if(++i == argc) { usage(); return;}
	  nodes = boost::lexical_cast<unsigned int>(argv[i]); break;
	default :
	  usage(); return;
	}
	break;
      default :
	usage(); return;
      }
    }
    if (print) {
      std::cout << "The number of nodes    = " << nodes << std::endl;
    }
  }

  void usage(std::ostream& os = std::cerr) {
    os << "[command line options]" << std::endl
       << "  -n # of nodes" << std::endl;
    valid = false;
  }
};
