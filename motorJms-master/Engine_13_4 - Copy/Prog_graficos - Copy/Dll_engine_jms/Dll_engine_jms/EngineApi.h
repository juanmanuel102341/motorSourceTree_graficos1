#ifndef ENGINE_API_H
#define ENGINE_API_H


#ifdef DLL_ENGINE_JMS_EXPORTS
#define ENGINE_API _declspec(dllexport)
#else
#define ENGINE_API _declspec(dllimport)
#endif

#endif