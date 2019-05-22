cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(SA CXX)

include_directories(include)

add_subdirectory(src)

set(PROGS main)
foreach(name ${PROGS})
  set(target_name ${name})
  add_executable(${target_name} ${name}.cpp)
  target_link_libraries(${target_name} mcmc)
endforeach(name)
