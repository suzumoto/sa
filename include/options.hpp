#pragma once

#include <boost/lexical_cast.hpp>
#include <iostream>

struct options{
  unsigned int nodes;
  
  unsigned int FREEZELIM;
  unsigned int SIZEFACTOR;
  unsigned int Nbar;
  double CUTOFF;
  double TEMPFACTOR;
  double MINPERCENT;
  double INITPROB;

  unsigned int seed;
  
  bool valid;

  options(int argc, char *argv[], bool print = true) :
    // default parameters
    nodes(10),
    FREEZELIM(5),
    SIZEFACTOR(16),
    Nbar(nodes),
    CUTOFF(0.1),
    TEMPFACTOR(0.95),
    MINPERCENT(0.02),
    INITPROB(0.8),
    seed(65672),
    valid(true)
  {
    for(unsigned int i = 1; i < argc; ++i){
      switch (argv[i][0]){
      case '-' :
	switch (argv[i][1]) {
	case 'n' :
	  if(++i == argc) { usage(); return;}
	  nodes = boost::lexical_cast<unsigned int>(argv[i]); break;
	case 'f' :
	  if(++i == argc) { usage(); return;}
	  FREEZELIM = boost::lexical_cast<unsigned int>(argv[i]); break;
	case 's' :
	  if(++i == argc) { usage(); return;}
	  SIZEFACTOR = boost::lexical_cast<unsigned int>(argv[i]); break;
	case 'b' :
	  if(++i == argc) { usage(); return;}
	  Nbar = boost::lexical_cast<unsigned int>(argv[i]); break;
	case 'c' :
	  if(++i == argc) { usage(); return;}
	  CUTOFF = boost::lexical_cast<double>(argv[i]); break;
	case 't' :
	  if(++i == argc) { usage(); return;}
	  TEMPFACTOR = boost::lexical_cast<double>(argv[i]); break;
	case 'm' :
	  if(++i == argc) { usage(); return;}
	  MINPERCENT = boost::lexical_cast<double>(argv[i]); break;
	case 'i' :
	  if(++i == argc) { usage(); return;}
	  INITPROB = boost::lexical_cast<double>(argv[i]); break;
	case 'r' :
	  if(++i == argc) { usage(); return;}
	  seed = boost::lexical_cast<unsigned int>(argv[i]); break;
	default :
	  usage(); return;
	}
	break;
      default :
	usage(); return;
      }
    }
    if (print) {
      std::cout << "  The number of nodes  = " << nodes << std::endl
		<< "  FREEZE LIMIT         = " << FREEZELIM << std::endl
		<< "  SIZE FACTOR          = " << SIZEFACTOR << std::endl
		<< "  CUTOFF               = " << CUTOFF << std::endl
		<< "  Size of neighborhood = " << Nbar << std::endl
		<< "  TEMPERATURE FACTOR   = " << TEMPFACTOR << std::endl
		<< "  MINIMUM PERCENT      = " << MINPERCENT << std::endl
		<< "  Initial acceptance   = " << INITPROB << std::endl
		<< "  Seed of RNG          = " << seed << std::endl;
    }
  }

  void usage(std::ostream& os = std::cerr) {
    os << "[command line options]" << std::endl
       << "  -n  unsigned int ----  # of nodes" << std::endl
       << "  -f  unsigned int ----  FREEZE LIMIT" << std::endl
       << "  -s  unsigned int ----  SIZE FACTOR" << std::endl
       << "  -b  unsigned int ----  Mean size of neighborhood" << std::endl
       << "  -c  double       ----  CUTOFF" << std::endl
       << "  -t  double       ----  TEMPERATURE FACTOR" << std::endl
       << "  -m  double       ----  MINIMUM PERCENT" << std::endl
       << "  -i  double       ----  Inital acceptance probability" << std::endl
       << "  -r  unsigned int ----  Seed of RNG"     << std::endl;
    valid = false;
  }
};
