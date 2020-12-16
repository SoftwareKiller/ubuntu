project (server)

set(SOURCE_SERVER
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
	
source_group(source FILES ${SOURCE_SERVER})

add_definitions(-DASIO_STANDALONE)

add_executable(server
	${SOURCE_SERVER}
)
