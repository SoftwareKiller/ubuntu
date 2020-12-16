PROJECT(SERVER)

SET(SRC_LISTS main.cpp
    Acceptor.cpp
    event.cpp
    IAddress.cpp
    Socket.cpp)

MESSAGE(STATUS "This is BINARY dir" ${SERVER_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir" ${SERVER_SOURCE_DIR})

ADD_EXECUTABLE(main ${SRC_LISTS})

