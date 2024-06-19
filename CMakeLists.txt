
cmake_minimum_required(VERSION 3.22)

project(utils LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall")

add_subdirectory(libs/nlohmann_json/)

add_library(utils SHARED src/utils.cpp)
target_include_directories(utils PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include/>
)
target_link_libraries(utils PUBLIC nlohmann_json::nlohmann_json)

set_target_properties(utils PROPERTIES PUBLIC_HEADER include/utils.hpp)

include(GNUInstallDirs)

install(TARGETS utils 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

