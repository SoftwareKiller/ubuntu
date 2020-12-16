project(main)
cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DNDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")

#SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


#find_package(Protobuf REQUIRED)
#include_directories(${Protobuf_INCLUDE_DIRS})

SET(PROTOBUF_LIBRARY ${CMAKE_SOURCE_DIR}/opt/protobuf_linux/lib/libprotobuf.a)
MESSAGE(STATUS ${PROTOBUF_LIBRARY})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/protobuf/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/protobuf/lib)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267")
else()
	find_program(CCACHE_FOUND ccache)
	if(CCACHE_FOUND)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
	endif(CCACHE_FOUND)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/protobuf_linux/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/protobuf_linux/lib)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/proto)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/main)
