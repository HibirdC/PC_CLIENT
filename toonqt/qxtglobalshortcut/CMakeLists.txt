cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE qxtglobalshortcut)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


FILE(GLOB SHORTCUT_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/*.h
    )

IF(APPLE)
    set(PLATFORMCPP ${CMAKE_CURRENT_SOURCE_DIR}/qxtglobalshortcut_mac.cpp)
    FIND_LIBRARY( CARBON_LIBRARY Carbon )
    FIND_LIBRARY( COCOA_LIBRARY Cocoa )
ENDIF()

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(PLATFORMCPP ${CMAKE_CURRENT_SOURCE_DIR}/qxtglobalshortcut_x11.cpp)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORMCPP ${CMAKE_CURRENT_SOURCE_DIR}/qxtglobalshortcut_win.cpp)
ENDIF()

FILE(GLOB SHORTCUT_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/qxtglobalshortcut.cpp
    ${PLATFORMCPP} 
    )

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

if(NOT APPLE)
find_package(X11)
endif()

include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
include_directories(${X11_INCLUDE_DIR})



ADD_LIBRARY(${PACKAGE} SHARED
    ${SHORTCUT_HEADER_FILES}
    ${SHORTCUT_SOURCE_FILES}
    )

TARGET_LINK_LIBRARIES(${PACKAGE}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    #${X11_LIBRARIES}
    ${CARBON_LIBRARY}
    ${COCOA_LIBRARY}
    )


set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

message(status "qxt out put:" ${TOON_OUTPUT_PATH})
set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
