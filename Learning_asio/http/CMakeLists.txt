project(chatserver)
cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

add_definitions(-DNDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")

MESSAGE(STATUS "current platform: ${CMAKE_SYSTEM_NAME}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/asio-1.18.0/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/)
