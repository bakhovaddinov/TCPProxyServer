cmake_minimum_required(VERSION 3.16)

find_package(Boost REQUIRED COMPONENTS system)

add_library(Core DatabaseServer.cpp PostgresManager.cpp)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Core PUBLIC ${Boost_LIBRARIES} pq)