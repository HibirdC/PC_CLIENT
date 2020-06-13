cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "Mine")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DMINE_LIB -DUNICODE)
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/Mine.rc
      @ONLY)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DMINE_LIB)
ELSE()
    add_definitions(-DMINE_LIB)
ENDIF()

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TNMVDd.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ToonProtocold.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TNMVD.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ToonProtocol.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TNMVDd.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ToonProtocold.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TNMVD.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ToonProtocol.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.so)
    ENDIF()
ENDIF ()

IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.dylib)
    ENDIF()
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ToonProtocol)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/TNMVD)
include_directories(${PROJECT_SOURCE_DIR}/Common)


FILE(GLOB PROTOCOL_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

FILE(GLOB PROTOCOL_FROM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
FILE(GLOB PROTOCOL_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

#FILE(GLOB PROTOCOL_MOC_FILES
    #${CMAKE_CURRENT_SOURCE_DIR}/TNMyCardListItemWidget.h
    #${CMAKE_CURRENT_SOURCE_DIR}/MineListArea.h
    #${CMAKE_CURRENT_SOURCE_DIR}/MineDetailsArea.h
	#${CMAKE_CURRENT_SOURCE_DIR}/Mine.h
#    )



if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${PROTOCOL_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${PROTOCOL_FROM_FILES})
    SOURCE_GROUP("Source Files" FILES ${PROTOCOL_SOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5Sql)

QT5_WRAP_UI(FORMS_UIC ${PROTOCOL_FROM_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${PROTOCOL_MOC_FILES})

#MESSAGE(STATUS "HEADERS_MOC:" ${HEADERS_MOC})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED
    ${PROTOCOL_WAV_SOURCE_FILES}
    ${PROTOCOL_HEADER_FILES}
    ${PROTOCOL_SOURCE_FILES}
    ${PROTOCOL_FROM_FILES}
    ${FROMS_UIC} ${QRC_RCC}
    ${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/Mine.rc
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED
    ${PROTOCOL_WAV_SOURCE_FILES}
    ${PROTOCOL_HEADER_FILES}
    ${PROTOCOL_SOURCE_FILES}
    ${PROTOCOL_FROM_FILES}
    ${FROMS_UIC} ${QRC_RCC}
    ${HEADERS_MOC}
    )
ENDIF()

#MESSAGE(STATUS "amr lib:" ${AMRLIB})
#生成目录
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::WebEngineWidgets
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql
        ${COMMONLIB}
        ${NETWORKLIB}
        ${IMCORELIB}
        ${STORAGELIB}
        ${TOONPROTOCAL}
        ${TNMVDLIB}
        )

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})


IF(APPLE)
    set(LIBRARY_OUTPUT_PATH ${TOON_MAC_APP_PATH})
ELSE()
    set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
ENDIF()

