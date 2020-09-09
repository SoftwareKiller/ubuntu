project(main)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -g")
ENDIF()
	
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../proto/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../opt
	)
	
set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
	
source_group(source FILES ${SOURCE_FILES})

add_executable(main
	${SOURCE_FILES} 
	)
	
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(main proto protobuf)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(main proto libprotobufd)
ENDIF()
