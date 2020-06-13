CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
set (PACKAGE "tnchttp")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/openssl/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include/curl)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/TNMP/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include/rapidjson)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

ADD_LIBRARY(${PACKAGE} SHARED ${DIR_SRCS})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TMTPd.lib)
        else()
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TMTP.lib)
        endif()
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TMTPd.lib)
            SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/libcurld.lib)
        else()
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TMTP.lib)
            SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/libcurl.lib)
        endif()
    endif()
endif()
if(APPLE)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.dylib)
    else()
        set(TMTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.dylib)
    endif()
    SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/mac/libcurl.dylib)
endif()

message(STATUS "libcurl:" ${LIBCURL})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libssl.so)
    SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libcrypto.so)
    SET(CURLLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/linux/libcurl.so)
    target_link_libraries(${PACKAGE}
        ${OPENSSLLIB}
        ${CRYPTOLIB}
        ${CURLLIB}
        )
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DUNICODE)
    target_link_libraries(${PACKAGE}
        ${OPENSSLLIB}
        ${CRYPTOLIB}
        ${TMTPLIB}
        ${LIBCURL}
        )
endif()

if(APPLE)
    target_link_libraries(${PACKAGE}
        ${LIBCURL}
        ${TMTPLIB}
        )
endif()

set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
