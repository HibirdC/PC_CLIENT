# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------
win32{
    TEMPLATE = lib
    CONFIG +=debug_and_release
    Debug:TARGET = Created
    Release:TARGET = Create
    Debug:DESTDIR = $$(TOONSDK)\x64\Debug
    Release:DESTDIR = $$(TOONSDK)\x64\Release
    QT += core widgets gui \
        webenginewidgets
    DEFINES += WIN64 QT_DLL CREATE_LIB
    Debug:INCLUDEPATH += ./GeneratedFiles \
        . \
        ./GeneratedFiles/Debug \
        ../Common
    Release:INCLUDEPATH += ./GeneratedFiles \
        . \
        ./GeneratedFiles/Release \
        ../Common
    Debug:LIBS += $$(TOONSDK)/x64/Debug/Commond.lib
    Release:LIBS += $$(TOONSDK)/x64/Release/Common.lib
    PRECOMPILED_HEADER = stdafx.h
    DEPENDPATH += .
    Debug:MOC_DIR += ./GeneratedFiles/debug
    Release:MOC_DIR += ./GeneratedFiles/Release
    Debug:OBJECTS_DIR += debug
    Release:OBJECTS_DIR += Release
    UI_DIR += ./GeneratedFiles
    RCC_DIR += ./GeneratedFiles
    include(Create.pri)
}
unix{
    TEMPLATE = lib
    CONFIG +=debug_and_release
    Debug:TARGET = Created
    Release:TARGET = Create
    Debug:DESTDIR = ../../TOONSDK/x64/Debug
    QT += core widgets gui \
        webenginewidgets
    DEFINES += QT_DLL CREATE_LIB
    INCLUDEPATH += ./GeneratedFiles \
        . \
        ./GeneratedFiles/Debug \
        ../Common
    LIBS += ../../TOONSDK/x64/Debug/libCommond.dylib
    PRECOMPILED_HEADER = stdafx.h
    DEPENDPATH += .
    Debug:MOC_DIR += ./GeneratedFiles/debug
    Release:MOC_DIR += ./GeneratedFiles/Release
    Debug:OBJECTS_DIR += debug
    Release:OBJECTS_DIR += Release
    UI_DIR += ./GeneratedFiles
    RCC_DIR += ./GeneratedFiles
    include(Create.pri)
}
