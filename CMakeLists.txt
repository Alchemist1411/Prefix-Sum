cmake_minimum_required(VERSION 3.12)
project(prefix_sum)

# HPX
find_package(HPX REQUIRED)

set (program prefix_sum)
add_hpx_executable(${program} ESSENTIAL SOURCES ${program}.cpp)
