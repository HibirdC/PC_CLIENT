cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "TNMVD")
set(CMAKE_AUTOMOC ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DTNMVD_LIB -DUNICODE)
    SET (CMAKE_DEBUG_POSTFIX "d")
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/TNMVD.rc
      @ONLY)
    #set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MD")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DTNMVD_LIB)
ENDIF()

IF(APPLE)
    add_definitions(-DTNMVD_LIB)
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
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/IMCored.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ToonProtocold.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ToonProtocol.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ToonProtocold.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ToonProtocol.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.so)
    ENDIF()
ENDIF ()
IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.dylib)
    ENDIF()
ENDIF()
#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/ToonProtocol)


FILE(GLOB TNMVD_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/frames/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/emotion/*.h
    )
FILE(GLOB TNMVD_FORM_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/frames/*.ui
    )
FILE(GLOB TNMVD_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/frames/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/emotion/*.cpp
    )
FILE(GLOB TNMVD_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/TNMVD/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)

if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${TNMVD_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${TNMVD_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${TNMVD_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${TNMVD_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Sql)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)

QT5_WRAP_UI(FORMS_UIC ${TNMVD_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${TNMVD_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${TNMVD_MOC_FILES})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
    FILE(GLOB NETWORK_GENERATED_FILES ${HEADERS_MOC}) 
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    ADD_LIBRARY(${PACKAGE} SHARED ${TNMVD_RESOURCE_FILES} ${TNMVD_HEADER_FILES} ${TNMVD_SOURCE_FILES} ${TNMVD_FORM_FILES} ${FROMS_UIC} ${QRC_RCC} ${HEADERS_MOC}
        ${CMAKE_CURRENT_SOURCE_DIR}/TNMVD.rc)
ELSE()
    ADD_LIBRARY(${PACKAGE} SHARED ${TNMVD_RESOURCE_FILES} ${TNMVD_HEADER_FILES} ${TNMVD_SOURCE_FILES} ${TNMVD_FORM_FILES} ${FROMS_UIC} ${QRC_RCC} ${HEADERS_MOC})
ENDIF()

TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
    Qt5::WebChannel
    Qt5::WebEngineWidgets
    ${COMMONLIB}
    ${STORAGELIB}
    ${NETWORKLIB}
    ${IMCORELIB}
    ${TOONPROTOCAL}
    )


set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})

