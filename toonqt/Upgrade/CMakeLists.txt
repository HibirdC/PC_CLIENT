cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "Upgrade")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DUPGRADE_DLL)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DUPGRADE_DLL)
ELSE()
    add_definitions(-DUPGRADE_DLL)
ENDIF()

#根据不同平台的编译环境加载lib
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
    #set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Commond.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/NetWorkApid.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
    ENDIF()
ENDIF ()

IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
    ENDIF()
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/Common/minizip)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/zlib/include)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)



FILE(GLOB UPGRADE_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h) 
FILE(GLOB UPGRADE_FORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
FILE(GLOB UPGRADE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB UPGRADE_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
#FILE(GLOB UPGRADE_MOC_FILES
    #${CMAKE_CURRENT_SOURCE_DIR}/TNDownloadProgressDialog.h
#    )
FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/Upgrade/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)


if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${UPGRADE_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${UPGRADE_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${UPGRADE_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${UPGRADE_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
#find_package(Qt5Sql)
#find_package(Qt5Multimedia)
#find_package(Qt5WebEngineWidgets)

QT5_WRAP_UI(FORMS_UIC ${UPGRADE_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${UPGRADE_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${UPGRADE_MOC_FILES})


if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

add_executable(${PACKAGE} WIN32
    ${UPGRADE_RESOURCE_FILES} 
    ${UPGRADE_HEADER_FILES}
    ${UPGRADE_SOURCE_FILES}
    ${UPGRADE_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC})

#生成目录
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::Core 
        Qt5::Gui
        Qt5::Widgets
        #Qt5::Sql
        Qt5::Network
        #Qt5::Multimedia
        ${COMMONLIB}
        #${STORAGELIB}
        ${NETWORKLIB}
        #${IMCORELIB}
        )
set_target_properties(${PACKAGE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TOON_OUTPUT_PATH})
