project (chat)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -g")
ENDIF()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/base
	${CMAKE_CURRENT_SOURCE_DIR}/net
	${CMAKE_CURRENT_SOURCE_DIR}/utils
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver
)

set(base
	${CMAKE_CURRENT_SOURCE_DIR}/base/AsyncLogging.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/base/AsyncLogging.h
	${CMAKE_CURRENT_SOURCE_DIR}/base/ConfigFileReader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/base/ConfigFileReader.h
	${CMAKE_CURRENT_SOURCE_DIR}/base/CountDownLatch.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/base/CountDownLatch.h
	${CMAKE_CURRENT_SOURCE_DIR}/base/Timestamp.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/base/Singleton.h
	${CMAKE_CURRENT_SOURCE_DIR}/base/Timestamp.h
)

set(net
	${CMAKE_CURRENT_SOURCE_DIR}/net/EventLoop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/EventLoop.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/io_service_pool.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/io_service_pool.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Timer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/Timer.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/TimerQueue.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/TimerQueue.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/TimerId.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Callbacks.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Channel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/Channel.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Tcp_connection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/Tcp_connection.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Tcp_server.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/Tcp_server.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/session_mgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/session_mgr.h
	${CMAKE_CURRENT_SOURCE_DIR}/net/Buffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/Buffer.h
)

set(chat
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_session.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/http_session.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/http_session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/HttpServer.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/HttpServer.cpp
)

set(utils
	${CMAKE_CURRENT_SOURCE_DIR}/utils/DaemonRun.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/DaemonRun.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/StringUtil.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/StringUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/URLEncodeUtil.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/URLEncodeUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/id_worker.h
)

set(SOURCE_SERVER
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
	
source_group(base FILES ${base})
source_group(net FILES ${net})
source_group(chat FILES ${chat})
source_group(utils FILES ${utils})
source_group(source FILES ${SOURCE_SERVER})

add_definitions(-DASIO_STANDALONE)

add_executable(chat_server
	${base}
	${net}
	${utils}
	${chat}
	${SOURCE_SERVER}
)
