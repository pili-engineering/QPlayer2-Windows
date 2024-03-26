#pragma once

#if defined __GNUC__
#  if __GNUC__ >= 4
#    define __QPLAYER_EXPORT   __attribute__((visibility("default")))
#    define __QPLAYER_IMPORT   __attribute__((visibility("default")))
#  else
#    define __QPLAYER_EXPORT
#    define __QPLAYER_IMPORT
#  endif
#elif _MSC_VER
#  define __QPLAYER_EXPORT     __declspec(dllexport)
#  define __QPLAYER_IMPORT     __declspec(dllimport)
#else
#  define __QPLAYER_EXPORT
#  define __QPLAYER_IMPORT
#endif

#ifndef QPLAYER_STATIC
#	ifdef QPLAYER_EXPORTS
#	define QPLAYER_API __QPLAYER_EXPORT
#	else
#	define QPLAYER_API __QPLAYER_IMPORT
#	endif
#else
#define QPLAYER_API
#endif
//namespace QMedia {
//#ifdef __OS_WINDOWS__
//	class QWindowsPlayer;
//	using QInnerPlayer = QWindowsPlayer;
//#elif defined __OS_LINUX__
//	class QLinuxPlayer;
//	using QInnerPlayer = QLinuxPlayer;
//#endif // __OS_WINDOWS__
//
//}
