cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "FaceId")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DFACEID_LIB -DUNICODE)
    SET (CMAKE_DEBUG_POSTFIX "d")
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/FaceId.rc
      @ONLY)
    #find_library(GDIPLUS gdiplus)
    #message(STATUS "gdiplus lib:" ${GDIPLUS})
ELSE()
    add_definitions(-DFACEID_LIB)
ENDIF()


#根据不同平台的编译环境加载lib
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET (CMAKE_DEBUG_POSTFIX "d")
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_tracking.lib)
            SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_recognition.lib)
            SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_detection.lib)
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/LocalStoraged.lib)
        ELSE()
            SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_tracking.lib)
            SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_recognition.lib)
            SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x64/libarcsoft_fsdk_face_detection.lib)
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_tracking.lib)
            SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_recognition.lib)
            SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_detection.lib)
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
        ELSE()
            SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_tracking.lib)
            SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_recognition.lib)
            SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/windows/x86/libarcsoft_fsdk_face_detection.lib)
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
        ENDIF()
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_tracking.so)
        SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_recognition.so)
        SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_detection.so)
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libLocalStorage.so)
    ELSE()
        SET(FACET_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_tracking.so)
        SET(FACER_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_recognition.so)
        SET(FACED_LIB ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/lib/linux_x64/libarcsoft_fsdk_face_detection.so)
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
    ENDIF()
ENDIF()

IF(APPLE)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
    ELSE()
    ENDIF()
ENDIF()



#头文件搜索路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/LocalStorage)
include_directories(${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/include)
#include_directories(${PROJECT_SOURCE_DIR}/toonsdk/opencv/include)


FILE(GLOB NOTICE_HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/toonsdk/face_tracking/include/*.h
    )

FILE(GLOB NOTICE_FORM_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    )

FILE(GLOB NOTICE_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

FILE(GLOB NOTICE_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)


if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${NOTICE_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${NOTICE_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${NOTICE_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${NOTICE_RESOURCE_FILES})
endif(MSVC)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)
find_package(Qt5Multimedia)
find_package(Qt5MultimediaWidgets)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/FaceId.rc
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

#生成目录
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        ${COMMONLIB}
        ${STORAGELIB}
        ${FACET_LIB}
        ${FACER_LIB}
        ${FACED_LIB}
        )

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

IF(APPLE)
    set(LIBRARY_OUTPUT_PATH ${TOON_MAC_APP_PATH})
ELSE()
    set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
ENDIF()
