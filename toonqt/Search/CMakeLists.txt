cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "Search")
set(CMAKE_AUTOMOC ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DSEARCH_LIB -DUNICODE)
    SET (CMAKE_DEBUG_POSTFIX "d")
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/Search.rc
      @ONLY)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DSEARCH_LIB)
ENDIF()

IF(APPLE)
    add_definitions(-DSEARCH_LIB)
ENDIF()

#根据不同平台的编译环境加载lib
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TNMVDd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TNMVD.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TNMVDd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TNMVD.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.so)
    ENDIF()
ENDIF ()
IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.dylib)
    ENDIF()
ENDIF()
#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/TNMVD)


FILE(GLOB SEARCH_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Search/*.h
    )
FILE(GLOB SEARCH_FORM_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Search/*.ui
    )
FILE(GLOB SEARCH_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Search/*.cpp
    )
FILE(GLOB SEARCH_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/Search/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)

if (MSVC)
	SOURCE_GROUP("Header Files" FILES ${SEARCH_HEADER_FILES})
	SOURCE_GROUP("Form Files" FILES ${SEARCH_FORM_FILES})
	SOURCE_GROUP("Source Files" FILES ${SEARCH_SOURCE_FILES})
	SOURCE_GROUP("Resource Files" FILES ${SEARCH_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Sql)
find_package(Qt5Widgets)
find_package(Qt5Network)

QT5_WRAP_UI(FORMS_UIC ${SEARCH_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${SEARCH_RESOURCE_FILES})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
    FILE(GLOB NETWORK_GENERATED_FILES ${HEADERS_MOC}) 
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	ADD_LIBRARY(${PACKAGE} SHARED ${SEARCH_RESOURCE_FILES} ${SEARCH_HEADER_FILES} ${SEARCH_SOURCE_FILES} ${SEARCH_FORM_FILES} ${FROMS_UIC} ${QRC_RCC} ${HEADERS_MOC}
        ${CMAKE_CURRENT_SOURCE_DIR}/Search.rc)
ELSE()
	ADD_LIBRARY(${PACKAGE} SHARED ${SEARCH_RESOURCE_FILES} ${SEARCH_HEADER_FILES} ${SEARCH_SOURCE_FILES} ${SEARCH_FORM_FILES} ${FROMS_UIC} ${QRC_RCC} ${HEADERS_MOC})
ENDIF()

TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
    Qt5::Network
    ${COMMONLIB}
    ${STORAGELIB}
    ${NETWORKLIB}
    ${IMCORELIB}
    ${TNMVDLIB}
    )


set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})

