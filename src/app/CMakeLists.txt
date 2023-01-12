cmake_minimum_required(VERSION 3.16)

add_executable(TcpProxyServer main.cpp)
target_link_libraries(TcpProxyServer PRIVATE Core)