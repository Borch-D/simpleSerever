cmake_minimum_required(VERSION 3.16)
project(simpleServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(serverLib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source/server.cpp)

add_executable(Server
        mainServer.cpp)

add_executable(Client
        mainClient.cpp)

target_link_libraries(Server serverLib)
