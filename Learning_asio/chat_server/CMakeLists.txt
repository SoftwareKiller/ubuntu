project(chatservice)
cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DNDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/mysql/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/mysql/lib)
	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267")
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/mysql/include_linux)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/mysql/lib)
endif()

MESSAGE(STATUS "current platform: ${CMAKE_SYSTEM_NAME}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/asio-1.18.0/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/)
