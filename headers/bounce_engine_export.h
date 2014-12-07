
#ifndef bounce_engine_EXPORT_H
#define bounce_engine_EXPORT_H

#ifdef bounce_engine_BUILT_AS_STATIC
#  define bounce_engine_EXPORT
#  define BOUNCE_ENGINE_NO_EXPORT
#else
#  ifndef bounce_engine_EXPORT
#    ifdef bounce_engine_EXPORTS
        /* We are building this library */
#      define bounce_engine_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define bounce_engine_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef BOUNCE_ENGINE_NO_EXPORT
#    define BOUNCE_ENGINE_NO_EXPORT 
#  endif
#endif

#ifndef BOUNCE_ENGINE_DEPRECATED
#  define BOUNCE_ENGINE_DEPRECATED __declspec(deprecated)
#endif

#ifndef BOUNCE_ENGINE_DEPRECATED_EXPORT
#  define BOUNCE_ENGINE_DEPRECATED_EXPORT bounce_engine_EXPORT BOUNCE_ENGINE_DEPRECATED
#endif

#ifndef BOUNCE_ENGINE_DEPRECATED_NO_EXPORT
#  define BOUNCE_ENGINE_DEPRECATED_NO_EXPORT BOUNCE_ENGINE_NO_EXPORT BOUNCE_ENGINE_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define BOUNCE_ENGINE_NO_DEPRECATED
#endif

#endif
