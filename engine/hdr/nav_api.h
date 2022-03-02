#ifndef NAV_API_H
#define NAV_API_H

#ifdef __cplusplus

#ifdef EXPORT_NAV_API
#define NAV_API extern "C" __declspec(dllexport)
#else
#define NAV_API extern "C" __declspec(dllimport)
#endif

#ifdef EXPORT_NAV_GAME_API
#define NAV_GAME_API extern "C" __declspec(dllexport)
#else
#define NAV_GAME_API extern "C" __declspec(dllimport)
#endif

#else

#ifdef EXPORT_NAV_API
#define NAV_API  __declspec(dllexport)
#else
#define NAV_API __declspec(dllimport)
#endif

#ifdef EXPORT_NAV_GAME_API
#define NAV_GAME_API __declspec(dllexport)
#else
#define NAV_GAME_API __declspec(dllimport)
#endif

#endif

#endif