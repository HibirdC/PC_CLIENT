﻿
#ifndef QXTGLOBALSHORTCUT_EXPORT_H
#define QXTGLOBALSHORTCUT_EXPORT_H

#ifdef QXTGLOBALSHORTCUT_STATIC_DEFINE
#  define QXTGLOBALSHORTCUT_EXPORT
#  define QXTGLOBALSHORTCUT_NO_EXPORT
#else
#  ifndef QXTGLOBALSHORTCUT_EXPORT
#    ifdef qxtglobalshortcut_EXPORTS
        /* We are building this library */
#      define QXTGLOBALSHORTCUT_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      ifdef _MSC_VER
#      	   define QXTGLOBALSHORTCUT_EXPORT __declspec(dllimport)
#      else
#      	   define QXTGLOBALSHORTCUT_EXPORT __attribute__((visibility("default")))
#      endif
#    endif
#  endif

#  ifndef QXTGLOBALSHORTCUT_NO_EXPORT
#    define QXTGLOBALSHORTCUT_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef QXTGLOBALSHORTCUT_DEPRECATED
#  define QXTGLOBALSHORTCUT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef QXTGLOBALSHORTCUT_DEPRECATED_EXPORT
#  define QXTGLOBALSHORTCUT_DEPRECATED_EXPORT QXTGLOBALSHORTCUT_EXPORT QXTGLOBALSHORTCUT_DEPRECATED
#endif

#ifndef QXTGLOBALSHORTCUT_DEPRECATED_NO_EXPORT
#  define QXTGLOBALSHORTCUT_DEPRECATED_NO_EXPORT QXTGLOBALSHORTCUT_NO_EXPORT QXTGLOBALSHORTCUT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QXTGLOBALSHORTCUT_NO_DEPRECATED
#    define QXTGLOBALSHORTCUT_NO_DEPRECATED
#  endif
#endif

#endif
