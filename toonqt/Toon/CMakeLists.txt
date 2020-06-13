cmake_minimum_required(VERSION 2.8.11) 

#SET(CMAKE_PREFIX_PATH "D:\\Qt\\5.6\\msvc2013_64\\")
set(PACKAGE "toon")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(toon_signal MATCHES "^TOON_SIGNAL=1$")
    add_definitions(-DTOON_SIGNAL)
    message("add_definitions: TOON_SIGNAL")
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DUNICODE)
    configure_file(
      ${CMAKE_SOURCE_DIR}/toon.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/Toon.rc
      @ONLY)
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
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/TNMVDd.lib)
            SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ToonProtocold.lib)
            IF(FACE_ID)
                SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/FaceIdd.lib)
            ENDIF()
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TNMVD.lib)
            SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ToonProtocol.lib)
            IF(FACE_ID)
                SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/FaceId.lib)
            ENDIF()
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TNMVDd.lib)
            SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ToonProtocold.lib)
            IF(FACE_ID)
                SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/FaceIdd.lib)
            ENDIF()
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TNMVD.lib)
            SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ToonProtocol.lib)
            IF(FACE_ID)
                SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/FaceId.lib)
            ENDIF()
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    #SET(OPENSSLLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libssl.so)
    #SET(CRYPTOLIB ${PROJECT_SOURCE_DIR}/toonsdk/openssl/lib/linux/libcrypto.so)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.so)
        SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.so)
        IF(FACE_ID)
            SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libFaceId.so)
        ENDIF()
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.so)
        SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.so)
        IF(FACE_ID)
            SET(FACEID ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libFaceId.so)
        ENDIF()
    ENDIF()
ENDIF ()

IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libTNMVD.dylib)
        SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libToonProtocol.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.dylib)
        SET(TOONPROTOCOL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.dylib)
    ENDIF()
    #mac app
    IF(TOONTYPE MATCHES "^toon$")
        SET(MACOSX_BUNDLE_ICON_FILE toon.icns)
    ELSEIF(TOONTYPE MATCHES "^bjtoon$")
        SET(MACOSX_BUNDLE_ICON_FILE bjtoon.icns)
    ELSEIF(TOONTYPE MATCHES "^daotoon$")
        SET(MACOSX_BUNDLE_ICON_FILE bjtoon.icns)
    ELSEIF(TOONTYPE MATCHES "^qltoon$")
        SET(MACOSX_BUNDLE_ICON_FILE qltoon.icns)
    ELSEIF(TOONTYPE MATCHES "^mctoon$")
        SET(MACOSX_BUNDLE_ICON_FILE mctoon.icns)
    ELSEIF(TOONTYPE MATCHES "^zqtoon$")
        SET(MACOSX_BUNDLE_ICON_FILE zqtoon.icns)
    ELSE()
        SET(MACOSX_BUNDLE_ICON_FILE toon.icns)
    ENDIF()

    SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/${MACOSX_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    SET(TOON_ICNS ${CMAKE_CURRENT_SOURCE_DIR}/${MACOSX_BUNDLE_ICON_FILE})
ENDIF()

#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/NetWorkAPI)
#include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include)
#include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include/util)
#include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include/jce)
include_directories(${PROJECT_SOURCE_DIR}/IMCore)
include_directories(${PROJECT_SOURCE_DIR}/Notice)
include_directories(${PROJECT_SOURCE_DIR}/Mine)
include_directories(${PROJECT_SOURCE_DIR}/Create)
include_directories(${PROJECT_SOURCE_DIR}/Avatar)
include_directories(${PROJECT_SOURCE_DIR}/unReadList)
include_directories(${PROJECT_SOURCE_DIR}/TNMVD)
include_directories(${PROJECT_SOURCE_DIR}/ToonProtocol)
include_directories(${PROJECT_SOURCE_DIR}/FaceId)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Login)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/tnimsdk/include)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/TNMP/include)
IF(APPLE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Avatar)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unReadList)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/macApplication)
ENDIF()


if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(UNREADLIST_H ${CMAKE_CURRENT_SOURCE_DIR}/unReadList/*.h)
    set(UNREADLIST_CPP ${CMAKE_CURRENT_SOURCE_DIR}/unReadList/*.cpp)
    set(UNREADLIST_UI ${CMAKE_CURRENT_SOURCE_DIR}/unReadList/*.ui)
endif()

if(APPLE)
    set(MACAPPLICATION_H ${CMAKE_CURRENT_SOURCE_DIR}/macApplication/macqapplication.h)
    set(MACAPPLICATION_CPP ${CMAKE_CURRENT_SOURCE_DIR}/macApplication/macqapplication.cpp)

    set(ToonApplication_LIBS)
    FIND_LIBRARY( COREFOUNDATION_LIBRARY CoreFoundation )
    LIST( APPEND ToonApplication_LIBS ${COREFOUNDATION_LIBRARY} )

    FIND_LIBRARY( CARBON_LIBRARY Carbon)
    LIST( APPEND ToonApplication_LIBS ${CARBON_LIBRARY} )

    FIND_LIBRARY( APPKIT_LIBRARY AppKit )
    LIST( APPEND ToonApplication_LIBS ${APPKIT_LIBRARY} )
endif()

FILE(GLOB TOON_HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Login/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Avatar/*.h
    ${UNREADLIST_H}
    ${MACAPPLICATION_H}
    )
FILE(GLOB TOON_FROM_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Login/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Avatar/*.ui
    ${UNREADLIST_UI}
    )

FILE(GLOB TOON_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Login/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Avatar/*.cpp
    ${UNREADLIST_CPP}
    ${MACAPPLICATION_CPP}
    )

FILE(GLOB TOON_RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
    )

FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/Toon/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)

if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${TOON_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${TOON_FROM_FILES})
    SOURCE_GROUP("Source Files" FILES ${TOON_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${TOON_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)
find_package(Qt5Multimedia)
find_package(Qt5WebEngineWidgets)

QT5_WRAP_UI(FORMS_UIC ${TOON_FROM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${TOON_RESOURCE_FILES})

#MESSAGE(STATUS "HEADERS_MOC:" ${HEADERS_MOC})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
add_executable(${PACKAGE} MACOSX_BUNDLE WIN32
    ${TOON_ICNS}
    ${TOON_RESOURCE_FILES}
    ${TOON_HEADER_FILES}
    ${TOON_SOURCE_FILES}
    ${TOON_FROM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/Toon.rc
    )
ELSE()
add_executable(${PACKAGE} MACOSX_BUNDLE
    ${TOON_ICNS}
    ${TOON_RESOURCE_FILES}
    ${TOON_HEADER_FILES}
    ${TOON_SOURCE_FILES}
    ${TOON_FROM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    )
ENDIF()
#设置输出名字
set_target_properties(${PACKAGE} PROPERTIES OUTPUT_NAME ${TOON_OUTPUT_NAME})

IF( APPLE )
    SET( MACOSX_BUNDLE_HIGHRESOLUTION_CAPABLE "true")
    SET( MACOSX_BUNDLE_INFO_STRING "toon ${TOON_VERSION}" )
    SET( MACOSX_BUNDLE_BUNDLE_VERSION "${TOON_VERSION}" )
    SET( MACOSX_BUNDLE_LONG_VERSION_STRING "toon ${TOON_LONG_VERSION}" )
    SET( MACOSX_BUNDLE_SHORT_VERSION_STRING "${TOON_VERSION}" )
    SET( MACOSX_BUNDLE_COPYRIGHT "2017-2019 思源科技" )
    SET( MACOSX_BUNDLE_GUI_IDENTIFITER "com.syswin.toon")
    SET( MACOSX_BUNDLE_BUNDLE_NAME ${TOON_OUTPUT_NAME} )
    SET( MACOSX_BUNDLE_DISPLAY_NAME ${TOON_OUTPUT_NAME} )
ENDIF()

IF(APPLE)
set_target_properties(${PACKAGE} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(STD_CXX_LIB  -lstdc++)
ENDIF()

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
        ${ToonApplication_LIBS}
        ${TOONPROTOCOL}
        ${FACEID}
        ${STD_CXX_LIB}
        )

#文件拷贝
IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        IF(NOT EXISTS ${TOON_MAC_APP_PATH}/Plugin.xml)
            FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_mac.xml DESTINATION
                ${TOON_MAC_APP_PATH})
            FILE(RENAME ${TOON_MAC_APP_PATH}/Plugin_mac.xml ${TOON_MAC_APP_PATH}/Plugin.xml)
        ENDIF()
    ELSE()
        IF(NOT EXISTS ${TOON_MAC_APP_PATH}/Plugin.xml)
            FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_mac.xml DESTINATION
                ${TOON_MAC_APP_PATH})
            FILE(RENAME ${TOON_MAC_APP_PATH}/Plugin_mac.xml ${TOON_MAC_APP_PATH}/Plugin.xml)
        ENDIF()
    ENDIF()
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(FACE_LOCATE_64 ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64)
    set(FACE_LOCATE_86 ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86)
    set(OPEN_AMR_64 ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x64/dll)
    set(OPEN_AMR_86 ${PROJECT_SOURCE_DIR}/toonsdk/opencore_amr/windows/x86/dll)
    set(QXT_SHORTCUT_64D ${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x64/Debug_add)
    set(QXT_SHORTCUT_64 ${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x64/Release_add)
    set(QXT_SHORTCUT_86D ${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x86/Debug_add)
    set(QXT_SHORTCUT_86 ${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x86/Release_add)
    set(ZLIB_64 ${PROJECT_SOURCE_DIR}/toonsdk/zlib/Windows/x64/dll)
    set(ZLIB_86 ${PROJECT_SOURCE_DIR}/toonsdk/zlib/Windows/x86/dll)
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OUTPUTPATH64D ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/)
        set(OUTPUTPATH64  ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            #拷贝Plugin.xml
            IF(NOT EXISTS ${OUTPUTPATH64D}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_windows_d.xml
                    DESTINATION ${OUTPUTPATH64D})
                FILE(RENAME ${OUTPUTPATH64D}/Plugin_windows_d.xml
                    ${OUTPUTPATH64D}Plugin.xml)
            ENDIF()
            #人脸识别库拷贝
            IF(NOT EXISTS ${OUTPUTPATH64D}/libarcsoft_fsdk_face_detection.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_detection.dll
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH64D}/libarcsoft_fsdk_face_recognition.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_recognition.dll
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH64D}/libarcsoft_fsdk_face_tracking.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_tracking.dll
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
            #opencore_amr音频库拷贝
            IF(NOT EXISTS ${OUTPUTPATH64D}/libopencore-amrnb-0.dll)
                FILE(COPY ${OPEN_AMR_64}/libopencore-amrnb-0.dll 
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
            #快捷键库qt_shortcut拷贝
            IF(NOT EXISTS ${OUTPUTPATH64D}/qxtglobalshortcut.dll) 
                FILE(COPY ${QXT_SHORTCUT_64D}/qxtglobalshortcut.dll
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
            #拷贝zlib库
            IF(NOT EXISTS ${OUTPUTPATH64D}/zlib.dll)
                FILE(COPY ${ZLIB_64}/zlib.dll
                    DESTINATION ${OUTPUTPATH64D})
            ENDIF()
        ELSE()
            IF(NOT EXISTS ${OUTPUTPATH64}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_windows_r.xml
                    DESTINATION ${OUTPUTPATH64})
                FILE(RENAME ${OUTPUTPATH64}/Plugin_windows_r.xml
                    ${OUTPUTPATH64}/Plugin.xml)
            ENDIF()
            #人脸识别库拷贝
            IF(NOT EXISTS ${OUTPUTPATH64}/libarcsoft_fsdk_face_detection.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_detection.dll
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH64}/libarcsoft_fsdk_face_recognition.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_recognition.dll
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH64}/libarcsoft_fsdk_face_tracking.dll)
                FILE(COPY ${FACE_LOCATE_64}/libarcsoft_fsdk_face_tracking.dll
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
            #opencore_amr音频库拷贝
            IF(NOT EXISTS ${OUTPUTPATH64}/libopencore-amrnb-0.dll)
                FILE(COPY ${OPEN_AMR_64}/libopencore-amrnb-0.dll 
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
            #快捷键库qt_shortcut拷贝
            IF(NOT EXISTS ${OUTPUTPATH64}/qxtglobalshortcut.dll) 
                FILE(COPY ${QXT_SHORTCUT_64}/qxtglobalshortcut.dll
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
            #拷贝zlib库
            IF(NOT EXISTS ${OUTPUTPATH64}/zlib.dll)
                FILE(COPY ${ZLIB_64}/zlib.dll
                    DESTINATION ${OUTPUTPATH64})
            ENDIF()
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(OUTPUTPATH86D ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/)
        set(OUTPUTPATH86  ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            IF(NOT EXISTS ${OUTPUTPATH86D}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_windows_d.xml DESTINATION
                    ${OUTPUTPATH86D})
                FILE(RENAME ${OUTPUTPATH86D}/Plugin_windows_d.xml
                    ${OUTPUTPATH86D}/Plugin.xml)
            ENDIF()
            #人脸识别库拷贝
            IF(NOT EXISTS ${OUTPUTPATH86D}/libarcsoft_fsdk_face_detection.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_detection.dll
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH86D}/libarcsoft_fsdk_face_recognition.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_recognition.dll
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH86D}/libarcsoft_fsdk_face_tracking.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_tracking.dll
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()
            #opencore_amr音频库拷贝
            IF(NOT EXISTS ${OUTPUTPATH86D}/libopencore-amrnb-0.dll)
                FILE(COPY ${OPEN_AMR_86}/libopencore-amrnb-0.dll 
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()
            #快捷键库qt_shortcut拷贝
            IF(NOT EXISTS ${OUTPUTPATH86D}/qxtglobalshortcut.dll) 
                FILE(COPY ${QXT_SHORTCUT_86D}/qxtglobalshortcut.dll
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()
            #拷贝zlib库
            IF(NOT EXISTS ${OUTPUTPATH86D}/zlib.dll)
                FILE(COPY ${ZLIB_86}/zlib.dll
                    DESTINATION ${OUTPUTPATH86D})
            ENDIF()

        ELSE()
            IF(NOT EXISTS ${OUTPUTPATH86}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_windows_r.xml DESTINATION
                    ${OUTPUTPATH86})
                FILE(RENAME ${OUTPUTPATH86}/Plugin_windows_r.xml
                    ${OUTPUTPATH86}/Plugin.xml)
            ENDIF()
            #人脸识别库拷贝
            IF(NOT EXISTS ${OUTPUTPATH86}/libarcsoft_fsdk_face_detection.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_detection.dll
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH86}/libarcsoft_fsdk_face_recognition.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_recognition.dll
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
            IF(NOT EXISTS ${OUTPUTPATH86}/libarcsoft_fsdk_face_tracking.dll)
                FILE(COPY ${FACE_LOCATE_86}/libarcsoft_fsdk_face_tracking.dll
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
            #opencore_amr音频库拷贝
            IF(NOT EXISTS ${OUTPUTPATH86}/libopencore-amrnb-0.dll)
                FILE(COPY ${OPEN_AMR_86}/libopencore-amrnb-0.dll 
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
            #快捷键库qt_shortcut拷贝
            IF(NOT EXISTS ${OUTPUTPATH86}/qxtglobalshortcut.dll) 
                FILE(COPY ${QXT_SHORTCUT_86}/qxtglobalshortcut.dll
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
            #拷贝zlib库
            IF(NOT EXISTS ${OUTPUTPATH86}/zlib.dll)
                FILE(COPY ${ZLIB_86}/zlib.dll
                    DESTINATION ${OUTPUTPATH86})
            ENDIF()
        ENDIF()
    ENDIF()
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OUTPUTPATH64D ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/)
        set(OUTPUTPATH64  ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            IF(NOT EXISTS ${OUTPUTPATH64D}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_linux.xml DESTINATION
                    ${OUTPUTPATH64D})
                FILE(RENAME ${OUTPUTPATH64D}/Plugin_linux.xml
                    ${OUTPUTPATH64D}/Plugin.xml)
            ENDIF()
        ELSE()
            IF(NOT EXISTS ${OUTPUTPATH64}/Plugin.xml)
                FILE(COPY ${PROJECT_SOURCE_DIR}/toonsdk/config/Plugin_linux.xml DESTINATION
                    ${OUTPUTPATH64})
                FILE(RENAME ${OUTPUTPATH64}/Plugin_linux.xml
                    ${OUTPUTPATH64}/Plugin.xml)
            ENDIF()
        ENDIF()
    ENDIF()
ENDIF()

set_target_properties(${PACKAGE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TOON_OUTPUT_PATH})
