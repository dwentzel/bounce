#ifndef BOUNCE_DISABLE_CLANG_WARNINGS_H_
#define BOUNCE_DISABLE_CLANG_WARNINGS_H_

#ifdef __clang__
#   pragma GCC diagnostic ignored "-Wall"
#   pragma GCC diagnostic ignored "-Wextra"
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wconversion"
#   pragma clang diagnostic ignored "-Wdeprecated"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wpacked"
#   pragma clang diagnostic ignored "-Wextra-semi"
#   pragma clang diagnostic ignored "-Wswitch-enum"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wdocumentation"
#   pragma clang diagnostic ignored "-Wdocumentation-html"
#   pragma clang diagnostic ignored "-Wswitch-enum"
#   pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#   pragma clang diagnostic ignored "-Wswitch-enum"
#   pragma clang diagnostic ignored "-Wnewline-eof"
#   pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#   pragma clang diagnostic ignored "-Wundef"
#   pragma clang diagnostic ignored "-Wnewline-eof"
#endif

#endif // BOUNCE_DISABLE_CLANG_WARNINGS_H_
