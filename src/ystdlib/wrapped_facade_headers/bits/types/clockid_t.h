#ifndef YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_CLOCKID_T_HPP
#define YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_CLOCKID_T_HPP

// clang-format off
// IWYU pragma: begin_exports
#if defined(__linux__)
#include <bits/time.h>
#include <bits/types/clockid_t.h>
#elif defined(__APPLE__)

#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 150000
#include <_time.h>
#else
#include <time.h>
#endif

#endif
// IWYU pragma: end_exports
// clang-format on

#endif  // YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_CLOCKID_T_HPP
