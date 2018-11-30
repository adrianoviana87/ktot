cmake_minimum_required(VERSION 3.0)

project(ktot_repo_json)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(PUBLIC ../include PRIVATE ${CMAKE_SOURCE_DIR})

add_library(
  ktot_repo_json
  task_json_repository_t.cpp
  serialization.cpp
  )

target_link_libraries(
  ktot_repo_json
  ktot_domain
  )

