# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(project4 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_path(
  MAPREDUCE_INCLUDE_DIR
  NAMES "mapreduce.h" "mr_task_factory.h"
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
)

