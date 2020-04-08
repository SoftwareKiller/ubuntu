PROJECT(AsyncLog)
   
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

SET(SRC_LIST 
main.cpp
src/AsyncLog.h
src/AsyncLog.cpp
)

ADD_EXECUTABLE(main ${SRC_LIST})
TARGET_LINK_LIBRARIES(main)
