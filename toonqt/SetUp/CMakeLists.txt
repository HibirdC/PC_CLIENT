cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "Setup")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DSETUP_LIB -DUNICODE)
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/SetUp.rc
      @ONLY)
ELSE()
    add_definitions(-DSETUP_LIB)
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
            SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ScreenShotd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ScreenShot.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ScreenShotd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ScreenShot.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.so)
        SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libScreenShot.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libScreenShot.so)
    ENDIF()
ENDIF ()

IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.dylib)
        SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libScreenShot.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(SCREENLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libScreenShot.dylib)
    ENDIF()
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/TNMVD)
include_directories(${PROJECT_SOURCE_DIR}/ScreenShot)



FILE(GLOB SETUP_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h) 
FILE(GLOB SETUP_FORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
FILE(GLOB SETUP_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB SETUP_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
#FILE(GLOB SETUP_MOC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/TNSyncCatalogDialog.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/TNExitLoginWidget.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/SetUpListArea.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/TNLocaleStorageSettingWidget.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/TNFeedBackProposalDialog.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/TNAboutUsWidget.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/TNExitLoginConfirmDialog.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/SetUpDetailsArea.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/SetUp.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/AppearanceWidget.h
#    )

FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/SetUp/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)


if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${SETUP_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${SETUP_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${SETUP_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${SETUP_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)
#find_package(Qt5Multimedia)
#find_package(Qt5WebEngineWidgets)

QT5_WRAP_UI(FORMS_UIC ${SETUP_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${SETUP_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${SETUP_MOC_FILES})


if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED 
    ${SETUP_RESOURCE_FILES} 
    ${SETUP_HEADER_FILES}
    ${SETUP_SOURCE_FILES}
    ${SETUP_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/SetUp.rc
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED 
    ${SETUP_RESOURCE_FILES} 
    ${SETUP_HEADER_FILES}
    ${SETUP_SOURCE_FILES}
    ${SETUP_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    )
ENDIF()

#生成目录
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::Core 
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        #Qt5::Multimedia
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${IMCORELIB}
        ${SCREENLIB}
        )

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

IF(APPLE)
    set(LIBRARY_OUTPUT_PATH ${TOON_MAC_APP_PATH})
ELSE()
    set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
ENDIF()

