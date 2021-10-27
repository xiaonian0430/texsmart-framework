#pragma once

#include <stdint.h>
#ifndef __cplusplus
#   include <stdbool.h>
#endif

#if defined _WIN32
#   ifdef TEXSMART_EXPORTS
#        define TEXSMART_API __declspec(dllexport)
#   else
#       ifdef __GNUC__
#           define TEXSMART_API __attribute__ ((dllimport))
#       else
#           define TEXSMART_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   endif
#else
#   if __GNUC__ >= 4
#       define TEXSMART_API __attribute__ ((visibility ("default")))
#   else
#       define TEXSMART_API
#   endif
#endif

#ifdef __cplusplus    //if used by C++ code
extern "C" {          //we need to export the C interface
namespace tencent {
namespace ai {
namespace texsmart {
#endif

TEXSMART_API void Util_PrintUnicodeString(const wchar_t *str, bool has_endl);

#ifdef __cplusplus    //if used by C++ code
} //end of texsmart
} //end of ai
} //end of tencent
} //extern "C"
#endif
