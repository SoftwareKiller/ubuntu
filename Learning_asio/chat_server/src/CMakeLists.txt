project (chat)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -g")
ENDIF()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/base
	${CMAKE_CURRENT_SOURCE_DIR}/net
	${CMAKE_CURRENT_SOURCE_DIR}/utils
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11
	${CMKKE_CURRENT_SOURCE_DIR}/mysqlapi
	${CMKKE_CURRENT_SOURCE_DIR}/mysqlmgr
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
	${CMAKE_CURRENT_SOURCE_DIR}/net/ProtocolStream.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/ProtocolStream.h
)

set(chat
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_server.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_server.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/Tcp_session.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/Tcp_session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_session.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/chat_session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/http_session.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/http_session.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/HttpServer.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/HttpServer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/BussinessLogic.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/BussinessLogic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/Msg.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/UserManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/chatserver/UserManager.cpp
)

set(utils
	${CMAKE_CURRENT_SOURCE_DIR}/utils/DaemonRun.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/DaemonRun.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/StringUtil.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/StringUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/URLEncodeUtil.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/URLEncodeUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils/id_worker.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils/json.hpp
)

set(zlib_srcs
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/zutil.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/uncompr.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/trees.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/inftrees.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/inflate.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/inffast.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/infback.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/gzwrite.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/gzread.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/gzlib.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/gzclose.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/deflate.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/crc32.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/compress.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/adler32.c
	${CMAKE_CURRENT_SOURCE_DIR}/zlib1.2.11/ZlibUtil.cpp
)

set(mysqlapi
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/QueryResult.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/QueryResult.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/Field.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/Field.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/DatabaseMysql.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlapi/DatabaseMysql.cpp
)

set(mysqlmgr
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/TaskList.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/TaskList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlThrdMgr.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlThrdMgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlThrd.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlThrd.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlTask.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/mysqlmgr/MysqlManager.cpp
)
	
source_group(base FILES ${base})
source_group(net FILES ${net})
source_group(chat FILES ${chat})
source_group(utils FILES ${utils})
source_group(zlib1.2.11 FILES ${zlib_srcs})
source_group(mysqlapi FILES ${mysqlapi})
source_group(mysqlmgr FILES ${mysqlmgr})

add_definitions(-DASIO_STANDALONE)

add_executable(chat_server
	${base}
	${net}
	${utils}
	${chat}
	${zlib_srcs}
	${mysqlapi}
	${mysqlmgr}
)

#message(debug_flag:${debug})
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(chat_server mysqlclient)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(chat_server libmysql)
ENDIF()
