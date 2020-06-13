cmake_minimum_required(VERSION 2.8.11) 
#MESSAGE(STATUS "bin dir:" ${CMAKE_CURRENT_BINARY_DIR})
#MESSAGE(STATUS "source dir:" ${CMAKE_CURRENT_SOURCE_DIR})
set(PACKAGE "Common")
set(CMAKE_AUTOMOC ON)
IF (WIN32)
    add_definitions(-DQT_DLL -DCOMMON_LIB -DUNICODE -D_CRT_SECURE_NO_WARNINGS
        -DWIN32_WINNT=0x0601)
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Linux") 
    add_definitions(-DCOMMON_LIB)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DCOMMON_LIB -DUNICODE)
    SET (CMAKE_DEBUG_POSTFIX "d")
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/Common.rc
      @ONLY)
    #set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MD")
ELSE()
    add_definitions(-DCOMMON_LIB)
ENDIF()


#头文件搜索路
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/xml) 
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/zlib/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/minizip)

FILE(GLOB COMMON_SPDLOG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    FILE (GLOB COMMON_MINIZIP_HEADER 
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/crypt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/ioapi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/mztools.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/unzip.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/zip.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/iowin32.h
        )

    FILE (GLOB COMMON_MINIZIP_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/crypt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/ioapi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/mztools.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/unzip.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/zip.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/iowin32.c
        )
else()
    FILE (GLOB COMMON_MINIZIP_HEADER 
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/crypt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/ioapi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/mztools.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/unzip.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/zip.h
        )

    FILE (GLOB COMMON_MINIZIP_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/crypt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/ioapi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/mztools.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/unzip.c
        ${CMAKE_CURRENT_SOURCE_DIR}/minizip/zip.c
        )
endif()

if(APPLE)
    FILE (GLOB COMMON_MAC_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/mac/mac_getwindowrects.h
        )
    FILE (GLOB COMMON_MAC_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/mac/mac_getwindowrects.mm
        )
endif()

FILE(GLOB COMMON_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    #${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/*.h
    ${COMMON_MINIZIP_HEADER}
    )
FILE(GLOB COMMON_FORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
FILE(GLOB COMMON_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${COMMON_MINIZIP_FILES}/*.c
    ${COMMON_MINIZIP_SOURCE}
    )

FILE(GLOB COMMON_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
FILE(GLOB COMMON_XML_FILES ${CMAKE_CURRENT_SOURCE_DIR}/xml/*)

if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${COMMON_HEADER_FILES} ${COMMON_MOC_FILES})
    SOURCE_GROUP("Form Files" FILES ${COMMON_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${COMMON_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${COMMON_RESOURCE_FILES})
    SOURCE_GROUP("Source Files\\xml" FILES ${COMMON_XML_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux") 
find_package(Qt5X11Extras)
ENDIF()


IF (CMAKE_SYSTEM_NAME MATCHES "Linux") 
    set(ZLIB "${PROJECT_SOURCE_DIR}/toonsdk/zlib/linux/libz.so")
    set(SHORTCUTLIB "${TOON_OUTPUT_PATH}/libqxtglobalshortcut.so")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ZLIB "${PROJECT_SOURCE_DIR}/toonsdk/zlib/Windows/x64/lib/zlib.lib")
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
           set(SHORTCUTLIB "${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x64/Debug_add/qxtglobalshortcut.lib")
        ELSE()
           set(SHORTCUTLIB "${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x64/Release_add/qxtglobalshortcut.lib")
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(ZLIB "${PROJECT_SOURCE_DIR}/toonsdk/zlib/Windows/x86/lib/zlib.lib")
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
           set(SHORTCUTLIB "${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x86/Debug_add/qxtglobalshortcut.lib")
        ELSE()
           set(SHORTCUTLIB "${PROJECT_SOURCE_DIR}/toonsdk/qxtglobalshortcut/windows/x86/Release_add/qxtglobalshortcut.lib")
        ENDIF()
    ENDIF()
ENDIF()

IF(APPLE)
    set(ZLIB "${PROJECT_SOURCE_DIR}/toonsdk/zlib/mac/libz.dylib")
    set(SHORTCUTLIB "${TOON_OUTPUT_PATH}/libqxtglobalshortcut.dylib")
    set(MAC_LIBS)
    FIND_LIBRARY( COREFOUNDATION_LIBRARY CoreFoundation )
    LIST( APPEND MAC_LIBS ${COREFOUNDATION_LIBRARY} )

    #FIND_LIBRARY( SECURITY_LIBRARY Security )
    #LIST( APPEND MAC_LIBS ${SECURITY_LIBRARY} )

    FIND_LIBRARY( CARBON_LIBRARY Carbon)
    LIST( APPEND MAC_LIBS ${CARBON_LIBRARY} )

    #FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    #LIST(APPEND MAC_LIBS ${COCOA_LIBRARY})

    FIND_LIBRARY( APPKIT_LIBRARY AppKit )
    LIST( APPEND MAC_LIBS ${APPKIT_LIBRARY} )
ENDIF()

QT5_WRAP_UI(FORMS_UIC ${COMMON_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${COMMON_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${COMMON_MOC_FILES})

#MESSAGE(STATUS "headers_moc:" ${HEADERS_MOC})
if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${FORMS_UIC} ${HEADERS_MOC} ${FORMS_UIC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED
    ${COMMON_XML_FILES}
    ${COMMON_RESOURCE_FILES}
    ${COMMON_HEADER_FILES}
    ${COMMON_SOURCE_FILES}
    ${COMMON_SHORTCUT_FILES}
    ${COMMON_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${COMMON_MOC_FILES}
    ${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.rc
    )
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
ADD_LIBRARY(${PACKAGE} SHARED
    ${COMMON_XML_FILES}
    ${COMMON_RESOURCE_FILES}
    ${COMMON_HEADER_FILES}
    ${COMMON_SOURCE_FILES}
    ${COMMON_SHORTCUT_FILES}
    ${COMMON_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${COMMON_MOC_FILES}
    ${HEADERS_MOC}
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED
    ${COMMON_XML_FILES}
    ${COMMON_RESOURCE_FILES}
    ${COMMON_HEADER_FILES}
    ${COMMON_SOURCE_FILES}
    ${COMMON_SHORTCUT_FILES}
    ${COMMON_FORM_FILES}
    ${COMMON_MAC_HEADER}
    ${COMMON_MAC_SOURCE}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${COMMON_MOC_FILES}
    ${HEADERS_MOC}
    )
ENDIF()

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})


IF (CMAKE_SYSTEM_NAME MATCHES "Linux") 
TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Widgets
    Qt5::WebChannel
    Qt5::WebEngineWidgets
    Qt5::X11Extras
    ${ZLIB}
    ${SHORTCUTLIB}
    )
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Widgets
    Qt5::WebChannel
    Qt5::WebEngineWidgets
    ${ZLIB}
    ${SHORTCUTLIB}
    )
ELSE()
TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Widgets
    Qt5::WebChannel
    Qt5::WebEngineWidgets
    ${ZLIB}
    ${MAC_LIBS}
    ${SHORTCUTLIB}
    )
ENDIF()
#根据32bit和64bit生成不同的目录
set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
