cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(ktot)

include_directories(../include)
add_subdirectory(../ktot_domain ../build/ktot_domain)
add_subdirectory(../ktot_repo_json ../build/ktot_repo_json)

add_executable(
  ktot
  ktot_app_t.cpp
  )

target_link_libraries(
  ktot
  ktot_domain
  ktot_repo_json
  )

