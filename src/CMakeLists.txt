cmake_minimum_required(VERSION 3.16)

add_subdirectory(core)
add_subdirectory(app)

target_link_libraries(TcpProxyServer PRIVATE Core)