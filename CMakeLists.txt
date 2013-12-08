cmake_minimum_required(VERSION 2.6.0)
SET(CMAKE_C_COMPILER "/usr/local/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
SET(CMAKE_PREFIX_PATH "/usr/local")

project(jhprimeminer)

find_package(OpenSSL REQUIRED)

set(jhprimeminer_SOURCES
	src/primecoinMiner/bn2.cpp
	src/primecoinMiner/bn2_div.cpp
	src/primecoinMiner/jhlib/customBuffer.cpp
	src/primecoinMiner/jhlib/streamWrapper.cpp
	src/primecoinMiner/jhlib/fastString.cpp
	src/primecoinMiner/jhlib/fastString_eprintf.cpp
	src/primecoinMiner/jhlib/hashTable_uint32.cpp
	src/primecoinMiner/jhlib/packetBuffer.cpp
	src/primecoinMiner/jhlib/simpleHTTP.cpp
	src/primecoinMiner/jhlib/simpleList.cpp
	src/primecoinMiner/jsonBuilder.cpp
	src/primecoinMiner/jsonClient.cpp
	src/primecoinMiner/jsonObject.cpp
	src/primecoinMiner/jsonParser.cpp
	src/primecoinMiner/jsonrpc.cpp
	src/primecoinMiner/main.cpp
	src/primecoinMiner/miner.cpp
	src/primecoinMiner/prime.cpp
	src/primecoinMiner/transaction.cpp
	src/primecoinMiner/ripemd160.cpp
	src/primecoinMiner/sha256.cpp
	src/primecoinMiner/xptClient.cpp
	src/primecoinMiner/xptClientPacketHandler.cpp
	src/primecoinMiner/xptPacketbuffer.cpp
	src/primecoinMiner/xptServer.cpp
	src/primecoinMiner/xptServerPacketHandler.cpp
	src/primecoinMiner/bignum2.h
	src/primecoinMiner/global.h
	src/primecoinMiner/jhlib/JHLib.h
	src/primecoinMiner/jhlib/customBuffer.h
	src/primecoinMiner/jhlib/fastSorter.h
	src/primecoinMiner/jhlib/fastString.h
	src/primecoinMiner/jhlib/hashTable.h
	src/primecoinMiner/jhlib/packetBuffer.h
	src/primecoinMiner/jhlib/simpleHTTP.h
	src/primecoinMiner/jhlib/simpleList.h
	src/primecoinMiner/jsonrpc.h
	src/primecoinMiner/prime.h
	src/primecoinMiner/ripemd160.h
	src/primecoinMiner/sha256.h
	src/primecoinMiner/uint256.h
	src/primecoinMiner/xptClient.h
	src/primecoinMiner/xptServer.h
)

if(UNIX)
	SET(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -march=native -mtune=native -fomit-frame-pointer")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=gnu++0x")

else()
	include_directories(${jhprimeminer_SOURCE_DIR}/include)
endif()


add_executable(jhprimeminer ${jhprimeminer_SOURCES})

if(UNIX)
        target_link_libraries(jhprimeminer pthread mpir pthread rt)
endif()

target_link_libraries(jhprimeminer ${OPENSSL_LIBRARIES})
