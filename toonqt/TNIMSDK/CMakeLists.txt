CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
set (PACKAGE "tnimsdk")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DSQLITE_HAS_CODEC -DENCODE_DATABASE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSQLITE_HAS_CODEC -DENCODE_DATABASE")


set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./API)
INCLUDE_DIRECTORIES(./db)
INCLUDE_DIRECTORIES(./CHAT)
INCLUDE_DIRECTORIES(./common)
INCLUDE_DIRECTORIES(./db/sqlite)
INCLUDE_DIRECTORIES(./db/sqlite/src)
INCLUDE_DIRECTORIES(./GroupChat)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/TNMP/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/HTTP)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/openssl/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include/rapidjson)

#AUX_SOURCE_DIRECTORY(./API DIR_SRCS)
#AUX_SOURCE_DIRECTORY(./CHAT DIR_SRCS)
#AUX_SOURCE_DIRECTORY(./db DIR_SRCS)
#AUX_SOURCE_DIRECTORY(db/sqlite DIR_SRCS)
#AUX_SOURCE_DIRECTORY(db/sqlite/src DIR_SRCS)
#AUX_SOURCE_DIRECTORY(./GroupChat/* DIR_SRCS)


FILE(GLOB TNIMSDK_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/CHAT/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CHAT/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/sqlite/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/sqlite/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/sqlite/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/*.hpp
    )
FILE(GLOB TNIMSDK_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/CHAT/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/sqlite/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/db/sqlite/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/API/*.h
    )

ADD_LIBRARY(tnimsdk SHARED ${TNIMSDK_HEADER_FILES} ${TNIMSDK_SOURCE_FILES})

#根据不同平台的编译环境加载lib
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/lib/x64/libcurl_a.lib)
            set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/tnchttp.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TMTP.lib)

            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libcrypto.lib)
        ELSE()
            set(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/lib/x64/libcurl_a.lib)
            set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/tnchttp.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TMTP.lib)

            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libcrypto.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/lib/x86/libcurl.lib)
            set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/tnchttp.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TMTP.lib)

            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
        ELSE()
            set(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/lib/x86/libcurl.lib)
            set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/tnchttp.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TMTP.lib)

            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libssl.so)
    SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libcrypto.so)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnchttp.so)
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.so)
    ELSE()
        set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnchttp.so)
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.so)
    ENDIF()
    set(LIBUUID libuuid.so)
ENDIF ()

IF(APPLE)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/openssl/include)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnchttp.dylib)
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.dylib)
    ELSE()
        set(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnchttp.dylib)
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.dylib)
    ENDIF()
    set(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/mac/libcurl.dylib)
    set(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/mac/libcrypto.dylib)
    set(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/mac/libssl.dylib)
ENDIF()


TARGET_LINK_LIBRARIES(${PACKAGE}
    ${CURLLIB}
    ${TMTPLIB}
    ${HTTPLIB}
    ${OPENSSLLIB}
    ${CRYPTOLIB}
    ${LIBUUID}
    )

set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
