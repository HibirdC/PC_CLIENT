#set(CMAKE_SYSTEM_NAME Android)
#set(CMAKE_SYSTEM_VERSION 21) # API level
#set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
#set(CMAKE_ANDROID_NDK /Users/lanhy/Library/Android/sdk/ndk-bundle/)
#set(CMAKE_ANDROID_STL_TYPE gnustl_static)

cmake_minimum_required(VERSION 2.8.11)
#project(TMTP)
set(PACKAGE "TMTP")



if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
endif()

if(ANDROID)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID")
 	message("-- CMAKE_CXX_FLAGS -DANDROID")
endif()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/openssl/include/)
#INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/../dest/include)

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    AUX_SOURCE_DIRECTORY(./src/win32 DIR_SRCS)
    ADD_LIBRARY(${PACKAGE} STATIC ${DIR_SRCS})
else()
    AUX_SOURCE_DIRECTORY(./src/unix DIR_SRCS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ADD_LIBRARY(${PACKAGE} SHARED ${DIR_SRCS})
endif()

#修改这里是为了不让跟系统openssl冲突因为系统的openssl版本可能跟我们用的openssl版本不一至
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PACKAGE}
        ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libssl.so
        ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libcrypto.so
        )
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        target_link_libraries(${PACKAGE}
            ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libssl.lib
            ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libcrypto.lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        target_link_libraries(${PACKAGE}
            ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib
            ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
    endif()
endif()

if(APPLE)
    target_link_libraries(${PACKAGE}
        ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/mac/libcrypto.dylib
        ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/mac/libssl.dylib
        )
endif()

set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})

#install(DIRECTORY ${PROJECT_BINARY_DIR}/../../3rd/rapidjson/ DESTINATION include/rapidjson)

#install(DIRECTORY include/ DESTINATION include)
#install(FILES include/CLog.h DESTINATION api)
#install(FILES include/CSafeQueue.h DESTINATION api)
#install(FILES include/CThreadEx.h DESTINATION api)
#install(TARGETS TMTP DESTINATION lib)

