cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "IMCore")
set(CMAKE_AUTOMOC ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DIMCORE_LIB -DUNICODE -DCURL_STATICLIB)
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/IMCore.rc
      @ONLY)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DIMCORE_LIB) 
ELSE()
    add_definitions(-DIMCORE_LIB) 
ENDIF()

#根据不同平台的编译环境加载lib
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
    #set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/NetWorkApid.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libcrypto.lib)
            SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TMTPd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x64/libcrypto.lib)
            #SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/TNMP/lib/x64/TMTP.lib)
            SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TMTP.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TMTPd.lib)
            SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/libcurld.lib)
            SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/TNHttpd.lib)
            SET(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/tnimsdkd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TMTP.lib)
            SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/libcurl.lib)
            SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/TNHttp.lib)
            SET(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/tnimsdk.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.so)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnchttp.so)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnimsdk.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.so)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnchttp.so)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnimsdk.so)
    ENDIF()
ENDIF ()
IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)

        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.dylib)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnchttp.dylib)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnimsdk.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)

        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.dylib)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnchttp.dylib)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnimsdk.dylib)
    ENDIF()
    SET(LIBCURL ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/mac/libcurl.dylib)
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include/util)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include/jce)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include/curl)



FILE(GLOB IMCORE_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB IMCORE_FORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
FILE(GLOB IMCORE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB IMCORE_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${IMCORE_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${IMCORE_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${IMCORE_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${IMCORE_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)

QT5_WRAP_UI(FORMS_UIC ${IMCORE_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${IMCORE_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${IMCORE_MOC_FILES})

#MESSAGE(STATUS "HEADERS_MOC:" ${HEADERS_MOC})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED
    ${IMCORE_RESOURCE_FILES}
    ${IMCORE_HEADER_FILES}
    ${IMCORE_SOURCE_FILES}
    ${IMCORE_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    #${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/IMCore.rc
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED
    ${IMCORE_RESOURCE_FILES}
    ${IMCORE_HEADER_FILES}
    ${IMCORE_SOURCE_FILES}
    ${IMCORE_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    #${HEADERS_MOC}
    )
ENDIF()


MESSAGE(STATUS "openssl lib:" ${OPENSSLLIB})
#生成目录
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    TARGET_LINK_LIBRARIES(${PACKAGE} 
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        Ws2_32.lib
        Crypt32.lib
        wldap32.lib
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${OPENSSLLIB}
        ${CRYPTOLIB}
        ${TNMPLIB}
        ${LIBCURL}
        ${HTTPLIB}
        ${TNIMSDKLIB}
        )
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${TNMPLIB}
        ${HTTPLIB}
        ${TNIMSDKLIB}
        )
endif()
IF(APPLE)
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${OPENSSLLIB}
        ${CRYPTOLIB}
        ${TNMPLIB}
        ${HTTPLIB}
        ${TNIMSDKLIB}
        ${LIBCURL}
        )
ENDIF()

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})
set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
