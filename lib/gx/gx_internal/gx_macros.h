#pragma once

#if !__GX_INTERNAL__
#  error "include gx.h instead."
#endif

#define GX_STRINGIFY(expr) #expr

#define GX_PRAGMA(expr) _Pragma(GX_STRINGIFY(expr))

#define GX_DIAGNOSTIC_BEGIN_MODIFY(modifier, flag)                             \
  GX_PRAGMA(GCC diagnostic push)                                               \
  GX_PRAGMA(GCC diagnostic modifier flag)

#define GX_DIAGNOSTIC_END_MODIFY() GX_PRAGMA(GCC diagnostic pop)
