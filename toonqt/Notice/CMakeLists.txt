cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "Notice")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DNOTICE_LIB -DUNICODE)
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/Notice.rc
      @ONLY)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DNOTICE_LIB)
ELSE()
    add_definitions(-DNOTICE_LIB)
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
            SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x64/lib/opencore-amrnb.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ToonProtocold.lib)
            SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ScreenShotd.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Searchd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TNMVD.lib)
            SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x64/lib/opencore-amrnb.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ToonProtocol.lib)
            SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ScreenShot.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Search.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TNMVDd.lib)
            SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x86/lib/opencore-amrnb.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ToonProtocold.lib)
            SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ScreenShotd.lib)
            SET(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/tnimsdkd.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Searchd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TNMVD.lib)
            SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x86/lib/opencore-amrnb.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ToonProtocol.lib)
            SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ScreenShot.lib)
            SET(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/lib/x86/tnimsdk.lib)
            SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libssl.lib)
            SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/x86/libcrypto.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Search.lib)
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
        SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/linux/lib/libopencore-amrnb.so)
        SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libScreenShot.so)
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libSearch.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.so)
        SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/linux/lib/libopencore-amrnb.so)
        SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libScreenShot.so)
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libSearch.so)
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
        SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/mac/lib/libopencore-amrnb.a)
        SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libScreenShot.dylib)
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libSearch.dylib)

        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTMTP.dylib)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnchttp.dylib)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libtnimsdk.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.dylib)
        SET(AMRLIB ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/mac/lib/libopencore-amrnb.a)
        SET(SCREENSHOTLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libScreenShot.dylib)
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libSearch.dylib)

        SET(TNMPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTMTP.dylib)
        SET(HTTPLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnchttp.dylib)
        set(TNIMSDKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libtnimsdk.dylib)
    ENDIF()
    set(OPENALLIB ${PROJECT_SOURCE_DIR}/toonsdk/openal/mac/libopenal.dylib)
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/AtSearch)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GroupChat)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand)
include_directories(${PROJECT_SOURCE_DIR}/ToonProtocol)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/Search)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include)
include_directories(${PROJECT_SOURCE_DIR}/TNMVD)
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/ScreenShot)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/list_notice)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/details_notice)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/emoji)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/input)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/audio)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/audio/wav)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model_data)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/draft)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/out_line_message)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/video)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/history)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    include_directories(${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/include)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    include_directories(${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/linux/include)
ELSE()
    include_directories(${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/mac/include)
ENDIF()

if(APPLE)
    set(MAC_PLAY_SOUND_H ${CMAKE_CURRENT_SOURCE_DIR}/audio/macosx/*.h)
    set(MAC_PLAY_SOUND_SRC ${CMAKE_CURRENT_SOURCE_DIR}/audio/macosx/*.cpp)
    include_directories(${PROJECT_SOURCE_DIR}/toonsdk/openal/include)
endif()


FILE(GLOB NOTICE_HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AtSearch/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/list_notice/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/details_notice/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/emoji/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/wav/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/input/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/model_data/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/draft/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/out_line_message/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/video/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/history/*.h
    ${MAC_PLAY_SOUND_H}
    )

FILE(GLOB NOTICE_FORM_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/AtSearch/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/details_notice/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/emoji/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/video/*.ui
    )

FILE(GLOB NOTICE_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wav/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AtSearch/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/list_notice/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/details_notice/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/wav/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model_data/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/emoji/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/draft/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out_line_message/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/video/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/history/*.cpp
    ${MAC_PLAY_SOUND_SRC}
    )

FILE(GLOB NOTICE_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/Notice/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)


if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${NOTICE_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${NOTICE_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${NOTICE_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${NOTICE_RESOURCE_FILES})
endif(MSVC)

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)
find_package(Qt5Multimedia)
find_package(Qt5WebEngineWidgets)

QT5_WRAP_UI(FORMS_UIC ${NOTICE_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${NOTICE_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${NOTICE_MOC_FILES})

#MESSAGE(STATUS "HEADERS_MOC:" ${HEADERS_MOC})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED
    ${NOTICE_RESOURCE_FILES}
    ${NOTICE_WAV_SOURCE_FILES}
    ${NOTICE_HEADER_FILES}
    ${NOTICE_SOURCE_FILES}
    ${NOTICE_FORM_FILES}
    ${FROMS_UIC} ${QRC_RCC}
    ${CMAKE_CURRENT_SOURCE_DIR}/Notice.rc
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED
    ${NOTICE_RESOURCE_FILES}
    ${NOTICE_WAV_SOURCE_FILES}
    ${NOTICE_HEADER_FILES}
    ${NOTICE_SOURCE_FILES}
    ${NOTICE_FORM_FILES}
    ${FROMS_UIC} ${QRC_RCC}
    )
ENDIF()

#MESSAGE(STATUS "amr lib:" ${AMRLIB})
#生成目录
MESSAGE(STATUS "TNIMSDK lib:" ${TNIMSDKLIB})
MESSAGE(STATUS "OPENSSL lib:" ${OPENSSLLIB})
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::WebEngineWidgets
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        Qt5::Multimedia
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${AMRLIB}
        ${TNMVDLIB}
        ${IMCORELIB}
        ${TOONPROTOCAL}
        ${SCREENSHOTLIB}
        ${TNIMSDKLIB}
        ${OPENSSLLIB}
        ${CRYPTOLIB}
        ${SEARCHLIB}
        ${OPENALLIB}
        )

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

IF(APPLE)
    set(LIBRARY_OUTPUT_PATH ${TOON_MAC_APP_PATH})
ELSE()
    set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
ENDIF()
