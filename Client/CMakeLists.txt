cmake_minimum_required(VERSION 3.25)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp CClient.h CClient.cpp)
target_link_libraries(Client Ws2_32.lib)