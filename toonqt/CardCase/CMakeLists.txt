cmake_minimum_required(VERSION 2.8.11) 

set(PACKAGE "CardCase")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DQT_DLL -DCARDCASE_LIB -DUNICODE)
    configure_file(
      ${CMAKE_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_SOURCE_DIR}/CardCase.rc
      @ONLY)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DCARDCASE_LIB)
ELSE()
    add_definitions(-DCARDCASE_LIB)
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
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/ToonProtocold.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/Searchd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/TNMVD.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/ToonProtocol.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/Search.lib)
        ENDIF()
    ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Commond.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/LocalStoraged.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/NetWorkApid.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/IMCored.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/TNMVDd.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/ToonProtocold.lib)
            SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Debug/Searchd.lib)
        ELSE()
            SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/Common.lib)
            SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/LocalStorage.lib)
            SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/NetWorkApi.lib)
            SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/IMCore.lib)
            SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/TNMVD.lib)
            SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x86/bin/Release/ToonProtocol.lib)
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
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libSearch.so)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.so)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.so)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.so)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.so)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.so)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.so)
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
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Debug/libSearch.dylib)
    ELSE()
        SET(COMMONLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libCommon.dylib)
        SET(STORAGELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libLocalStorage.dylib)
        SET(NETWORKLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libNetWorkApi.dylib)
        SET(IMCORELIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libIMCore.dylib)
        SET(TNMVDLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libTNMVD.dylib)
        SET(TOONPROTOCAL ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libToonProtocol.dylib)
        SET(SEARCHLIB ${PROJECT_SOURCE_DIR}/toonsdk/build/x64/bin/Release/libSearch.dylib)
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
include_directories(${PROJECT_SOURCE_DIR}/ToonProtocol)
include_directories(${PROJECT_SOURCE_DIR}/Search)




FILE(GLOB CARDCASE_HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Friend/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Colleague/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Group/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.h
    )
FILE(GLOB CARDCASE_FORM_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Friend/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Colleague/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.ui
    )
FILE(GLOB CARDCASE_SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Friend/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Colleague/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Group/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupChat/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.cpp
    )
FILE(GLOB CARDCASE_RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
#FILE(GLOB CARDCASE_MOC_FILES 
    #${CMAKE_CURRENT_SOURCE_DIR}/CardCaseListArea.h
    #${CMAKE_CURRENT_SOURCE_DIR}/CardCaseDetailsArea.h
    #${CMAKE_CURRENT_SOURCE_DIR}/cardcasesearcharea.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNColleagueTreeView.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNCardCaseTreeModel.h
    #${CMAKE_CURRENT_SOURCE_DIR}/PhotoGetter.h
    #${CMAKE_CURRENT_SOURCE_DIR}/CardCase.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNCardCaseColleagueItemDelegate.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNCompanyItemWidget.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNCardCaseListItemWidget.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Colleague/TNDepartmentItemWidget.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Friend/TNCardCaseListItemDelegate.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Friend/TNCardCaseListAdapter.h
    #${CMAKE_CURRENT_SOURCE_DIR}/cardcasesearchbottom.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Search/*.h
    #${CMAKE_CURRENT_SOURCE_DIR}/TNSearchItemWidget.h
    #${CMAKE_CURRENT_SOURCE_DIR}/searchtableview.h
    #${CMAKE_CURRENT_SOURCE_DIR}/ToonCommand/*.h
#    ) 
FILE(GLOB NOTAUTOMOC_SOURCE ${CMAKE_BINARY_DIR}/CardCase/qrc_*.cpp)
set_property(SOURCE ${NOTAUTOMOC_SOURCE} PROPERTY SKIP_AUTOMOC ON)

if (MSVC)
    SOURCE_GROUP("Header Files" FILES ${CARDCASE_HEADER_FILES})
    SOURCE_GROUP("Form Files" FILES ${CARDCASE_FORM_FILES})
    SOURCE_GROUP("Source Files" FILES ${CARDCASE_SOURCE_FILES})
    SOURCE_GROUP("Resource Files" FILES ${CARDCASE_RESOURCE_FILES})
endif(MSVC)
#QT GUI

find_package(Qt5Network)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Sql)
#find_package(Qt5Multimedia)
find_package(Qt5WebEngineWidgets)

QT5_WRAP_UI(FORMS_UIC ${CARDCASE_FORM_FILES})
QT5_ADD_RESOURCES(QRC_RCC ${CARDCASE_RESOURCE_FILES})
#QT5_WRAP_CPP(HEADERS_MOC ${CARDCASE_MOC_FILES})

#MESSAGE(STATUS "HEADERS_MOC:" ${HEADERS_MOC})

if(MSVC)
    SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC})
endif(MSVC)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(${PACKAGE} SHARED
    ${CARDCASE_RESOURCE_FILES}
    ${NOTICE_WAV_SOURCE_FILES}
    ${CARDCASE_HEADER_FILES}
    ${CARDCASE_SOURCE_FILES}
    ${CARDCASE_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    ${CMAKE_CURRENT_SOURCE_DIR}/CardCase.rc
    )
ELSE()
ADD_LIBRARY(${PACKAGE} SHARED
    ${CARDCASE_RESOURCE_FILES}
    ${NOTICE_WAV_SOURCE_FILES}
    ${CARDCASE_HEADER_FILES}
    ${CARDCASE_SOURCE_FILES}
    ${CARDCASE_FORM_FILES}
    ${FROMS_UIC}
    ${QRC_RCC}
    ${HEADERS_MOC}
    )
ENDIF()

#生成目录
    TARGET_LINK_LIBRARIES(${PACKAGE}
        Qt5::WebEngineWidgets
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        ${COMMONLIB}
        ${STORAGELIB}
        ${NETWORKLIB}
        ${AMRLIB}
        ${TNMVDLIB}
        ${IMCORELIB}
        ${TOONPROTOCAL}
        ${SEARCHLIB}
        )

set_target_properties(${PACKAGE} PROPERTIES SOVERSION ${TOON_VERSION})

IF(APPLE)
    set(LIBRARY_OUTPUT_PATH ${TOON_MAC_APP_PATH})
ELSE()
    set(LIBRARY_OUTPUT_PATH ${TOON_OUTPUT_PATH})
ENDIF()

